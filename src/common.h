#include <xc.h>
#include <plib.h>
#include <stdint.h>
#include <stdbool.h>
#include <p32xxxx.h>

/******************************************************************************/
#define VERSION_MAJOR "00"
#define VERSION_MINOR "01"
/******************************************************************************/

// activate for test / sender circuit!
// #define BUFFER_SENDER

// #define __FILE__
// #pragma message("File: " __FILE__)
#ifdef BUFFER_SENDER
// Transmitter - test version
   #if __FILE__=="main.c"
       #pragma message("Test / Sender Version, Ver.: " VERSION_MAJOR "." VERSION_MINOR)
   #endif
   #undef BUFFER_RECEIVER
#else
// Receiver - production version
//   #warning ("Production Version, Ver.: " VERSION_MAJOR "." VERSION_MINOR)
   // #ifdef main.c
      #pragma message("Production Version, Ver.: " VERSION_MAJOR "." VERSION_MINOR)
      //#undef main.c
   //#endif
   #define BUFFER_RECEIVER
#endif



#undef HAVE_RTCC

// 80MHz
#define SYS_FREQ 80000000L

/* main.c */
void delay_ms(int time_ms);
void delay_us(int time_us);
#define delay_50nS() {Nop();Nop();Nop();Nop();}

/* led.c */
void led1_set(BOOL onoff);
void led2_set(BOOL onoff);
void led3_set(BOOL onoff);
void led4_set(BOOL onoff);
void led5_set(BOOL onoff);
void led6_set(BOOL onoff);
void led7_set(BOOL onoff);
void led8_set(BOOL onoff);
void leds_init(void);

// lcd-color.c
void lcd_demo(void);


/* end */
