#include "common.h"
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "USB/usb.h"
#include "USB/usb_host_android.h"

static char manufacturer[] = "Microchip Technology Inc.";
static char model[] = "Basic Accessory Demo";
static char description[] = "SPI DEBUG";
static char version[] = "2.0";
static char uri[] = "http://www.microchip.com/android";
static char serial[] = "N/A";

ANDROID_ACCESSORY_INFORMATION myDeviceInfo =
{
    manufacturer,
    sizeof(manufacturer),
    model,
    sizeof(model),
    description,
    sizeof(description),
    version,
    sizeof(version),
    uri,
    sizeof(uri),
    serial,
    sizeof(serial)
};

//Creation of the data packet that is going to be sent.  In this example
//  there is just a command code and a one byte data.
typedef struct __attribute__((packed))
{
    BYTE command;
    BYTE data;
} ACCESSORY_APP_PACKET;

static BOOL device_attached = FALSE;
static BYTE read_buffer[64];
static ACCESSORY_APP_PACKET outgoing_packet;
static void* device_handle = NULL;

    BOOL responseNeeded;
    BYTE pushButtonValues = 0xFF;
    BYTE potPercentage = 0xFF;
    BOOL buttonsNeedUpdate = FALSE;
    BOOL potNeedsUpdate = FALSE;
    BOOL readyToRead = TRUE;
    BOOL writeInProgress = FALSE;
    BYTE tempValue = 0xFF;
    BYTE errorCode;
ACCESSORY_APP_PACKET* command_packet = NULL;

    BOOL connected_to_app = FALSE;
    BOOL need_to_disconnect_from_app = FALSE;
    DWORD size = 0;

#ifndef MAX_ALLOWED_CURRENT
    #define MAX_ALLOWED_CURRENT             (500)         // Maximum power we can supply in mA
#endif

typedef enum _ACCESSORY_DEMO_COMMANDS
{
    COMMAND_SET_LEDS            = 0x01,
    COMMAND_UPDATE_PUSHBUTTONS  = 0x02,
    COMMAND_UPDATE_POT          = 0x03,
    COMMAND_APP_CONNECT         = 0xFE,
    COMMAND_APP_DISCONNECT      = 0xFF
} ACCESSORY_DEMO_COMMANDS;

void usb_init(void) {
    USBInitialize(0);
    AndroidAppStart(&myDeviceInfo);
}

