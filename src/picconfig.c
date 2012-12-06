/*
 * File:   picconfig.c
 * Author: ch
 *
 * Created on 14. März 2011, 17:57
 */

#include "common.h"

#pragma config ICESEL = ICS_PGx2


#ifdef __DEBUG
  #pragma message("********************** Debung build ****************************")
  #pragma config DEBUG = ON
#endif

// Freq
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPLLODIV = DIV_1
#pragma config POSCMOD = HS
#pragma config FNOSC = PRIPLL
#pragma config OSCIOFNC = OFF
#pragma config FPBDIV = DIV_1, FCKSM = CSECME
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)

// Clock Osc. 32kHZ
// disabled!
#ifdef HAVE_RTCC
#pragma config FSOSCEN = ON
#else
#pragma config FSOSCEN = OFF
#endif

//#pragma config USERID = 0x0
// Addr: 1FC0_2FF0 wird aber als BFC02FF0 dargestellt !?!??!?!?
//http://www.microchip.com/forums/m481840-print.aspx
//const __DEVCFG3bits_t __attribute__((section(".config_BFC02FF0"))) devcfg3 =
// {
//     {
//        .USERID = 0x0,
//     }
// };
 const int __attribute__((section(".config_BFC02FF0"))) configword_2ff0 = 0xffff0000u;

// Watchdog
#pragma config FWDTEN = OFF

// USB
//#pragma config FUSBIDIO = ON, FVBUSONIO = ON
//#pragma config UPLLEN = ON, UPLLIDIV = DIV_2

