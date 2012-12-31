/* SSD1963 Display Controller */

#include "common.h"
#ifdef LCD_COLOR

#include "lcd-color.h"
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
#define MAX_X    (320-1) // Pixel
#define MAX_Y    (240-1) // Pixel

#define SSD1963_CMD_SOFT_RESET             0x01
#define SSD1963_CMD_GET_POWER_MODE         0x0A
#define SSD1963_CMD_GET_ADDRESS_MODE       0x0B
#define SSD1963_CMD_GET_DISPLAY_MODE       0x0D
#define SSD1963_CMD_GET_TEAR_EFFECT_STATUS 0x0E
#define SSD1963_CMD_ENTER_PARTIAL_MODE     0x12
#define SSD1963_CMD_ENTER_WHOLE_MODE       0x13
#define SSD1963_CMD_SET_DISPLAY_OFF        0x28
#define SSD1963_CMD_SET_DISPLAY_ON         0x29
#define SSD1963_CMD_SET_COLUMN_ADDRESS     0x2A
#define SSD1963_CMD_SET_PAGE_ADDRESS       0x2B
#define SSD1963_CMD_WRITE_MEMORY_START     0x2C
#define SSD1963_CMD_READ_MEMORY_START      0x2E
#define SSD1963_CMD_SET_PARTIAL_AREA       0x30
#define SSD1963_CMD_SET_ADDRESS_MODE       0x36
#define SSD1963_CMD_GET_LCD_MODE           0xB0
#define SSD1963_CMD_SET_LCD_MODE           0xB1
#define SSD1963_CMD_SET_PIXEL_DATA_IF      0xF0

extern void delay_ms(int time_ms);

static void lcd_set_window(unsigned int x_start, unsigned int x_end, unsigned int y_start, unsigned int y_end);
static void lcd_fill(unsigned long color);

void Write_Command(unsigned char command) {
    LCD_CD = LCD_CD_C;
    PMDIN = command; // CS low to WR low: 50ns (WAITB), WR low to WR high: 100ns (WAITM)
    while (mIsPMPBusy()); // 200ns done
    //   delay_50ns(); // WR high/PMBUSY to CE high (50ns)  -- 250ns done
}

