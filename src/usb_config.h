/*
********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright � 2007-2008 Microchip Technology Inc.  All rights reserved.           
                                                                                
Microchip licenses to you the right to use, modify, copy and distribute Software
only when embedded on a Microchip microcontroller or digital signal controller  
that is integrated into your product or third party product (pursuant to the    
sublicense terms in the accompanying license agreement).                        
                                                                                
You should refer to the license agreement accompanying this Software for        
additional information regarding your rights and obligations.                   
                                                                                
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,   
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF        
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.  
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER       
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR    
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES         
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR     
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF        
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES          
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.     
                                                                                
********************************************************************************
*/

// Created by the Microchip USBConfig Utility, Version 2.7.1.0, 12/7/2012, 20:17:36
#include "spidebug_features.h"

#ifndef _usb_config_h_
#define _usb_config_h_

#if defined(__PIC24F__)
    #include <p24fxxxx.h>
#elif defined(__18CXX)
    #include <p18cxxx.h>
#elif defined(__PIC32MX__)
    #include <p32xxxx.h>
    #include "plib.h"
#else
    #error No processor header file.
#endif

#define _USB_CONFIG_VERSION_MAJOR 2
#define _USB_CONFIG_VERSION_MINOR 7
#define _USB_CONFIG_VERSION_DOT   1
#define _USB_CONFIG_VERSION_BUILD 0

#ifdef USB_SERIAL

// Supported USB Configurations

#define USB_SUPPORT_DEVICE

// Hardware Configuration

#define USB_PING_PONG_MODE  USB_PING_PONG__FULL_PING_PONG

// Peripheral Configuration

#define MY_VID            0xfffe
#define MY_PID            0x1485
#define USB_POLLING
#define USB_PULLUP_OPTION      USB_PULLUP_ENABLE
#define USB_TRANSCEIVER_OPTION USB_INTERNAL_TRANSCEIVER
#define USB_EP0_BUFF_SIZE     8
#define USB_MAX_NUM_INT       (0+1)
#define USB_MAX_EP_NUMBER 6
#define USB_NUM_STRING_DESCRIPTORS 3

//#define USB_DISABLE_SOF_HANDLER                 
//#define USB_DISABLE_ERROR_HANDLER               
//#define USB_DISABLE_SET_DESCRIPTOR_HANDLER      
#define USB_USER_DEVICE_DESCRIPTOR         &device_dsc
#define USB_USER_DEVICE_DESCRIPTOR_INCLUDE extern ROM USB_DEVICE_DESCRIPTOR device_dsc
#define USB_USER_CONFIG_DESCRIPTOR         USB_CD_Ptr
#define USB_USER_CONFIG_DESCRIPTOR_INCLUDE extern ROM BYTE *ROM USB_CD_Ptr[]

#define USB_ENABLE_ALL_HANDLERS

// CDC Function Configuration

#define USB_USE_CDC
#define CDC_COMM_INTF_ID        0x00
#define CDC_COMM_EP             1
#define CDC_COMM_IN_EP_SIZE     10
#define CDC_DATA_INTF_ID        0x01
#define CDC_DATA_EP             2
#define CDC_DATA_IN_EP_SIZE     64
#define CDC_DATA_OUT_EP_SIZE    64

#define USB_CDC_SET_LINE_CODING_HANDLER mySetLineCodingHandler


//#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D2 //Send_Break command
#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D1 //Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and Serial_State commands

//#define USB_CDC_SUPPORT_DSR_REPORTING   //Signal from UART peripheral device, to CDC/USB host.  Indicates UART peripheral is ready to receive data and/or commands.
//#define USB_CDC_SUPPORT_DTR_SIGNALING   //Signal sent from the USB/CDC host, down to the UART peripheral device
//#define USB_CDC_SUPPORT_HARDWARE_FLOW_CONTROL   //Implements RTS/CTS UART flow control.

// HID Function Configuration
/*
#define USB_USE_HID
#define HID_INTF_ID             0x10
#define HID_EP 					1
#define HID_INT_IN_EP_SIZE      3
#define HID_INT_OUT_EP_SIZE     3
#define HID_NUM_OF_DSC          1
#define HID_RPT01_SIZE          50
*/
#endif /* USB_SERIAL */

#ifdef ANDROID_HOST

#define USB_SUPPORT_HOST

#define USB_PING_PONG_MODE  USB_PING_PONG__FULL_PING_PONG

#define NUM_TPL_ENTRIES 3
#define NUM_CLIENT_DRIVER_ENTRIES 2

#define USB_ENABLE_TRANSFER_EVENT

#define USB_HOST_APP_DATA_EVENT_HANDLER USB_ApplicationDataEventHandler
//#define USB_ENABLE_SOF_EVENT
#define USB_ENABLE_1MS_EVENT

#define USB_MAX_GENERIC_DEVICES 1
#define USB_NUM_CONTROL_NAKS 20
#define USB_SUPPORT_INTERRUPT_TRANSFERS
#define USB_SUPPORT_BULK_TRANSFERS
#define USB_NUM_INTERRUPT_NAKS 3
#define USB_INITIAL_VBUS_CURRENT (100/2)
#define USB_INSERT_TIME (250+1)
#define USB_HOST_APP_EVENT_HANDLER USB_ApplicationEventHandler

#define USBTasks()                  \
    {                               \
        USBHostTasks();             \
        AndroidTasks();          \
    }

#define USBInitialize(x)            \
    {                               \
        USBHostInit(x);             \
    }

#endif

#endif
