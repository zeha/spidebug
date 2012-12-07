/* 
 * File:   HardwareProfile.h
 * Author: ch
 *
 * Created on December 7, 2012, 8:05 PM
 */

#ifndef HARDWAREPROFILE_H
#define	HARDWAREPROFILE_H
/*
    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
    #define USB_BUS_SENSE       1
 */

#define self_power 1

/*

    #define BAUDRATE2       57600UL
    #define BRG_DIV2        4
    #define BRGH2           1
*/

    //These definitions are only relevant if the respective functions are enabled
    //in the usb_config.h file.
    //Make sure these definitions match the GPIO pins being used for your hardware
    //setup.
/*
    #define UART_DTS PORTDbits.RD6
    #define UART_DTR LATAbits.LATA1
    #define UART_RTS LATFbits.LATF13
    #define UART_CTS PORTFbits.RF12

    #define mInitRTSPin() {TRISFbits.TRISF13 = 0;}   //Configure RTS as a digital output.
    #define mInitCTSPin() {TRISFbits.TRISF12 = 1;}   //Configure CTS as a digital input.  (Make sure pin is digital if ANxx functions is present on the pin)
    #define mInitDTSPin() {TRISDbits.TRISD6 = 1;}   //Configure DTS as a digital input.  (Make sure pin is digital if ANxx functions is present on the pin)
    #define mInitDTRPin() {TRISAbits.TRISA1 = 0;}   //Configure DTR as a digital output.
*/
#endif	/* HARDWAREPROFILE_H */