void usb_tick(void) {
    USBTasks();

    //If the device isn't attached yet,
    if(device_attached == FALSE)
    {
        buttonsNeedUpdate = TRUE;
        potNeedsUpdate = TRUE;
        need_to_disconnect_from_app = FALSE;
        connected_to_app = FALSE;
        size = 0;

        return;
    }


        if(readyToRead == TRUE)
        {
            errorCode = AndroidAppRead(device_handle, (BYTE*)&read_buffer, (DWORD)sizeof(read_buffer));
            //If the device is attached, then lets wait for a command from the application
            if( errorCode != USB_SUCCESS)
            {
                //Error
                //DEBUG_PrintString("Error trying to start read");
            }
            else
            {
                readyToRead = FALSE;
            }
        }

        size = 0;

        if(AndroidAppIsReadComplete(device_handle, &errorCode, &size) == TRUE)
        {
            //We've received a command over the USB from the Android device.
            if(errorCode == USB_SUCCESS)
            {
                //Maybe process the data here.  Maybe process it somewhere else.
                command_packet = (ACCESSORY_APP_PACKET*)&read_buffer[0];
            }
            else
            {
                //Error
                //DEBUG_PrintString("Error trying to complete read request");
            }

        }

        while(size > 0)
        {
            if(connected_to_app == FALSE)
            {
                if(command_packet->command == COMMAND_APP_CONNECT)
                {
                    connected_to_app = TRUE;
                    need_to_disconnect_from_app = FALSE;
                }
            }
            else
            {
                switch(command_packet->command)
                {
                    case COMMAND_SET_LEDS:

                        //SetLEDs(command_packet->data);
                        led1_set(!(command_packet->data & 0x01));
                        led2_set(!(command_packet->data & 0x02));
                        led3_set(!(command_packet->data & 0x04));
                        led4_set(!(command_packet->data & 0x08));
                        break;

                    case COMMAND_APP_DISCONNECT:
                        need_to_disconnect_from_app = TRUE;
                        break;

                    default:
                        //Error, unknown command
                        //DEBUG_PrintString("Error: unknown command received");
                        break;
                }
            }
            //All commands in this example are two bytes, so remove that from the queue
            size -= 2;
            //And move the pointer to the next packet (this works because
            //  all command packets are 2 bytes.  If variable packet size
            //  then need to handle moving the pointer by the size of the
            //  command type that arrived.
            command_packet++;

            if(need_to_disconnect_from_app == TRUE)
            {
                break;
            }
        }

        if(size == 0)
        {
            readyToRead = TRUE;
        }

        //Get the current pushbutton settings
        tempValue = (~PORTE) >> 8; //GetPushbuttons();

        //If the current button settings are different than the last time
        //  we read the button values, then we need to send an update to the
        //  attached Android device
        if(tempValue != pushButtonValues)
        {
            buttonsNeedUpdate = TRUE;
            pushButtonValues = tempValue;
        }

        //Get the current potentiometer setting
        tempValue = 0; //ReadPOT();

        //If it is different than the last time we read the pot, then we need
        //  to send it to the Android device
        if(tempValue != potPercentage)
        {
            potNeedsUpdate = TRUE;
            potPercentage = tempValue;
        }

        //If there is a write already in progress, we need to check its status
        if( writeInProgress == TRUE )
        {
            if(AndroidAppIsWriteComplete(device_handle, &errorCode, &size) == TRUE)
            {
                writeInProgress = FALSE;
                if(need_to_disconnect_from_app == TRUE)
                {
                    connected_to_app = FALSE;
                    need_to_disconnect_from_app = FALSE;
                }

                if(errorCode != USB_SUCCESS)
                {
                    //Error
                    //DEBUG_PrintString("Error trying to complete write");
                }
            }
        }

        if((need_to_disconnect_from_app == TRUE) && (writeInProgress == FALSE))
        {
            outgoing_packet.command = COMMAND_APP_DISCONNECT;
            outgoing_packet.data = 0;
            writeInProgress = TRUE;

            errorCode = AndroidAppWrite(device_handle,(BYTE*)&outgoing_packet, 2);
            if( errorCode != USB_SUCCESS )
            {
                //DEBUG_PrintString("Error trying to send button update");
            }
        }

        if(connected_to_app == FALSE)
        {
            //If the app hasn't told us to start sending data, let's not do anything else.
            return;
        }

        //If we need up update the button status on the Android device and we aren't
        //  already busy in a write, then we can send the new button data.
        if((buttonsNeedUpdate == TRUE) && (writeInProgress == FALSE))
        {
            outgoing_packet.command = COMMAND_UPDATE_PUSHBUTTONS;
            outgoing_packet.data = pushButtonValues;

            errorCode = AndroidAppWrite(device_handle,(BYTE*)&outgoing_packet, 2);
            if( errorCode != USB_SUCCESS )
            {
                //DEBUG_PrintString("Error trying to send button update");
            }

            buttonsNeedUpdate = FALSE;
            writeInProgress = TRUE;
        }

        //If we need up update the pot status on the Android device and we aren't
        //  already busy in a write, then we can send the new pot data.
        if((potNeedsUpdate == TRUE) && (writeInProgress == FALSE))
        {
            outgoing_packet.command = COMMAND_UPDATE_POT;
            outgoing_packet.data = potPercentage;

            errorCode = AndroidAppWrite(device_handle,(BYTE*)&outgoing_packet, 2);
            if( errorCode != USB_SUCCESS )
            {
                //DEBUG_PrintString("Error trying to send pot update");
            }

            potNeedsUpdate = FALSE;
            writeInProgress = TRUE;
        }
}

/****************************************************************************
  Function:
    BOOL USB_ApplicationDataEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )

  Summary:
    Handles USB data application events

  Description:
    Handles USB data application events

  Precondition:
    None

  Parameters:
    BYTE address - address of the device causing the event
    USB_EVENT event - the event that has occurred
    void* data - data associated with the event
    DWORD size - the size of the data in the data field

  Return Values:
    BOOL - Return TRUE of the event was processed.  Return FALSE if the event
           wasn't handled.

  Remarks:
    None
  ***************************************************************************/
BOOL USB_ApplicationDataEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    return FALSE;
}


/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )

  Summary:
    Handles USB application events

  Description:
    Handles USB application events

  Precondition:
    None

  Parameters:
    BYTE address - address of the device causing the event
    USB_EVENT event - the event that has occurred
    void* data - data associated with the event
    DWORD size - the size of the data in the data field

  Return Values:
    BOOL - Return TRUE of the event was processed.  Return FALSE if the event
           wasn't handled.

  Remarks:
    None
  ***************************************************************************/
BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( (INT)event )
    {
        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            if (((USB_VBUS_POWER_EVENT_DATA*)data)->current <= (MAX_ALLOWED_CURRENT / 2))
            {
                return TRUE;
            }
            else
            {
                //DEBUG_PrintString( "\r\n***** USB Error - device requires too much current *****\r\n" );
            }
            break;

        case EVENT_VBUS_RELEASE_POWER:
        case EVENT_HUB_ATTACH:
        case EVENT_UNSUPPORTED_DEVICE:
        case EVENT_CANNOT_ENUMERATE:
        case EVENT_CLIENT_INIT_ERROR:
        case EVENT_OUT_OF_MEMORY:
        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
        case EVENT_DETACH:                   // USB cable has been detached (data: BYTE, address of device)
        case EVENT_ANDROID_DETACH:
            device_attached = FALSE;
            return TRUE;
            break;

        // Android Specific events
        case EVENT_ANDROID_ATTACH:
            device_attached = TRUE;

            device_handle = data;
            return TRUE;

        default :
            break;
    }
    return FALSE;
}