void Write_Data(unsigned char data1) {
    LCD_CD = LCD_CD_D;
    PMDIN = data1; // CS low to WR low: 50ns (WAITB), WR low to WR high: 100ns (WAITM)
    while (mIsPMPBusy()); // 200ns done
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

static void init_SSD1963(void) {
    lcd_tris_init();

    LCD_RESET = LCD_RESET_ON;
    LCD_BACKLITE = LCD_BACKLITE_OFF; // turn off backlight while we reinit the lcd

    // Init Parallel Master Port
    // Note: CPU Errata: WAITE=1 is 0 wait cycles!
    // Note: 80MHz Peripheral Bus clock -> 12.5ns
    //       RD low must be 75ns min.
    // Pin 71 = PMACS1 = Disp. #CS
    // Pin 44 = PMALL/PMA0 = RB15 = DSP-#C/D   - nicht im PM verwenden!
    // Pin 43 = PMALH/PMA1 = RB14 = DSP-#RES   - nicht im PM verwenden!
    mPMPOpen(
            PMP_CS2_CS1_EN | PMP_MUX_OFF | PMP_READ_WRITE_EN | PMP_WRITE_POL_LO | PMP_READ_POL_LO | PMP_CS1_POL_LO | PMP_TTL | PMP_IDLE_CON,
            PMP_IRQ_OFF | PMP_DATA_BUS_8 | PMP_MODE_MASTER2 | PMP_AUTO_ADDR_OFF | PMP_WAIT_BEG_1 | PMP_WAIT_MID_0 | PMP_WAIT_END_1,
            PMP_PEN_14 ,
            PMP_INT_OFF
            );
    PMPSetAddress(0x4000); // CS1 = PMA 14!!!
    delay_ms(30); // critical reset recovery delay, RD and WR are LOW == Reset for ESCC

    mPMPEnable();
     

    delay_ms(30);
    LCD_RESET = LCD_RESET_OFF;
    delay_ms(3);

    Write_Command(SSD1963_CMD_SOFT_RESET);
    Write_Command(SSD1963_CMD_SOFT_RESET);
    Write_Command(SSD1963_CMD_SOFT_RESET);
    delay_ms(5);
    Command_Write(0xe0, 0x01); //START PLL
    delay_ms(1);
    Command_Write(0xe0, 0x03); //LOCK PLL

    Write_Command(0xb0); //SET LCD MODE  SET TFT 18Bits MODE
    Write_Data(0x0c); //SET TFT MODE & hsync+Vsync+DEN MODE
    Write_Data(0x80); //SET TFT MODE & hsync+Vsync+DEN MODE
    Write_Data(0x01); //SET horizontal size=320-1 HightByte
    Write_Data(0x3f); //SET horizontal size=320-1 LowByte
    Write_Data(0x00); //SET vertical size=240-1 HightByte
    Write_Data(0xef); //SET vertical size=240-1 LowByte
    Write_Data(0x00); //SET even/odd line RGB seq.=RGB

    Command_Write(SSD1963_CMD_SET_PIXEL_DATA_IF, 0x00); //SET pixel data I/F format=8bit
    Command_Write(0x3a, 0x60); // SET R G B format = 6 6 6

#ifdef PORTRAIT
    Command_Write(0x36,0xa0);   //portrait mode
#endif

    Write_Command(0xe2); //SET PLL freq=113.33MHz  ;
    Write_Data(0x22);
    Write_Data(0x03);
    Write_Data(0x04);

    Write_Command(0xe6); //SET PCLK freq=6.5MHz/19MHz  ; pixel clock frequency
    Write_Data(0x00); //0x02
    Write_Data(0xea); //0xb0
    Write_Data(0xec); //0xb5
    //Write_Data(0x0a);		//
    //Write_Data(0x3d);		//
    //Write_Data(0x70);		//


    Write_Command(0xb4); //SET HBP,
    Write_Data(0x01); //SET HSYNC Tatol = 440
    Write_Data(0xb8);
    Write_Data(0x00); //SET HBP = 68
    Write_Data(0x44);
    Write_Data(0x0f); //SET VBP 16 = 15 + 1
    Write_Data(0x00); //SET Hsync pulse start position
    Write_Data(0x00);
    Write_Data(0x00); //SET Hsync pulse subpixel start position

    Write_Command(0xb6); //SET VBP,
    Write_Data(0x01); //SET Vsync total 265 = 264 + 1
    Write_Data(0x08);
    Write_Data(0x00); //SET VBP = 18
    Write_Data(0x12);
    Write_Data(0x07); //SET Vsync pulse 8 = 7 + 1
    Write_Data(0x00); //SET Vsync pulse start position
    Write_Data(0x00);

    // turn on display, fill with black pixels, then turn on backlight.
    //lcd_set_window(0, MAX_X, 0, MAX_Y);
    Write_Command(SSD1963_CMD_SET_DISPLAY_ON);
    Write_Command(SSD1963_CMD_WRITE_MEMORY_START);
    lcd_fill(COLOR_BLACK);
    LCD_BACKLITE = LCD_BACKLITE_ON; // backlite on

}

void lcd_set_window(unsigned int x_start, unsigned int x_end, unsigned int y_start, unsigned int y_end) {
    Write_Command(SSD1963_CMD_SET_COLUMN_ADDRESS);
    Write_Data((x_start) >> 8);
    Write_Data(x_start);
    Write_Data((x_end) >> 8);
    Write_Data(x_end);

    Write_Command(SSD1963_CMD_SET_PAGE_ADDRESS);
    Write_Data((y_start) >> 8);
    Write_Data(y_start);
    Write_Data((y_end) >> 8);
    Write_Data(y_end);
}

static void lcd_fill(unsigned long color) {
    unsigned int x, y;
    lcd_set_window(0, MAX_X, 0, MAX_Y);
    Write_Command(SSD1963_CMD_WRITE_MEMORY_START);
    for (x = 0; x <= MAX_X; x++) {
        for (y = 0; y <= MAX_Y; y++) {
            SendData(color);
        }
    }
}

#ifdef DEMO
void test1(void) {
    unsigned int x, y;

    lcd_set_window(0, MAX_X, 0, MAX_Y);
    Write_Command(SSD1963_CMD_WRITE_MEMORY_START);
    unsigned long color = 0;
    for (x = 0; x <= MAX_X; x++) {
        for (y = 0; y <= MAX_Y; y++) {
            SendData(color);
            color += 8;
        }
    }
}

void test2(void) {
    unsigned int x, y;

    lcd_set_window(0, MAX_X, 0, MAX_Y);
    Write_Command(SSD1963_CMD_WRITE_MEMORY_START);
    uint32_t colors[] = { 0, 0x343434, 0x888888, 0xbbbbbb, 0xffffff, 0xff0000, 0x00ff00, 0x0000ff };
    for (x = 0; x <= MAX_X; x++) {
        for (y = 0; y <= MAX_Y; y++) {
            SendData(colors[(x/4) % 8]);
        }
    }

}

void FULL_RAM(unsigned long dat) {
    unsigned int x, y;
    lcd_set_window(0x00A0, 0x00B3, 0x0078, 0x00B3);
    Write_Command(SSD1963_CMD_WRITE_MEMORY_START);
    for (x = 0; x < 60; x++) {
        for (y = 0; y < 20; y++) {
            SendData(dat);
        }
    }

}
#endif

void lcd_show_color_string(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, const unsigned int font_width, const unsigned int font_height, const unsigned char font_table[], const unsigned int font_table_size, unsigned int length, const char* p) {
    const char* q = p + length;
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

        lcd_set_window(x, x + font_width-1, y, y+font_height-1);
        Write_Command(SSD1963_CMD_WRITE_MEMORY_START);

        int row;
        for (row = 0; row < font_height; row++) {
            int col;
            for (col = 0; col < font_width; col++) {
                const unsigned char glyph = font_table[glyph_id + col];
                uint32_t mask = (1 << row);
                bool visible = (glyph & mask);
                lcd_color_t color = visible ? foreground : background;
                SendData(color);
            }
        }

        x += font_width;
    }
}

