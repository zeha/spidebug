/* 
 * File:   HardwareProfile.h
 * Author: ch
 *
 * Created on December 7, 2012, 8:05 PM
 */

#ifndef HARDWAREPROFILE_H
#define	HARDWAREPROFILE_H

#define USE_USB_BUS_SENSE_IO
#define USB_BUS_SENSE       PORTBbits.RB5
#define usb_init_bus_sense() { mPORTBSetPinsDigitalIn(BIT_5); }
#define self_power 1

#define LCD_RESET LATBbits.LATB14
#define LCD_RESET_ON 0
#define LCD_RESET_OFF 1

#define LCD_CD    LATBbits.LATB15
#define LCD_CD_C  0
#define LCD_CD_D  1

#define LCD_WR    LATDbits.LATD4
#define LCD_WR_ON  0
#define LCD_WR_OFF  1

#define LCD_RD    LATDbits.LATD5
#define LCD_RD_ON  0
#define LCD_RD_OFF  1

#define LCD_CS    LATDbits.LATD11
#define LCD_CS_ON  0
#define LCD_CS_OFF  1


#define LCD_BACKLITE LATDbits.LATD1
#define LCD_BACKLITE_ON 1
#define LCD_BACKLITE_OFF 0

// -RES, -C/D
// Backlite
#define lcd_tris_init() {  mPORTBSetPinsDigitalOut(BIT_14 | BIT_15);  mPORTDSetPinsDigitalOut(BIT_1); }

#endif	/* HARDWAREPROFILE_H */

