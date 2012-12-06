/*
 * File:   picconfig.c
 * Author: ch
 *
 * Created on 14. März 2011, 17:57
 */

// PIC32MX460F512L Configuration Bit Settings
#include <p32xxxx.h>
#include "common.h"

#ifdef __DEBUG
  #pragma message("********************** Debung build ****************************")
  #pragma config DEBUG = ON
#endif

// DEVCFG3
// USERID = No Setting

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)
#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)

// #pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPLLODIV = DIV_1

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
//#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Inctive on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (WDT Enabled)

// ** #pragma config POSCMOD = HS
// #pragma config FNOSC = PRIPLL
// #pragma config OSCIOFNC = OFF
// ** #pragma config FPBDIV = DIV_1, FCKSM = CSECME
// #pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#ifdef HAVE_RTCC
#pragma config FSOSCEN = ON
#else
#pragma config FSOSCEN = OFF
#endif

// DEVCFG0
//#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


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
//

