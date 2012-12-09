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

#endif	/* HARDWAREPROFILE_H */

