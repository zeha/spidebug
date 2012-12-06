#include "common.h"

void leds_init(void)
{
    PORTD = 0;
    mPORTDSetPinsDigitalOut(BIT_2|BIT_3|BIT_12|BIT_13|BIT_6|BIT_7);
    mPORTGSetPinsDigitalOut(BIT_15);
    mPORTBSetPinsDigitalOut(BIT_12);
}

void led1_set(BOOL onoff)
{
    PORTDbits.RD2 = onoff;
}
void led2_set(BOOL onoff)
{
    PORTDbits.RD3 = onoff;
}
void led3_set(BOOL onoff)
{
    PORTDbits.RD12 = onoff;
}
void led4_set(BOOL onoff)
{
    PORTDbits.RD13 = onoff;
}

void led5_set(BOOL onoff)
{
    PORTDbits.RD6 = onoff;
}
void led6_set(BOOL onoff)
{
    PORTDbits.RD7 = onoff;
}
void led7_set(BOOL onoff)
{
    PORTGbits.RG15 = onoff;
}
void led8_set(BOOL onoff)
{
    PORTBbits.RB12 = onoff;
}

