#include "common.h"
#include <stdint.h>
#include <stdbool.h>
#include "ledmatrix.h"


void ledmatrix_init() {
    TRISBCLR = 0x0F00;
    AD1PCFGSET = 0x0F00;
    TRISGCLR = 0x03;
    TRISFCLR = 0x03;
    ODCGSET = 0x3;
    ODCFSET = 0x3;

#ifdef LEDMATRIX_USE_INTERRUPT
    IEC0bits.T2IE = 0;
    IFS0bits.T2IF = 0;
    T2CON = 0;
    //T2CONbits.TCKPS = 0b11; // 1:256
    TMR2 = 0;
    PR2 = 0xFFFF;

    IPC2bits.T2IP = 2;
    IPC2bits.T2IS = 0;
    IEC0bits.T2IE = 1;

    T2CONSET = 0x8000; // ON
#endif
}


#define LED_ROW_ALL 0x7F00
#define LED_ROW_MAX 7

#define LED_COL_ALL 0xFF00
#define LED_COL_SHIFT 8

uint8_t ledmatrix_data[] = {
    0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF
//    0x01, 0x02, 0x04, 0x08, 0xFF, 0xFF, 0xFF
};

void ledmatrix_tick() {

    uint8_t col;
    uint32_t rowdata;
    

    // B = row
    // D = col
    //PORTDSET = LED_COL_ALL;
    //PORTDbits.RD9 = 0;
    //PORTGSET = 0x3;
    //PORTFSET = 0x3;
    //PORTGCLR = 0x3;
    //PORTFCLR = 0x3;

    for (col = 0; col != sizeof(ledmatrix_data); col++) {
        rowdata = ledmatrix_data[col];
        PORTBSET = LED_COL_ALL;
        PORTGSET = 0x3;
        PORTGCLR = (rowdata & 0x3);
        PORTFSET = 0x3;
        PORTFCLR = ((rowdata & 0x8) >> 3) | ((rowdata & 0x4) >> 1);

        PORTBCLR = (1 << col) << 8;
        delay_ms(2);

    }

}

void __ISR(_TIMER_2_VECTOR, ipl2) ledmatrix_isr(void) {
    if (IFS0bits.T2IF) {
        ledmatrix_tick();
        IFS0bits.T2IF = 0;
    }
}
