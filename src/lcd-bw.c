/* ST7565R Display Controller */

#include "common.h"
//#include "lcd-bw.h"
#include <peripheral/pmp.h>
#include <peripheral/ports.h>

#include "font-table-4x6.c"
#include "font-table-5x7.c"
#include "font-table-5x8.c"
// #define PORTRAIT

#ifdef PORTRAIT
  #pragma message(">>>>>>> Portrait Mode")
#else 
  #pragma message(">>>>>>> Landscape Mode")
#endif

// Display size
#define MAX_X    (128-1) // Pixel
#define MAX_Y    (64-1) // Pixel


extern void delay_ms(int time_ms);

static void lcd_set_window(unsigned int x_start, unsigned int x_end, unsigned int y_start, unsigned int y_end);
static void lcd_fill(unsigned long color);

void Write_Command(unsigned char command) {
    LCD_CD = LCD_CD_C;
    PMDIN = command; // CS low to WR low: 12ns (WAITB), WR low to WR high: 48ns (WAITM), 48ns WAITE
    while (mIsPMPBusy()); // 3 * 12ns = 36 ns
    //Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    // Nop(); Nop(); Nop();
}

inline void Write_Data(unsigned char data1) {
    LCD_CD = LCD_CD_D;
    PMDIN = data1; // CS low to WR low: 50ns (WAITB), WR low to WR high: 100ns (WAITM)
    while (mIsPMPBusy()); // 200ns done
    // Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    // Nop(); Nop(); Nop();
}
#define Write_Data_Fast(data1) {LCD_CD = LCD_CD_D; PMDIN = data1;}
// LCD_CS = 12.5 nS
// CS low to WR low: 50ns (WAITB), WR low to WR high: 100ns (WAITM)
//==============================================================

void Command_Write(unsigned char command, unsigned char data1) {
    Write_Command(command);
    Write_Data(data1);
}

void SendData(unsigned long color) {
    Write_Data_Fast((color) >> 16); // color is red
    Write_Data_Fast((color) >> 8); // color is green
    Write_Data_Fast(color); // color is blue

 //   Write_Data((color) >> 16); // color is red
 //   Write_Data((color) >> 8); // color is green
 //   Write_Data(color); // color is blue

}

void lcd_show_string(unsigned int x, unsigned int y, bool reverse, const unsigned int font_width, const unsigned int font_height, const unsigned char font_table[], const unsigned int font_table_size, unsigned int length, const char* p) {
    const char* q = p + length;

    Write_Command(0xB0 + y); // Send page address
    Write_Command(0x10 | ( x >> 4 ));  // column address upper 4 bits + 0x10
    Write_Command(0x00 | ( x & 0x0f));  // column address lower 4 bits + 0x00

    while (p != q) {
        int glyph_id = *p++;
        if (glyph_id >= 0x20) {
            glyph_id -= 0x20;
        }
        glyph_id *= font_width;
        if (glyph_id > font_table_size) {
            // non-printable (and out of bounds) characters are mapped to whitespace
            glyph_id = 0;
        }

//        lcd_set_window(x, x + font_width-1, y, y+font_height-1);
//        Write_Command(SSD1963_CMD_WRITE_MEMORY_START);


        int col;
        for (col = 0; col < font_width; col++) {
            const unsigned char glyph = font_table[glyph_id + col];
            Write_Data( reverse ? ~glyph : glyph );
        }

        x += font_width;
    }
}

void lcd_show_string_5x8(unsigned int x, unsigned int y, bool reverse, unsigned int length, const char* p) {
    const unsigned int font_width = 5;
    const unsigned int font_height = 8;
    lcd_show_string(x, y, reverse, font_width, font_height, font_table_5x8, sizeof(font_table_5x8), length, p);
}

void lcd_show_string_5x7(unsigned int x, unsigned int y, bool reverse, unsigned int length, const char* p) {
    const unsigned int font_width = 5;
    const unsigned int font_height = 7;
    lcd_show_string(x, y, reverse, font_width, font_height, font_table_5x7, sizeof(font_table_5x7), length, p);
}

void lcd_show_string_4x6(unsigned int x, unsigned int y, bool reverse, unsigned int length, const char* p) {
    const unsigned int font_width = 4;
    const unsigned int font_height = 6;
    lcd_show_string(x, y, reverse, font_width, font_height, font_table_4x6, sizeof(font_table_4x6), length, p);
}


void TestBWDisplay() {
    while (true) {
    Write_Command(0xA6); // Dispaly normal
    delay_ms(500);
    Write_Command(0xA7); // Dispaly invers
    delay_ms(200);
   // Write_Command(0xAE); // Dispaly OFF
    delay_ms(200);
   // Write_Command(0xAF); // Dispaly ON
    delay_ms(200);
    Nop();
    }
 }