void lcd_show_color_string_5x8(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, unsigned int length, const char* p) {
    const unsigned int font_width = 5;
    const unsigned int font_height = 8;
    lcd_show_color_string(x, y, foreground, background, font_width, font_height, font_table_5x8, sizeof(font_table_5x8), length, p);
}

void lcd_show_color_string_5x7(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, unsigned int length, const char* p) {
    const unsigned int font_width = 5;
    const unsigned int font_height = 7;
    lcd_show_color_string(x, y, foreground, background, font_width, font_height, font_table_5x7, sizeof(font_table_5x7), length, p);
}

void lcd_show_color_string_4x6(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, unsigned int length, const char* p) {
    const unsigned int font_width = 4;
    const unsigned int font_height = 6;
    lcd_show_color_string(x, y, foreground, background, font_width, font_height, font_table_4x6, sizeof(font_table_4x6), length, p);
}

void black_frame_with_border(void) {
    unsigned int i, j;
    Write_Command(SSD1963_CMD_WRITE_MEMORY_START);
    for (j = 0; j < 40; j++) {
        for (i = 0; i < 8; i++) {
            SendData(0xffffff); //
        }
    }

    for (j = 0; j < 238; j++) {
        SendData(0xff0000); //red
        for (i = 0; i < 159; i++) {
            SendData(0x000000); //blue
            SendData(0x000000); //blue
        }
        SendData(0x00ff00); //red
    }

    for (j = 0; j < 40; j++) {
        for (i = 0; i < 8; i++) {
            SendData(0xffffff); //red
        }
    }

}

#ifdef DEMO
void show_picture(void) {
    unsigned int x;
    //unsigned char z;
    lcd_set_window(0, MAX_X, 0, 29);
    Write_Command(SSD1963_CMD_WRITE_MEMORY_START);

    for (x = 0; x < 28800; x++) {
        Write_Data(pic[x]);
    }

}

void clearWDT(void){
    //   ClrWdt();
}

void xxFULL_RAM(unsigned long dat) {
    unsigned int x, y;
    lcd_set_window(160, 179, 120, 131);
    Write_Command(SSD1963_CMD_WRITE_MEMORY_START);
    for (x = 0; x < 60; x++) {
        for (y = 0; y < 20; y++) {
            SendData(dat);
        }
    }

}
#endif

void lcd_init(void) {
    init_SSD1963();
    black_frame_with_border();
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

#endif
