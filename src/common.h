#ifndef COMMON_H
#define COMMON_H

#include <xc.h>
#include <plib.h>
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/
#define VERSION_MAJOR "00"
#define VERSION_MINOR "01"
/******************************************************************************/

#undef HAVE_RTCC
#undef SERIAL_USE_BUS
#define SERIAL_BUFFER_SIZE 64

// 80MHz
#define SYS_FREQ 80000000L

#define TRIS_INPUT      1
#define TRIS_OUTPUT     0

typedef uint16_t timer_ticks_t;

// main.c
void delay_ms(int time_ms);
void delay_us(int time_us);
#define delay_50nS() {Nop();Nop();Nop();Nop();}

// led.c
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
void lcd_init(void);
void lcd_demo_loop(void);

// usb.c
void usb_init(void);
void usb_tick(void);

#endif

