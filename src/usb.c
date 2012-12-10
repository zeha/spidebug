#include "common.h"
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "USB/usb.h"
#include "USB/usb_function_cdc.h"
#include "serial.h"

// usb_init must init this to 0 for CDC to work
USB_HANDLE  lastTransmission;

static uint8_t *usb_serial_rx;

void usb_init(void) {
    lastTransmission = 0;
    usb_serial_rx = serial_rx_pointer;

    // USB Vbus sense
    usb_init_bus_sense();
    USBDeviceInit();
#ifdef USB_INTERRUPT
    USBDeviceAttach();
#endif
    CDCSetBaudRate(115200);
    CDCSetCharacterFormat(NUM_STOP_BITS_1);
    CDCSetDataSize(8);
    CDCSetParity(PARITY_NONE);
}

void usb_tick(void) {
    USBDeviceTasks();
    if (USBGetDeviceState() >= CONFIGURED_STATE && USBSuspendControl == 0) {
        char buffer[64];
        unsigned int len = getsUSBUSART(buffer, sizeof(buffer));
        if (len > 0) {
            serial_begin_tx_raw(len, buffer);
        }
        if (USBUSARTIsTxTrfReady() && usb_serial_rx != serial_rx_pointer) {
            len = serial_rx_pointer - usb_serial_rx;
            if (len > sizeof(serial_rx_buffer)) {
                // wraparound
                len = sizeof(serial_rx_buffer) - (usb_serial_rx - serial_rx_buffer);
                putUSBUSART(usb_serial_rx, len);
                usb_serial_rx = serial_rx_buffer;
            }
            len = serial_rx_pointer - usb_serial_rx;
            putUSBUSART(usb_serial_rx, len);
            usb_serial_rx = serial_rx_pointer;
        }

        CDCTxService();
    }
}

#if defined(USB_CDC_SET_LINE_CODING_HANDLER)
void mySetLineCodingHandler(void)
{
    // just say "Yes, sir!" for now.
    CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate.Val);
    //U2BRG = ((GetPeripheralClock()+(BRG_DIV2/2*line_coding.dwDTERate.Val))/BRG_DIV2/line_coding.dwDTERate.Val-1);
    //U2MODEbits.BRGH = BRGH2;
}
#endif

BOOL USER_USB_CALLBACK_EVENT_HANDLER(int event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
            break;
        case EVENT_SOF:
            break;
        case EVENT_SUSPEND:
            break;
        case EVENT_RESUME:
            break;
        case EVENT_CONFIGURED:
            CDCInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            break;
        case EVENT_EP0_REQUEST:
            USBCheckCDCRequest();
            break;
        case EVENT_BUS_ERROR:
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT
            //      endpoints).
            break;
        default:
            break;
    }
    return TRUE;
}
