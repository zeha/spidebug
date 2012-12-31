#ifndef COMMON_H
#define COMMON_H

#include "spidebug_features.h"
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


#define BUS_DIRECTION LATFbits.LATF12
#define BUS_DIRECTION_TRIS TRISFbits.TRISF12
#define BUS_DIRECTION_RECEIVE 0
#define BUS_DIRECTION_TRANSMIT 1



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
typedef uint32_t lcd_color_t;
void lcd_init(void);
void lcd_demo_loop(void);
void lcd_show_color_string(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, unsigned int length, const char* p);
#define COLOR_BLACK                        0x000000
#define COLOR_WHITE                        0xffffff
#define COLOR_RED                          0xff0000
#define COLOR_GREEN                        0x00ff00
#define COLOR_BLUE                         0x0000ff

// usb.c
void usb_init(void);
void usb_tick(void);

#endif