void black_frame_with_border(void) {
    unsigned int i, j;

//    Write_Command(0xAE); // Dispaly OFF
    for (i = 0; i < 8; i++) {
        Write_Command(0xB0 + i); // Send page address
        Write_Command(0x10);  // column address upper 4 bits + 0x10
        Write_Command(0x00);  // column address lower 4 bits + 0x00
        for (j = 0; j < 128; j++) {
            Write_Data(j);
        }
    }
//    Write_Command(0xAF); // Dispaly ON

}


void lcd_init(void) {
    lcd_tris_init();

    LCD_RESET = LCD_RESET_ON;
    LCD_BACKLITE = LCD_BACKLITE_OFF; // turn off backlight while we reinit the lcd
    LCD_CD = LCD_CD_C;

    // Init Parallel Master Port
    // Note: CPU Errata: WAITE=1 is 0 wait cycles!
    // Note: 80MHz Peripheral Bus clock -> 12.5ns
    //       RD low must be 75ns min.
    // Pin 71 = PMACS1 = Disp. #CS
    // Pin 44 = PMALL/PMA0 = RB15 = DSP-#C/D   - nicht im PM verwenden!
    // Pin 43 = PMALH/PMA1 = RB14 = DSP-#RES   - nicht im PM verwenden!
    mPMPOpen(
            PMP_CS2_CS1_EN | PMP_MUX_OFF | PMP_READ_WRITE_EN | PMP_WRITE_POL_LO | PMP_READ_POL_LO | PMP_CS1_POL_LO | PMP_TTL | PMP_IDLE_CON,
            PMP_IRQ_OFF | PMP_DATA_BUS_8 | PMP_MODE_MASTER2 | PMP_AUTO_ADDR_OFF | PMP_WAIT_BEG_1 | PMP_WAIT_MID_5 | PMP_WAIT_END_4,
            PMP_PEN_14 ,
            PMP_INT_OFF
            );
    PMPSetAddress(0x4000); // CS1 = PMA 14!!!
    delay_ms(30); // critical reset recovery delay, RD and WR are LOW == Reset for ESCC

    mPMPEnable();


    delay_ms(30);
    LCD_RESET = LCD_RESET_OFF;
    delay_ms(3);

    delay_ms(20);

    Write_Command(0xA2); // 1/9 Bias
    Write_Command(0xA0); // ADC Select Normal
    Write_Command(0xC8); // COM Output Reverse
    Write_Command(0xA4); // Display All Points Normal
    Write_Command(0x40); // Display Start Line Set
    Write_Command(0x25); // Internal Resistor Ratio
    Write_Command(0x81); // Electronic Volume Mode Set
    //Write_Command(0x10); // Electronic Volume
    Write_Command(0x2F); // Electronic Volume
    Write_Command(0x2F); // Power Controller Set
    Write_Command(0xAF); // Display On

    // Set Line 0 for LCD Line Logic
    Write_Command(0x40); // Display start address + 0x40

    LCD_BACKLITE = LCD_BACKLITE_ON;

    black_frame_with_border();
//    TestBWDisplay();
    const char *p = " Hallo xxx ";
    lcd_show_string_5x8(24, 0, false, strlen(p), p);

    const char *q = " Line 1 ";
    lcd_show_string_5x8(24, 1, false, strlen(q), q);

    const char *r = " Line 7 ";
    lcd_show_string_5x8(24, 7, false, strlen(r), r);
}

#ifdef DEMO
void lcd_demo_loop(void) {
    bool led = false;

    while (1) {
        //    LCD_BACKLITE = LCD_BACKLITE_ON;         // backlite on

        led3_set(led);
        led = !led;

        black_frame_with_border();
        //STP_SC();
        //Command_Write(0x36, 0x08); // set color mode to BGR
        show_picture();
        clearWDT();
        delay_ms(2000);
        test1();
        clearWDT();
        delay_ms(4000);
        test2();
        delay_ms(4000);

        //STP_SC();
        //FULL_ON(0x000000);
        //STP_SC();
        lcd_fill(0xff0000); // red
        //STP_SC();
        FULL_RAM(0xffffff);	//
        delay_ms(1000);
        //STP_SC();
        //FULL_ON(0x9fff00);
        //STP_SC();
        lcd_fill(0x00ff00); // green
        //STP_SC();
        lcd_fill(0x0000ff); // blue
        delay_ms(1000);
        // //STP_SC();
        lcd_fill(0xff00ff); // purple
        delay_ms(1000);
        // //STP_SC();
        lcd_fill(0xffffff); // white
        delay_ms(1000);
        // //STP_SC();
        //  LCD_BACKLITE = LCD_BACKLITE_OFF;         // backlite on
        //      delay (1000);

    }
}
#endif
