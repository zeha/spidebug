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

#if defined(ANDROID_HOST) || defined(USB_SERIAL)

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "USB/usb.h"

#endif

#ifdef ANDROID_HOST

#include "USB/usb_host_android.h"

// *****************************************************************************
// Client Driver Function Pointer Table for the USB Embedded Host foundation
// *****************************************************************************

CLIENT_DRIVER_TABLE usbClientDrvTable[NUM_CLIENT_DRIVER_ENTRIES] =
{
    {
        AndroidAppInitialize,
        AndroidAppEventHandler,
        AndroidAppDataEventHandler,
        0
    },
    {
        AndroidAppInitialize,
        AndroidAppEventHandler,
        AndroidAppDataEventHandler,
        ANDROID_INIT_FLAG_BYPASS_PROTOCOL
    }
};

// *****************************************************************************
// USB Embedded Host Targeted Peripheral List (TPL)
// *****************************************************************************
USB_TPL usbTPL[NUM_TPL_ENTRIES] =
{
      /*[1] Device identification information
        [2] Initial USB configuration to use
        [3] Client driver table entry
        [4] Flags (HNP supported, client driver entry, SetConfiguration() commands allowed)
    ---------------------------------------------------------------------
                [1]                      [2][3] [4]
    ---------------------------------------------------------------------*/
    { INIT_VID_PID( 0x18D1ul, 0x2D00ul ), 0, 1, {0} }, // Android accessory
    { INIT_VID_PID( 0x18D1ul, 0x2D01ul ), 0, 1, {0} }, // Android accessory
    { INIT_VID_PID( 0xFFFFul, 0xFFFFul ), 0, 0, {0} }, // Enumerates everything
};

#endif
