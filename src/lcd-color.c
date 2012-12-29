//=============================================================
//          WINSTAR Display Co.,Ltd
//    LCM     	 :WF35 8 BIT (80-Series)
//    Contraller: SSD1963
//    Author     :Brian lin 2009/04/21
//    history     :
//==============================================================
//=================================
//   parameter  define
//=================================
#include "common.h"


// #define PORTRAIT

#ifdef PORTRAIT
  #pragma message(">>>>>>> Portrait Mode")
#else 
  #pragma message(">>>>>>> Landscape Mode")
#endif

// Display size
#define MAX_X    (320-1) // Pixel
#define MAX_Y    (240-1) // Pixel


#define LCD_RESET LATBbits.LATB14
#define LCD_RESET_ON 0
#define LCD_RESET_OFF 1

#define LCD_CD    LATBbits.LATB15
#define LCD_CD_C  0
#define LCD_CD_D  1

#define LCD_WR    LATDbits.LATD4
#define LCD_WR_ON  0
#define LCD_WR_OFF  1

#define LCD_RD    LATDbits.LATD5
#define LCD_RD_ON  0
#define LCD_RD_OFF  1

#define LCD_CS    LATDbits.LATD11
#define LCD_CS_ON  0
#define LCD_CS_OFF  1


#define LCD_BACKLITE LATDbits.LATD1
#define LCD_BACKLITE_ON 1
#define LCD_BACKLITE_OFF 0



const unsigned char font_table_5x7[] = {
0x00,0x00,0x00,0x00,0x00,		// 0-4
0x00,0x00,0x4F,0x00,0x00,		// 5-  (  1)  ! - 0x0021 Exclamation Mark
0x00,0x07,0x00,0x07,0x00,		//   (  2)  " - 0x0022 Quotation Mark
0x14,0x7F,0x14,0x7F,0x14,		//   (  3)  # - 0x0023 Number Sign
0x24,0x2A,0x7F,0x2A,0x12,		//   (  4)  $ - 0x0024 Dollar Sign
0x23,0x13,0x08,0x64,0x62,		//   (  5)  % - 0x0025 Percent Sign
0x36,0x49,0x55,0x22,0x50,		//   (  6)  & - 0x0026 Ampersand
0x00,0x05,0x03,0x00,0x00,		//   (  7)  ' - 0x0027 Apostrophe
0x00,0x1C,0x22,0x41,0x00,		//   (  8)  ( - 0x0028 Left Parenthesis
0x00,0x41,0x22,0x1C,0x00,		//   (  9)  ) - 0x0029 Right Parenthesis
0x14,0x08,0x3E,0x08,0x14,		//   ( 10)  * - 0x002A Asterisk
0x08,0x08,0x3E,0x08,0x08,		//   ( 11)  + - 0x002B Plus Sign
0x00,0x50,0x30,0x00,0x00,		//   ( 12)  , - 0x002C Comma
0x08,0x08,0x08,0x08,0x08,		//   ( 13)  - - 0x002D Hyphen-Minus
0x00,0x60,0x60,0x00,0x00,		//   ( 14)  . - 0x002E Full Stop
0x20,0x10,0x08,0x04,0x02,		//   ( 15)  / - 0x002F Solidus
0x3E,0x51,0x49,0x45,0x3E,		//   ( 16)  0 - 0x0030 Digit Zero
0x00,0x42,0x7F,0x40,0x00,		//   ( 17)  1 - 0x0031 Digit One
0x42,0x61,0x51,0x49,0x46,		//   ( 18)  2 - 0x0032 Digit Two
0x21,0x41,0x45,0x4B,0x31,		//   ( 19)  3 - 0x0033 Digit Three
0x18,0x14,0x12,0x7F,0x10,		//   ( 20)  4 - 0x0034 Digit Four
0x27,0x45,0x45,0x45,0x39,		//   ( 21)  5 - 0x0035 Digit Five
0x3C,0x4A,0x49,0x49,0x30,		//   ( 22)  6 - 0x0036 Digit Six
0x01,0x71,0x09,0x05,0x03,		//   ( 23)  7 - 0x0037 Digit Seven
0x36,0x49,0x49,0x49,0x36,		//   ( 24)  8 - 0x0038 Digit Eight
0x06,0x49,0x49,0x29,0x1E,		//   ( 25)  9 - 0x0039 Dight Nine
0x00,0x36,0x36,0x00,0x00,		//   ( 26)  : - 0x003A Colon
0x00,0x56,0x36,0x00,0x00,		//   ( 27)  ; - 0x003B Semicolon
0x08,0x14,0x22,0x41,0x00,		//   ( 28)  < - 0x003C Less-Than Sign
0x14,0x14,0x14,0x14,0x14,		//   ( 29)  = - 0x003D Equals Sign
0x00,0x41,0x22,0x14,0x08,		//   ( 30)  > - 0x003E Greater-Than Sign
0x02,0x01,0x51,0x09,0x06,		//   ( 31)  ? - 0x003F Question Mark
0x32,0x49,0x79,0x41,0x3E,		//   ( 32)  @ - 0x0040 Commercial At
0x7E,0x11,0x11,0x11,0x7E,		//   ( 33)  A - 0x0041 Latin Capital Letter A
0x7F,0x49,0x49,0x49,0x36,		//   ( 34)  B - 0x0042 Latin Capital Letter B
0x3E,0x41,0x41,0x41,0x22,		//   ( 35)  C - 0x0043 Latin Capital Letter C
0x7F,0x41,0x41,0x22,0x1C,		//   ( 36)  D - 0x0044 Latin Capital Letter D
0x7F,0x49,0x49,0x49,0x41,		//   ( 37)  E - 0x0045 Latin Capital Letter E
0x7F,0x09,0x09,0x09,0x01,		//   ( 38)  F - 0x0046 Latin Capital Letter F
0x3E,0x41,0x49,0x49,0x7A,		//   ( 39)  G - 0x0047 Latin Capital Letter G
0x7F,0x08,0x08,0x08,0x7F,		//   ( 40)  H - 0x0048 Latin Capital Letter H
0x00,0x41,0x7F,0x41,0x00,		//   ( 41)  I - 0x0049 Latin Capital Letter I
0x20,0x40,0x41,0x3F,0x01,		//   ( 42)  J - 0x004A Latin Capital Letter J
0x7F,0x08,0x14,0x22,0x41,		//   ( 43)  K - 0x004B Latin Capital Letter K
0x7F,0x40,0x40,0x40,0x40,		//   ( 44)  L - 0x004C Latin Capital Letter L
0x7F,0x02,0x0C,0x02,0x7F,		//   ( 45)  M - 0x004D Latin Capital Letter M
0x7F,0x04,0x08,0x10,0x7F,		//   ( 46)  N - 0x004E Latin Capital Letter N
0x3E,0x41,0x41,0x41,0x3E,		//   ( 47)  O - 0x004F Latin Capital Letter O
0x7F,0x09,0x09,0x09,0x06,		//   ( 48)  P - 0x0050 Latin Capital Letter P
0x3E,0x41,0x51,0x21,0x5E,		//   ( 49)  Q - 0x0051 Latin Capital Letter Q
0x7F,0x09,0x19,0x29,0x46,		//   ( 50)  R - 0x0052 Latin Capital Letter R
0x46,0x49,0x49,0x49,0x31,		//   ( 51)  S - 0x0053 Latin Capital Letter S
0x01,0x01,0x7F,0x01,0x01,		//   ( 52)  T - 0x0054 Latin Capital Letter T
0x3F,0x40,0x40,0x40,0x3F,		//   ( 53)  U - 0x0055 Latin Capital Letter U
0x1F,0x20,0x40,0x20,0x1F,		//   ( 54)  V - 0x0056 Latin Capital Letter V
0x3F,0x40,0x38,0x40,0x3F,		//   ( 55)  W - 0x0057 Latin Capital Letter W
0x63,0x14,0x08,0x14,0x63,		//   ( 56)  X - 0x0058 Latin Capital Letter X
0x07,0x08,0x70,0x08,0x07,		//   ( 57)  Y - 0x0059 Latin Capital Letter Y
0x61,0x51,0x49,0x45,0x43,		//   ( 58)  Z - 0x005A Latin Capital Letter Z
0x00,0x7F,0x41,0x41,0x00,		//   ( 59)  [ - 0x005B Left Square Bracket
0x02,0x04,0x08,0x10,0x20,		//   ( 60)  \ - 0x005C Reverse Solidus
0x00,0x41,0x41,0x7F,0x00,		//   ( 61)  ] - 0x005D Right Square Bracket
0x04,0x02,0x01,0x02,0x04,		//   ( 62)  ^ - 0x005E Circumflex Accent
0x40,0x40,0x40,0x40,0x40,		//   ( 63)  _ - 0x005F Low Line
0x01,0x02,0x04,0x00,0x00,		//   ( 64)  ` - 0x0060 Grave Accent
0x20,0x54,0x54,0x54,0x78,		//   ( 65)  a - 0x0061 Latin Small Letter A
0x7F,0x48,0x44,0x44,0x38,		//   ( 66)  b - 0x0062 Latin Small Letter B
0x38,0x44,0x44,0x44,0x20,		//   ( 67)  c - 0x0063 Latin Small Letter C
0x38,0x44,0x44,0x48,0x7F,		//   ( 68)  d - 0x0064 Latin Small Letter D
0x38,0x54,0x54,0x54,0x18,		//   ( 69)  e - 0x0065 Latin Small Letter E
0x08,0x7E,0x09,0x01,0x02,		//   ( 70)  f - 0x0066 Latin Small Letter F
0x06,0x49,0x49,0x49,0x3F,		//   ( 71)  g - 0x0067 Latin Small Letter G
0x7F,0x08,0x04,0x04,0x78,		//   ( 72)  h - 0x0068 Latin Small Letter H
0x00,0x44,0x7D,0x40,0x00,		//   ( 73)  i - 0x0069 Latin Small Letter I
0x20,0x40,0x44,0x3D,0x00,		//   ( 74)  j - 0x006A Latin Small Letter J
0x7F,0x10,0x28,0x44,0x00,		//   ( 75)  k - 0x006B Latin Small Letter K
0x00,0x41,0x7F,0x40,0x00,		//   ( 76)  l - 0x006C Latin Small Letter L
0x7C,0x04,0x18,0x04,0x7C,		//   ( 77)  m - 0x006D Latin Small Letter M
0x7C,0x08,0x04,0x04,0x78,		//   ( 78)  n - 0x006E Latin Small Letter N
0x38,0x44,0x44,0x44,0x38,		//   ( 79)  o - 0x006F Latin Small Letter O
0x7C,0x14,0x14,0x14,0x08,		//   ( 80)  p - 0x0070 Latin Small Letter P
0x08,0x14,0x14,0x18,0x7C,		//   ( 81)  q - 0x0071 Latin Small Letter Q
0x7C,0x08,0x04,0x04,0x08,		//   ( 82)  r - 0x0072 Latin Small Letter R
0x48,0x54,0x54,0x54,0x20,		//   ( 83)  s - 0x0073 Latin Small Letter S
0x04,0x3F,0x44,0x40,0x20,		//   ( 84)  t - 0x0074 Latin Small Letter T
0x3C,0x40,0x40,0x20,0x7C,		//   ( 85)  u - 0x0075 Latin Small Letter U
0x1C,0x20,0x40,0x20,0x1C,		//   ( 86)  v - 0x0076 Latin Small Letter V
0x3C,0x40,0x30,0x40,0x3C,		//   ( 87)  w - 0x0077 Latin Small Letter W
0x44,0x28,0x10,0x28,0x44,		//   ( 88)  x - 0x0078 Latin Small Letter X
0x0C,0x50,0x50,0x50,0x3C,		//   ( 89)  y - 0x0079 Latin Small Letter Y
0x44,0x64,0x54,0x4C,0x44,		//   ( 90)  z - 0x007A Latin Small Letter Z
0x00,0x08,0x36,0x41,0x00,		//   ( 91)  { - 0x007B Left Curly Bracket
0x00,0x00,0x7F,0x00,0x00,		//   ( 92)  | - 0x007C Vertical Line
0x00,0x41,0x36,0x08,0x00,		//   ( 93)  } - 0x007D Right Curly Bracket
0x02,0x01,0x02,0x04,0x02,		//   ( 94)  ~ - 0x007E Tilde
0x3E,0x55,0x55,0x41,0x22,		//   ( 95)  C - 0x0080 <Control>
0x00,0x00,0x00,0x00,0x00,		//   ( 96)    - 0x00A0 No-Break Space
0x00,0x00,0x79,0x00,0x00,		//   ( 97)  ! - 0x00A1 Inverted Exclamation Mark
0x18,0x24,0x74,0x2E,0x24,		//   ( 98)  c - 0x00A2 Cent Sign
0x48,0x7E,0x49,0x42,0x40,		//   ( 99)  L - 0x00A3 Pound Sign
0x5D,0x22,0x22,0x22,0x5D,		//   (100)  o - 0x00A4 Currency Sign
0x15,0x16,0x7C,0x16,0x15,		//   (101)  Y - 0x00A5 Yen Sign
0x00,0x00,0x77,0x00,0x00,		//   (102)  | - 0x00A6 Broken Bar
0x0A,0x55,0x55,0x55,0x28,		//   (103)    - 0x00A7 Section Sign
0x00,0x01,0x00,0x01,0x00,		//   (104)  " - 0x00A8 Diaeresis
0x00,0x0A,0x0D,0x0A,0x04,		//   (105)    - 0x00AA Feminine Ordinal Indicator
0x08,0x14,0x2A,0x14,0x22,		//   (106) << - 0x00AB Left-Pointing Double Angle Quotation Mark
0x04,0x04,0x04,0x04,0x1C,		//   (107)    - 0x00AC Not Sign
0x00,0x08,0x08,0x08,0x00,		//   (108)  - - 0x00AD Soft Hyphen
0x01,0x01,0x01,0x01,0x01,		//   (109)    - 0x00AF Macron
0x00,0x02,0x05,0x02,0x00,		//   (110)    - 0x00B0 Degree Sign
0x44,0x44,0x5F,0x44,0x44,		//   (111) +- - 0x00B1 Plus-Minus Sign
0x00,0x00,0x04,0x02,0x01,		//   (112)  ` - 0x00B4 Acute Accent
0x7E,0x20,0x20,0x10,0x3E,		//   (113)  u - 0x00B5 Micro Sign
0x06,0x0F,0x7F,0x00,0x7F,		//   (114)    - 0x00B6 Pilcrow Sign
0x00,0x18,0x18,0x00,0x00,		//   (115)  . - 0x00B7 Middle Dot
};

const unsigned char pic[28800];

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
    mPORTBSetPinsDigitalOut(BIT_14 | BIT_15); // -RES, -C/D
    mPORTDSetPinsDigitalOut(BIT_1); // Backlite

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

void lcd_show_color_string(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, unsigned int length, const char* p) {
    const unsigned int font_width = 5;
    const unsigned int font_height = 7;

    const char* q = p + length;
    while (p != q) {
        int glyph_id = *p++;
        if (glyph_id >= 0x20) {
            glyph_id -= 0x20;
        }
        glyph_id *= 5;
        if (glyph_id > sizeof(font_table_5x7)) {
            // non-printable (and out of bounds) characters are mapped to whitespace
            glyph_id = 0;
        }

        lcd_set_window(x, x + font_width-1, y, y+font_height-1);
        Write_Command(SSD1963_CMD_WRITE_MEMORY_START);

        int row;
        for (row = 0; row < font_height; row++) {
            int col;
            for (col = 0; col < font_width; col++) {
                const unsigned char glyph = font_table_5x7[glyph_id + col];
                uint32_t mask = (1 << row);
                bool visible = (glyph & mask);
                lcd_color_t color = visible ? foreground : background;
                SendData(color);
            }
        }

        x += font_width+1;
    }
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

void lcd_init(void) {
    init_SSD1963();
    black_frame_with_border();
}

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

//=======================================
const unsigned char pic[28800] = {//(320)*(240/8)*3
    0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC,
    0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5,
    0XE5, 0XE5, 0XE3, 0XE3, 0XE4, 0XE2, 0XE1, 0XE5, 0XE3, 0XE0, 0XE4, 0XE1, 0XDE, 0XE3, 0XDF, 0XDC,
    0XE1, 0XDE, 0XDA, 0XDF, 0XDC, 0XD8, 0XDC, 0XD9, 0XD5, 0XDB, 0XD6, 0XD3, 0XD9, 0XD5, 0XD0, 0XD6,
    0XD3, 0XCB, 0XD0, 0XCD, 0XC5, 0XCF, 0XCD, 0XC3, 0XCA, 0XC8, 0XBE, 0XC6, 0XC4, 0XBA, 0XC2, 0XBF,
    0XB5, 0XBD, 0XBA, 0XAE, 0XB9, 0XB6, 0XA7, 0XB2, 0XAD, 0X9B, 0XAC, 0XA8, 0X92, 0XA9, 0XA4, 0X8B,
    0XA4, 0X9E, 0X84, 0X9C, 0X95, 0X7A, 0X95, 0X92, 0X70, 0X8F, 0X8D, 0X6A, 0X89, 0X87, 0X62, 0X8F,
    0X8C, 0X5C, 0X81, 0X83, 0X40, 0X6E, 0X73, 0X18, 0X69, 0X71, 0X03, 0X6C, 0X77, 0X00, 0X6D, 0X79,
    0X00, 0X6D, 0X7A, 0X00, 0X70, 0X7C, 0X04, 0X68, 0X75, 0X00, 0X66, 0X73, 0X06, 0X5F, 0X6B, 0X08,
    0X4F, 0X59, 0X02, 0X4F, 0X5C, 0X01, 0X5C, 0X73, 0X02, 0X5A, 0X76, 0X00, 0X5A, 0X75, 0X00, 0X5C,
    0X7B, 0X02, 0X5F, 0X7F, 0X02, 0X62, 0X84, 0X02, 0X64, 0X87, 0X00, 0X66, 0X88, 0X02, 0X65, 0X88,
    0X00, 0X66, 0X8A, 0X01, 0X66, 0X8A, 0X01, 0X65, 0X89, 0X00, 0X67, 0X89, 0X00, 0X68, 0X8A, 0X00,
    0X6A, 0X8C, 0X01, 0X69, 0X8C, 0X00, 0X69, 0X8E, 0X00, 0X6B, 0X92, 0X02, 0X6A, 0X90, 0X00, 0X69,
    0X8F, 0X00, 0X69, 0X90, 0X00, 0X6E, 0X94, 0X01, 0X6F, 0X94, 0X00, 0X70, 0X96, 0X01, 0X6E, 0X95,
    0X00, 0X72, 0X98, 0X01, 0X75, 0X9A, 0X01, 0X78, 0X9C, 0X00, 0X7B, 0X9C, 0X00, 0X7B, 0X9E, 0X00,
    0X7C, 0X9F, 0X00, 0X82, 0XA2, 0X00, 0X89, 0XA7, 0X00, 0X8D, 0XAA, 0X00, 0X93, 0XAE, 0X00, 0X97,
    0XAF, 0X00, 0X9C, 0XB7, 0X03, 0X8E, 0XAC, 0X04, 0XB0, 0XC0, 0X5C, 0XF4, 0XF5, 0XDC, 0XF8, 0XF8,
    0XF2, 0XF0, 0XF3, 0XEE, 0XF4, 0XF4, 0XF2, 0XF4, 0XF2, 0XEF, 0XF5, 0XF4, 0XF0, 0XF5, 0XF4, 0XF0,
    0XF4, 0XF3, 0XF0, 0XF3, 0XF1, 0XF0, 0XF2, 0XF0, 0XEF, 0XF2, 0XF0, 0XF0, 0XF3, 0XF1, 0XF1, 0XF2,
    0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF,
    0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC,
    0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7, 0XE7, 0XE9,
    0XE7, 0XE6, 0XE7, 0XE5, 0XE4, 0XE6, 0XE3, 0XE3, 0XE4, 0XE2, 0XE0, 0XE4, 0XE1, 0XDE, 0XE3, 0XE0,
    0XDC, 0XE1, 0XDD, 0XD9, 0XDE, 0XD9, 0XD6, 0XDC, 0XD7, 0XD4, 0XD8, 0XD3, 0XD0, 0XD6, 0XD0, 0XCD,
    0XD1, 0XCA, 0XC7, 0XC9, 0XC3, 0XBE, 0XC3, 0XBD, 0XB7, 0XBA, 0XB3, 0XAC, 0XB3, 0XAB, 0XA4, 0XB2,
    0XAA, 0XA1, 0XB4, 0XAB, 0XA2, 0XB5, 0XAC, 0XA3, 0XB1, 0XA9, 0XA0, 0XB0, 0XAA, 0XA0, 0XB3, 0XAD,
    0XA5, 0X78, 0X78, 0X76, 0X53, 0X57, 0X57, 0X55, 0X59, 0X5A, 0X56, 0X5A, 0X5A, 0X4A, 0X51, 0X4E,
    0X42, 0X49, 0X47, 0X3D, 0X41, 0X43, 0X29, 0X30, 0X34, 0X28, 0X31, 0X3B, 0X22, 0X2A, 0X39, 0X24,
    0X2D, 0X40, 0X28, 0X34, 0X48, 0X27, 0X35, 0X49, 0X22, 0X31, 0X48, 0X25, 0X34, 0X4F, 0X23, 0X30,
    0X4C, 0X27, 0X32, 0X4E, 0X2C, 0X39, 0X55, 0X23, 0X31, 0X4D, 0X23, 0X31, 0X4D, 0X27, 0X35, 0X51,
    0X26, 0X30, 0X4E, 0X28, 0X35, 0X53, 0X27, 0X37, 0X55, 0X25, 0X35, 0X52, 0X1F, 0X2F, 0X4F, 0X38,
    0X4B, 0X6F, 0X88, 0XA1, 0XC6, 0XAE, 0XCA, 0XEE, 0X94, 0XB0, 0XD1, 0X4A, 0X60, 0X8A, 0X32, 0X46,
    0X75, 0X3B, 0X51, 0X7A, 0X4C, 0X63, 0X89, 0X58, 0X70, 0X94, 0X4A, 0X60, 0X84, 0X51, 0X67, 0X8B,
    0X5C, 0X6E, 0X91, 0XBC, 0XC4, 0XD1, 0XF6, 0XF9, 0XF4, 0XED, 0XEC, 0XED, 0XEC, 0XEE, 0XEF, 0XEE,
    0XED, 0XEF, 0XF1, 0XEE, 0XEF, 0XEC, 0XEF, 0XEE, 0XED, 0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XEE,
    0XEE, 0XEF, 0XEF, 0XEF, 0XF0, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF,
    0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEF, 0XF0, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF,
    0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEE, 0XF0, 0XEE, 0XED, 0XEF, 0XED, 0XEC,
    0XEE, 0XEE, 0XED, 0XEF, 0XED, 0XEC, 0XEE, 0XEB, 0XEA, 0XEC, 0XEB, 0XEA, 0XEC, 0XEA, 0XE9, 0XEB,
    0XE9, 0XE8, 0XEA, 0XE7, 0XE6, 0XE8, 0XE7, 0XE6, 0XE9, 0XE6, 0XE5, 0XE9, 0XE4, 0XE3, 0XE7, 0XE2,
    0XE1, 0XE5, 0XDE, 0XDD, 0XE2, 0XDA, 0XD8, 0XDE, 0XD9, 0XD7, 0XDC, 0XD1, 0XCE, 0XD7, 0XCE, 0XCA,
    0XD6, 0XC2, 0XBD, 0XCE, 0XBC, 0XB7, 0XCC, 0XBA, 0XB4, 0XCC, 0XB2, 0XAA, 0XC6, 0XAE, 0XA2, 0XC5,
    0XAA, 0X9D, 0XD0, 0X9E, 0X8F, 0XE0, 0X8C, 0X7C, 0XEA, 0X89, 0X76, 0XF4, 0X89, 0X74, 0XF4, 0X8A,
    0X72, 0XF6, 0X88, 0X6D, 0XFC, 0X85, 0X6D, 0XF8, 0X84, 0X6F, 0XF7, 0X6D, 0X4E, 0XEF, 0X85, 0X6D,
    0XF0, 0XAC, 0X99, 0XFE, 0X8C, 0X71, 0XF6, 0X77, 0X58, 0XF3, 0X7A, 0X59, 0XF9, 0X79, 0X56, 0XFB,
    0X7A, 0X57, 0XFC, 0X7B, 0X59, 0XFA, 0X7A, 0X58, 0XF8, 0X77, 0X55, 0XF8, 0X79, 0X56, 0XF9, 0X7E,
    0X5D, 0XFC, 0X77, 0X58, 0XF8, 0X73, 0X52, 0XFA, 0X77, 0X57, 0XFD, 0X76, 0X5A, 0XF7, 0X78, 0X59,
    0XF6, 0X79, 0X59, 0XF7, 0X7B, 0X5A, 0XFB, 0X78, 0X5A, 0XF6, 0X9B, 0X8D, 0XF3, 0XC3, 0XBD, 0XFE,
    0XB2, 0XA5, 0XF9, 0X89, 0X72, 0XF0, 0X75, 0X5C, 0XF3, 0X73, 0X5B, 0XF4, 0X7C, 0X62, 0XFC, 0X7A,
    0X5C, 0XFA, 0X7A, 0X58, 0XFB, 0X79, 0X56, 0XFB, 0X79, 0X56, 0XFB, 0X77, 0X55, 0XFA, 0X74, 0X53,
    0XFB, 0X72, 0X51, 0XFB, 0X77, 0X58, 0XFA, 0X7E, 0X60, 0XF9, 0X8C, 0X73, 0XF5, 0XC7, 0XBF, 0XF7,
    0XF3, 0XF6, 0XFB, 0XF3, 0XF2, 0XFA, 0XF2, 0XF0, 0XFB, 0XF3, 0XF2, 0XFC, 0XF2, 0XF0, 0XFA, 0XEF,
    0XEE, 0XF8, 0XF4, 0XF3, 0XFC, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF2, 0XF2, 0XFA, 0XEF, 0XF1,
    0XF9, 0XEF, 0XEF, 0XF8, 0XEF, 0XEE, 0XF7, 0XEF, 0XEE, 0XF7, 0XF0, 0XEF, 0XF6, 0XEF, 0XEF, 0XF5,
    0XEF, 0XEF, 0XF5, 0XF0, 0XEF, 0XF5, 0XF2, 0XF0, 0XF6, 0XF2, 0XF0, 0XF6, 0XF3, 0XF1, 0XF6, 0XF2,
    0XF1, 0XF5, 0XF2, 0XF1, 0XF5, 0XF4, 0XF3, 0XF7, 0XF2, 0XF1, 0XF5, 0XF3, 0XF2, 0XF3, 0XF1, 0XF0,
    0XF2, 0XF0, 0XEF, 0XF1, 0XF1, 0XF0, 0XF2, 0XF1, 0XF0, 0XF2, 0XF1, 0XF0, 0XF2, 0XF0, 0XEF, 0XF1,
    0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XF1, 0XF0, 0XF0, 0XF2,
    0XF0, 0XF0, 0XF1, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEE, 0XED, 0XED, 0XEC, 0XEC,
    0XEC, 0XEC, 0XEB, 0XEB, 0XEC, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XEC, 0XE8, 0XE9, 0XEA, 0XE7, 0XE7,
    0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEC, 0XEA, 0XEA, 0XEC,
    0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7,
    0XE7, 0XE7, 0XE5, 0XE5, 0XE5, 0XE3, 0XE3, 0XE5, 0XE3, 0XE3, 0XE3, 0XE2, 0XE1, 0XE3, 0XE0, 0XDE,
    0XE1, 0XDE, 0XDB, 0XDF, 0XDC, 0XD8, 0XDE, 0XDB, 0XD7, 0XDD, 0XD9, 0XD5, 0XDA, 0XD6, 0XD2, 0XD8,
    0XD5, 0XCE, 0XD6, 0XD3, 0XCB, 0XD2, 0XD0, 0XC6, 0XCE, 0XCC, 0XC2, 0XC9, 0XC7, 0XBD, 0XC5, 0XC3,
    0XB9, 0XC1, 0XBE, 0XB3, 0XBE, 0XB9, 0XAE, 0XB5, 0XB1, 0XA1, 0XB1, 0XAD, 0X9A, 0XAE, 0XA9, 0X94,
    0XA7, 0XA2, 0X8A, 0X9E, 0X98, 0X81, 0X9C, 0X97, 0X7A, 0X93, 0X8F, 0X6F, 0X8E, 0X89, 0X68, 0X8F,
    0X8A, 0X67, 0X8B, 0X87, 0X5B, 0X81, 0X82, 0X3F, 0X6E, 0X76, 0X15, 0X67, 0X73, 0X02, 0X6B, 0X76,
    0X05, 0X72, 0X7C, 0X0C, 0X74, 0X80, 0X0D, 0X72, 0X7F, 0X08, 0X66, 0X77, 0X00, 0X64, 0X73, 0X02,
    0X66, 0X73, 0X0A, 0X4C, 0X57, 0X00, 0X54, 0X65, 0X01, 0X62, 0X7A, 0X05, 0X57, 0X6F, 0X00, 0X56,
    0X70, 0X02, 0X5A, 0X78, 0X00, 0X61, 0X83, 0X01, 0X63, 0X85, 0X01, 0X61, 0X84, 0X00, 0X63, 0X86,
    0X01, 0X64, 0X87, 0X00, 0X65, 0X89, 0X01, 0X66, 0X89, 0X00, 0X69, 0X8A, 0X00, 0X69, 0X89, 0X00,
    0X6D, 0X8F, 0X01, 0X6B, 0X8F, 0X00, 0X6B, 0X8F, 0X00, 0X6B, 0X92, 0X02, 0X69, 0X90, 0X00, 0X6B,
    0X92, 0X01, 0X6B, 0X92, 0X01, 0X68, 0X8F, 0X00, 0X6D, 0X91, 0X01, 0X6C, 0X93, 0X01, 0X6D, 0X94,
    0X00, 0X70, 0X96, 0X01, 0X75, 0X9A, 0X01, 0X77, 0X9A, 0X00, 0X78, 0X9A, 0X00, 0X7C, 0X9F, 0X00,
    0X7E, 0XA0, 0X00, 0X7D, 0X9E, 0X00, 0X83, 0XA3, 0X01, 0X89, 0XA6, 0X00, 0X8E, 0XAB, 0X01, 0X91,
    0XAC, 0X00, 0X96, 0XB3, 0X00, 0X96, 0XB6, 0X01, 0X91, 0XAB, 0X0F, 0XBD, 0XC8, 0X6A, 0XF8, 0XF9,
    0XDC, 0XF3, 0XF7, 0XEF, 0XEE, 0XF3, 0XEF, 0XF3, 0XF3, 0XF1, 0XF5, 0XF3, 0XF0, 0XF4, 0XF3, 0XEF,
    0XF4, 0XF3, 0XEF, 0XF3, 0XF1, 0XF0, 0XF3, 0XF1, 0XF1, 0XF4, 0XF2, 0XF1, 0XF3, 0XF1, 0XF1, 0XF3,
    0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF,
    0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC,
    0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE7,
    0XE5, 0XE6, 0XE7, 0XE5, 0XE4, 0XE4, 0XE2, 0XE1, 0XE4, 0XE2, 0XE1, 0XE4, 0XE1, 0XDF, 0XE3, 0XE0,
    0XDC, 0XE1, 0XDC, 0XD9, 0XDF, 0XDA, 0XD7, 0XDB, 0XD6, 0XD3, 0XDA, 0XD5, 0XD2, 0XD6, 0XD1, 0XCE,
    0XD1, 0XCA, 0XC7, 0XCA, 0XC4, 0XC0, 0XC2, 0XBC, 0XB7, 0XBA, 0XB3, 0XAC, 0XB6, 0XAF, 0XA7, 0XB4,
    0XAB, 0XA3, 0XB1, 0XA8, 0X9F, 0XB1, 0XA8, 0X9F, 0XB0, 0XA8, 0X9F, 0XB3, 0XAB, 0XA3, 0XB3, 0XAD,
    0XA5, 0X76, 0X77, 0X73, 0X51, 0X56, 0X55, 0X56, 0X5A, 0X5B, 0X55, 0X59, 0X5A, 0X4C, 0X52, 0X50,
    0X3A, 0X40, 0X3F, 0X38, 0X3E, 0X40, 0X2D, 0X34, 0X39, 0X2B, 0X33, 0X3E, 0X23, 0X2C, 0X3B, 0X25,
    0X2F, 0X42, 0X23, 0X30, 0X43, 0X24, 0X32, 0X47, 0X23, 0X31, 0X48, 0X22, 0X2F, 0X49, 0X25, 0X30,
    0X4C, 0X29, 0X36, 0X51, 0X2A, 0X36, 0X52, 0X26, 0X34, 0X50, 0X2A, 0X38, 0X53, 0X29, 0X36, 0X52,
    0X28, 0X33, 0X51, 0X25, 0X33, 0X4F, 0X3E, 0X50, 0X6B, 0X21, 0X31, 0X4E, 0X17, 0X27, 0X49, 0X51,
    0X65, 0X8B, 0XA3, 0XBD, 0XE5, 0XA8, 0XC6, 0XEE, 0XA7, 0XC8, 0XEC, 0X61, 0X79, 0XA5, 0X2A, 0X3F,
    0X6E, 0X43, 0X58, 0X83, 0X4C, 0X63, 0X8A, 0X57, 0X6E, 0X94, 0X49, 0X5F, 0X83, 0X4E, 0X64, 0X88,
    0X5A, 0X6C, 0X8D, 0XB6, 0XBE, 0XCA, 0XF5, 0XF8, 0XF3, 0XEC, 0XEB, 0XED, 0XEC, 0XEE, 0XEE, 0XF0,
    0XEF, 0XF0, 0XF3, 0XF0, 0XF1, 0XED, 0XF0, 0XEF, 0XED, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XED, 0XED,
    0XED, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEF, 0XF0, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF,
    0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEE,
    0XEE, 0XEE, 0XEE, 0XEF, 0XEE, 0XED, 0XED, 0XEE, 0XED, 0XEC, 0XEE, 0XED, 0XEC, 0XEE, 0XED, 0XEC,
    0XEE, 0XEC, 0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XEA, 0XE9, 0XEB, 0XEA, 0XE9, 0XEA, 0XE9, 0XE8, 0XEA,
    0XE9, 0XE8, 0XEA, 0XE8, 0XE7, 0XEA, 0XE7, 0XE6, 0XEA, 0XE4, 0XE3, 0XE7, 0XE2, 0XE1, 0XE5, 0XE1,
    0XE0, 0XE3, 0XDD, 0XDB, 0XE1, 0XD8, 0XD6, 0XDC, 0XD2, 0XD0, 0XD7, 0XCD, 0XCA, 0XD4, 0XC9, 0XC4,
    0XD2, 0XC2, 0XBC, 0XCF, 0XBC, 0XB6, 0XCC, 0XB3, 0XAD, 0XC7, 0XB2, 0XA7, 0XC6, 0XAB, 0XA1, 0XC8,
    0XA3, 0X96, 0XD9, 0X92, 0X81, 0XE8, 0X8D, 0X7A, 0XF6, 0X8C, 0X76, 0XF9, 0X89, 0X6F, 0XF5, 0X87,
    0X6E, 0XF5, 0X87, 0X6C, 0XFB, 0X88, 0X70, 0XFA, 0X78, 0X5D, 0XF6, 0X73, 0X55, 0XEF, 0XA3, 0X91,
    0XFD, 0X9D, 0X87, 0XFB, 0X7F, 0X5D, 0XF6, 0X7A, 0X5A, 0XF9, 0X78, 0X57, 0XF9, 0X7A, 0X57, 0XFC,
    0X79, 0X57, 0XFB, 0X7A, 0X58, 0XFA, 0X7A, 0X59, 0XF9, 0X78, 0X57, 0XF8, 0X79, 0X59, 0XF7, 0X7A,
    0X5B, 0XF9, 0X76, 0X56, 0XFB, 0X72, 0X53, 0XFC, 0X73, 0X57, 0XFC, 0X75, 0X5B, 0XF8, 0X75, 0X5B,
    0XF7, 0X7A, 0X5B, 0XFC, 0X78, 0X58, 0XF5, 0X94, 0X80, 0XF5, 0XBD, 0XB5, 0XFC, 0XC5, 0XBC, 0XFC,
    0XAA, 0X99, 0XF5, 0X87, 0X6B, 0XF8, 0X77, 0X5C, 0XF9, 0X7A, 0X60, 0XF8, 0X7B, 0X5C, 0XF9, 0X7A,
    0X59, 0XF9, 0X7A, 0X56, 0XFA, 0X77, 0X54, 0XF9, 0X77, 0X54, 0XFB, 0X77, 0X55, 0XFB, 0X72, 0X53,
    0XFB, 0X72, 0X56, 0XFB, 0X78, 0X59, 0XF8, 0X87, 0X69, 0XF5, 0XAF, 0X9E, 0XF1, 0XEB, 0XEA, 0XFC,
    0XF2, 0XF4, 0XFA, 0XF1, 0XF0, 0XFD, 0XF2, 0XF1, 0XFC, 0XF1, 0XF0, 0XFA, 0XF3, 0XF2, 0XFC, 0XF2,
    0XF1, 0XFA, 0XF2, 0XF1, 0XFA, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XEF, 0XF0,
    0XF8, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF6, 0XF0, 0XF0, 0XF6, 0XF0, 0XF0, 0XF6,
    0XF1, 0XF0, 0XF6, 0XF1, 0XF0, 0XF6, 0XF2, 0XF0, 0XF6, 0XF2, 0XF0, 0XF5, 0XF3, 0XF2, 0XF6, 0XF1,
    0XF0, 0XF4, 0XF2, 0XF1, 0XF5, 0XF3, 0XF2, 0XF6, 0XF2, 0XF1, 0XF5, 0XF2, 0XF1, 0XF3, 0XF1, 0XF0,
    0XF2, 0XF1, 0XF0, 0XF2, 0XF0, 0XEF, 0XF1, 0XF1, 0XF0, 0XF2, 0XF1, 0XF0, 0XF2, 0XEF, 0XEE, 0XF0,
    0XEF, 0XEE, 0XF0, 0XF0, 0XEF, 0XF1, 0XEF, 0XEE, 0XF0, 0XF0, 0XEE, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1,
    0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEC, 0XEB,
    0XEB, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XEC, 0XE8, 0XE9, 0XEA, 0XE5, 0XE6, 0XE9, 0XE4, 0XE5,
    0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XED,
    0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XEA, 0XE8,
    0XE8, 0XE8, 0XE6, 0XE6, 0XE7, 0XE4, 0XE6, 0XE6, 0XE4, 0XE4, 0XE3, 0XE1, 0XE1, 0XE3, 0XE0, 0XDF,
    0XE4, 0XE0, 0XDE, 0XE2, 0XDF, 0XDB, 0XE0, 0XDD, 0XD9, 0XDE, 0XDB, 0XD6, 0XDC, 0XD9, 0XD4, 0XD8,
    0XD6, 0XD0, 0XD8, 0XD5, 0XCD, 0XD4, 0XD3, 0XC9, 0XD2, 0XD0, 0XC6, 0XCE, 0XCC, 0XC2, 0XC9, 0XC7,
    0XBD, 0XC3, 0XC2, 0XB7, 0XC2, 0XBE, 0XB3, 0XBD, 0XB9, 0XAC, 0XB7, 0XB3, 0XA4, 0XB1, 0XAC, 0X9A,
    0XAC, 0XA7, 0X93, 0XA4, 0X9F, 0X8B, 0X9F, 0X98, 0X82, 0X99, 0X94, 0X78, 0X93, 0X90, 0X6E, 0X8F,
    0X8C, 0X6A, 0X8D, 0X88, 0X64, 0X8C, 0X8A, 0X58, 0X7C, 0X83, 0X35, 0X68, 0X73, 0X0F, 0X6A, 0X76,
    0X0A, 0X6F, 0X7A, 0X10, 0X7B, 0X85, 0X1B, 0X7B, 0X87, 0X15, 0X71, 0X7F, 0X07, 0X6A, 0X79, 0X01,
    0X6A, 0X79, 0X03, 0X5F, 0X6D, 0X03, 0X50, 0X5C, 0X00, 0X58, 0X67, 0X04, 0X5B, 0X71, 0X05, 0X55,
    0X6C, 0X01, 0X58, 0X74, 0X00, 0X5E, 0X7F, 0X01, 0X60, 0X81, 0X01, 0X61, 0X83, 0X01, 0X63, 0X87,
    0X00, 0X64, 0X87, 0X00, 0X64, 0X88, 0X00, 0X68, 0X8B, 0X00, 0X6C, 0X8E, 0X02, 0X70, 0X90, 0X05,
    0X74, 0X94, 0X05, 0X72, 0X95, 0X03, 0X6C, 0X90, 0X01, 0X6A, 0X8F, 0X00, 0X6A, 0X91, 0X01, 0X6B,
    0X92, 0X01, 0X6A, 0X91, 0X02, 0X69, 0X8F, 0X01, 0X6B, 0X8F, 0X01, 0X6A, 0X91, 0X01, 0X6D, 0X94,
    0X02, 0X6E, 0X95, 0X01, 0X72, 0X97, 0X00, 0X75, 0X98, 0X00, 0X7C, 0X9C, 0X02, 0X7D, 0XA1, 0X02,
    0X7E, 0XA1, 0X01, 0X7C, 0X9E, 0X00, 0X7E, 0XA0, 0X00, 0X82, 0XA1, 0X00, 0X88, 0XA6, 0X00, 0X8F,
    0XAE, 0X01, 0X92, 0XAF, 0X02, 0X94, 0XB1, 0X02, 0X96, 0XB2, 0X00, 0X95, 0XAC, 0X14, 0XC5, 0XCF,
    0X83, 0XF8, 0XF9, 0XEC, 0XF2, 0XF5, 0XF0, 0XF3, 0XF4, 0XED, 0XF6, 0XF5, 0XF1, 0XF3, 0XF2, 0XEE,
    0XF4, 0XF3, 0XEF, 0XF2, 0XF1, 0XEE, 0XF4, 0XF2, 0XF1, 0XF5, 0XF3, 0XF2, 0XF2, 0XF0, 0XF1, 0XF2,
    0XF0, 0XF0, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF,
    0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC,
    0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE9,
    0XE7, 0XE7, 0XE6, 0XE4, 0XE4, 0XE5, 0XE3, 0XE2, 0XE5, 0XE3, 0XE2, 0XE4, 0XE1, 0XDF, 0XE2, 0XDF,
    0XDC, 0XE0, 0XDC, 0XD8, 0XDF, 0XDA, 0XD7, 0XDD, 0XD8, 0XD5, 0XDA, 0XD5, 0XD2, 0XD5, 0XD0, 0XCD,
    0XD1, 0XCC, 0XC9, 0XC9, 0XC4, 0XBF, 0XC5, 0XBF, 0XB9, 0XBB, 0XB5, 0XAE, 0XB3, 0XAB, 0XA5, 0XB4,
    0XAC, 0XA4, 0XB0, 0XA7, 0X9E, 0XB2, 0XA9, 0XA0, 0XB3, 0XAC, 0XA2, 0XB2, 0XAB, 0XA3, 0XB2, 0XAB,
    0XA5, 0X80, 0X82, 0X7E, 0X54, 0X59, 0X58, 0X52, 0X56, 0X57, 0X54, 0X59, 0X59, 0X48, 0X4E, 0X4D,
    0X3A, 0X40, 0X3F, 0X38, 0X40, 0X41, 0X29, 0X2F, 0X35, 0X2A, 0X31, 0X3C, 0X22, 0X2A, 0X3A, 0X22,
    0X2C, 0X40, 0X29, 0X36, 0X4B, 0X24, 0X32, 0X47, 0X24, 0X30, 0X47, 0X28, 0X31, 0X4B, 0X2C, 0X37,
    0X53, 0X2E, 0X3A, 0X56, 0X2A, 0X36, 0X52, 0X27, 0X35, 0X51, 0X26, 0X34, 0X50, 0X2B, 0X39, 0X54,
    0X28, 0X34, 0X52, 0X26, 0X34, 0X50, 0X25, 0X34, 0X4F, 0X2E, 0X3D, 0X5A, 0X3C, 0X4C, 0X6F, 0X66,
    0X7B, 0XA5, 0XAA, 0XC5, 0XF2, 0XA3, 0XC2, 0XED, 0XAF, 0XD0, 0XF7, 0X83, 0X9E, 0XC9, 0X31, 0X48,
    0X76, 0X49, 0X5F, 0X8B, 0X4A, 0X60, 0X89, 0X59, 0X70, 0X96, 0X4A, 0X61, 0X85, 0X4D, 0X65, 0X88,
    0X58, 0X6A, 0X8B, 0XB5, 0XBD, 0XCA, 0XF5, 0XF7, 0XF4, 0XEC, 0XEB, 0XEE, 0XED, 0XEF, 0XEF, 0XEF,
    0XEE, 0XEF, 0XF1, 0XEE, 0XEF, 0XED, 0XEF, 0XEE, 0XEE, 0XEF, 0XEF, 0XF0, 0XF0, 0XF0, 0XEF, 0XEF,
    0XEF, 0XEF, 0XEF, 0XEF, 0XED, 0XED, 0XED, 0XEE, 0XEE, 0XEE, 0XF0, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF,
    0XF0, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XED, 0XED, 0XED, 0XED,
    0XED, 0XED, 0XEE, 0XEF, 0XEE, 0XED, 0XEC, 0XEE, 0XEB, 0XEA, 0XED, 0XEB, 0XEA, 0XEC, 0XEC, 0XEB,
    0XED, 0XEC, 0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XEA, 0XE9, 0XEB, 0XE9, 0XE8, 0XEA, 0XE8, 0XE7, 0XEA,
    0XE9, 0XE8, 0XEB, 0XE8, 0XE7, 0XEB, 0XE4, 0XE3, 0XE8, 0XE3, 0XE3, 0XE6, 0XE2, 0XE1, 0XE6, 0XDE,
    0XDD, 0XE2, 0XDA, 0XD8, 0XDD, 0XD6, 0XD4, 0XDB, 0XCF, 0XCC, 0XD5, 0XC9, 0XC5, 0XD1, 0XC5, 0XC0,
    0XD0, 0XC0, 0XB9, 0XCE, 0XB7, 0XB1, 0XCA, 0XB1, 0XA9, 0XC6, 0XAD, 0XA2, 0XC5, 0XA5, 0X9B, 0XCF,
    0X99, 0X8A, 0XE3, 0X8E, 0X7C, 0XF3, 0X8B, 0X77, 0XF6, 0X8A, 0X73, 0XF4, 0X89, 0X6D, 0XF6, 0X89,
    0X70, 0XF9, 0X87, 0X70, 0XFA, 0X82, 0X65, 0XFB, 0X6B, 0X4B, 0XF0, 0X97, 0X82, 0XF9, 0XA7, 0X97,
    0XFE, 0X8A, 0X6D, 0XF6, 0X7C, 0X58, 0XF9, 0X7A, 0X5A, 0XFB, 0X78, 0X56, 0XFB, 0X78, 0X55, 0XFD,
    0X78, 0X56, 0XFC, 0X79, 0X58, 0XFB, 0X77, 0X57, 0XF9, 0X79, 0X59, 0XFA, 0X79, 0X59, 0XF9, 0X75,
    0X56, 0XF7, 0X75, 0X57, 0XFB, 0X72, 0X56, 0XFA, 0X73, 0X59, 0XF9, 0X74, 0X5A, 0XF9, 0X74, 0X59,
    0XFB, 0X77, 0X58, 0XFB, 0X86, 0X6E, 0XEE, 0XBB, 0XB1, 0XFB, 0XC1, 0XB5, 0XFC, 0XB8, 0XAA, 0XF5,
    0XAA, 0X97, 0XF7, 0X80, 0X61, 0XF7, 0X79, 0X5E, 0XFA, 0X81, 0X64, 0XFB, 0X7C, 0X5A, 0XF9, 0X79,
    0X57, 0XF8, 0X7A, 0X57, 0XFB, 0X79, 0X55, 0XFB, 0X77, 0X54, 0XFB, 0X73, 0X52, 0XF9, 0X74, 0X56,
    0XFB, 0X78, 0X5E, 0XFB, 0X81, 0X64, 0XF5, 0X9C, 0X84, 0XF0, 0XDC, 0XD3, 0XF9, 0XF5, 0XF4, 0XFD,
    0XF1, 0XEF, 0XFC, 0XF1, 0XF0, 0XFD, 0XF2, 0XF1, 0XFC, 0XF1, 0XF0, 0XFB, 0XF1, 0XF0, 0XFA, 0XF3,
    0XF2, 0XFA, 0XF1, 0XF0, 0XF9, 0XF2, 0XF1, 0XFA, 0XF1, 0XF0, 0XF9, 0XF0, 0XEF, 0XF7, 0XF0, 0XEF,
    0XF8, 0XEF, 0XEE, 0XF7, 0XF0, 0XEF, 0XF6, 0XF0, 0XF0, 0XF6, 0XEF, 0XEF, 0XF5, 0XF1, 0XEF, 0XF5,
    0XF2, 0XF0, 0XF6, 0XF2, 0XF0, 0XF6, 0XF2, 0XF1, 0XF6, 0XF2, 0XF1, 0XF5, 0XF2, 0XF1, 0XF5, 0XF1,
    0XF0, 0XF4, 0XF2, 0XF1, 0XF4, 0XF1, 0XF0, 0XF3, 0XF2, 0XF1, 0XF3, 0XF1, 0XF0, 0XF2, 0XF0, 0XEF,
    0XF1, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XF1, 0XF0, 0XF2, 0XF0, 0XEF, 0XF1,
    0XEF, 0XEE, 0XF0, 0XF1, 0XF0, 0XF2, 0XF0, 0XEE, 0XF0, 0XF0, 0XED, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0,
    0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC, 0XEB,
    0XEB, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE9, 0XE5, 0XE6, 0XE9, 0XE3, 0XE5, 0XE8, 0XE2, 0XE3,
    0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE,
    0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7,
    0XE7, 0XE8, 0XE6, 0XE6, 0XE7, 0XE4, 0XE7, 0XE5, 0XE2, 0XE4, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2,
    0XE4, 0XE0, 0XE0, 0XE3, 0XDF, 0XDD, 0XE1, 0XDE, 0XDB, 0XDE, 0XDC, 0XD9, 0XDC, 0XDA, 0XD7, 0XDB,
    0XD9, 0XD4, 0XDA, 0XD7, 0XD1, 0XD6, 0XD4, 0XCC, 0XD3, 0XD1, 0XC8, 0XD2, 0XCF, 0XC7, 0XCD, 0XCB,
    0XC1, 0XCB, 0XC9, 0XBF, 0XC5, 0XC3, 0XB8, 0XC1, 0XBE, 0XB3, 0XBC, 0XB8, 0XAC, 0XB7, 0XB3, 0XA4,
    0XB0, 0XAB, 0X9A, 0XAA, 0XA4, 0X92, 0XA5, 0X9D, 0X8C, 0X9F, 0X9A, 0X81, 0X94, 0X92, 0X70, 0X90,
    0X8F, 0X6A, 0X8F, 0X8D, 0X68, 0X8B, 0X89, 0X5C, 0X88, 0X8C, 0X4F, 0X79, 0X82, 0X2E, 0X69, 0X76,
    0X0B, 0X6B, 0X77, 0X0C, 0X74, 0X7D, 0X14, 0X72, 0X7B, 0X0F, 0X73, 0X7D, 0X0D, 0X6E, 0X7A, 0X06,
    0X6B, 0X78, 0X03, 0X66, 0X73, 0X00, 0X60, 0X6A, 0X04, 0X4F, 0X58, 0X00, 0X58, 0X67, 0X03, 0X5C,
    0X74, 0X02, 0X57, 0X71, 0X00, 0X5A, 0X75, 0X01, 0X5D, 0X7B, 0X00, 0X61, 0X82, 0X00, 0X64, 0X87,
    0X02, 0X64, 0X88, 0X00, 0X64, 0X87, 0X00, 0X69, 0X8C, 0X01, 0X6F, 0X91, 0X05, 0X6F, 0X91, 0X04,
    0X6E, 0X90, 0X02, 0X6D, 0X90, 0X00, 0X6B, 0X8F, 0X00, 0X6C, 0X90, 0X00, 0X6A, 0X91, 0X00, 0X69,
    0X90, 0X00, 0X69, 0X8F, 0X01, 0X6A, 0X8E, 0X01, 0X69, 0X8F, 0X00, 0X69, 0X90, 0X00, 0X6A, 0X91,
    0X01, 0X6E, 0X95, 0X02, 0X72, 0X98, 0X01, 0X75, 0X99, 0X00, 0X7B, 0X9B, 0X01, 0X7B, 0X9C, 0X01,
    0X7B, 0X9E, 0X00, 0X7B, 0X9E, 0X01, 0X7A, 0X9E, 0X00, 0X7C, 0X9E, 0X00, 0X81, 0XA3, 0X00, 0X87,
    0XA8, 0X01, 0X8D, 0XAB, 0X03, 0X93, 0XB1, 0X04, 0X97, 0XB3, 0X01, 0X97, 0XB2, 0X04, 0X93, 0XAA,
    0X21, 0XCE, 0XD6, 0X9A, 0XFC, 0XFA, 0XF1, 0XF5, 0XF3, 0XEF, 0XF5, 0XF4, 0XEF, 0XF4, 0XF3, 0XEF,
    0XF4, 0XF3, 0XEF, 0XF4, 0XF3, 0XEF, 0XF4, 0XF2, 0XF1, 0XF3, 0XF1, 0XF0, 0XF3, 0XF1, 0XF0, 0XF2,
    0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF0, 0XEE,
    0XEE, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEF, 0XED, 0XED,
    0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE8,
    0XE6, 0XE6, 0XE5, 0XE3, 0XE3, 0XE5, 0XE3, 0XE3, 0XE4, 0XE3, 0XE1, 0XE3, 0XE0, 0XDF, 0XE2, 0XDF,
    0XDC, 0XE2, 0XDD, 0XDA, 0XE0, 0XDC, 0XD8, 0XDC, 0XD7, 0XD4, 0XDB, 0XD5, 0XD2, 0XD5, 0XD0, 0XCD,
    0XCF, 0XCB, 0XC7, 0XC8, 0XC4, 0XBF, 0XC4, 0XBF, 0XBA, 0XBC, 0XB6, 0XAF, 0XB8, 0XB0, 0XAA, 0XB4,
    0XAB, 0XA4, 0XB3, 0XAA, 0XA1, 0XB3, 0XAA, 0XA1, 0XB1, 0XA9, 0XA1, 0XB3, 0XAB, 0XA4, 0XB4, 0XAE,
    0XA8, 0X85, 0X86, 0X83, 0X5C, 0X62, 0X61, 0X5D, 0X61, 0X61, 0X5E, 0X64, 0X64, 0X45, 0X4B, 0X4A,
    0X32, 0X3A, 0X39, 0X33, 0X3A, 0X3C, 0X3B, 0X41, 0X48, 0X33, 0X3A, 0X45, 0X26, 0X2F, 0X40, 0X2A,
    0X37, 0X4C, 0X2C, 0X3A, 0X51, 0X40, 0X4D, 0X64, 0X2E, 0X39, 0X51, 0X2B, 0X32, 0X4D, 0X2B, 0X34,
    0X50, 0X2D, 0X39, 0X55, 0X26, 0X33, 0X4F, 0X26, 0X33, 0X4F, 0X23, 0X33, 0X4E, 0X25, 0X34, 0X50,
    0X28, 0X36, 0X53, 0X25, 0X33, 0X4F, 0X23, 0X31, 0X4C, 0X36, 0X45, 0X64, 0X4D, 0X5E, 0X85, 0X3F,
    0X57, 0X84, 0X81, 0X9F, 0XCF, 0XA7, 0XC8, 0XF6, 0XAC, 0XCC, 0XF5, 0XAC, 0XC6, 0XF1, 0X4A, 0X63,
    0X90, 0X44, 0X5C, 0X87, 0X47, 0X5E, 0X87, 0X54, 0X6A, 0X92, 0X4A, 0X61, 0X86, 0X4F, 0X66, 0X8C,
    0X56, 0X6A, 0X8B, 0XB2, 0XBA, 0XC8, 0XF4, 0XF6, 0XF4, 0XEC, 0XEB, 0XEE, 0XEC, 0XEE, 0XEF, 0XEE,
    0XED, 0XEF, 0XF1, 0XEE, 0XEF, 0XED, 0XEF, 0XEE, 0XEE, 0XEF, 0XEF, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0,
    0XF0, 0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF,
    0XF0, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XEE,
    0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XED, 0XEC, 0XEE, 0XEC, 0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XEC, 0XEB,
    0XED, 0XEB, 0XEA, 0XEC, 0XEB, 0XEA, 0XEC, 0XE8, 0XE7, 0XE9, 0XE8, 0XE7, 0XEA, 0XE7, 0XE6, 0XEB,
    0XE7, 0XE6, 0XEA, 0XE7, 0XE6, 0XEA, 0XE4, 0XE4, 0XE7, 0XE1, 0XE0, 0XE5, 0XDE, 0XDD, 0XE2, 0XDC,
    0XDA, 0XE1, 0XD7, 0XD5, 0XDC, 0XD2, 0XD0, 0XD8, 0XCC, 0XC8, 0XD2, 0XC7, 0XC2, 0XD0, 0XC1, 0XBB,
    0XCD, 0XBC, 0XB4, 0XCC, 0XB2, 0XAA, 0XC8, 0XAD, 0XA3, 0XC5, 0XAA, 0X9E, 0XCC, 0XA1, 0X92, 0XDD,
    0X90, 0X7D, 0XEC, 0X8D, 0X79, 0XF8, 0X88, 0X74, 0XF1, 0X8A, 0X75, 0XF3, 0X89, 0X6E, 0XF9, 0X88,
    0X70, 0XF7, 0X86, 0X6E, 0XFA, 0X6F, 0X4A, 0XF5, 0X7F, 0X63, 0XF2, 0XA9, 0X9A, 0XFE, 0X8F, 0X79,
    0XF5, 0X7A, 0X5A, 0XF2, 0X7B, 0X5A, 0XFB, 0X78, 0X5A, 0XFC, 0X76, 0X57, 0XFC, 0X74, 0X56, 0XFC,
    0X76, 0X57, 0XFC, 0X75, 0X57, 0XFA, 0X75, 0X57, 0XFA, 0X78, 0X5A, 0XFC, 0X78, 0X58, 0XFB, 0X73,
    0X54, 0XF9, 0X74, 0X57, 0XFA, 0X75, 0X5C, 0XF9, 0X74, 0X5B, 0XF8, 0X76, 0X5A, 0XFB, 0X77, 0X58,
    0XFD, 0X77, 0X5B, 0XF1, 0XAB, 0X9B, 0XF5, 0XC6, 0XBC, 0XFD, 0XBB, 0XAC, 0XFA, 0XB5, 0XA8, 0XFA,
    0X9B, 0X86, 0XF7, 0X7B, 0X5C, 0XF8, 0X7B, 0X5F, 0XF9, 0X7D, 0X5E, 0XF7, 0X7B, 0X59, 0XF8, 0X79,
    0X56, 0XF8, 0X78, 0X56, 0XFA, 0X76, 0X54, 0XFB, 0X78, 0X55, 0XFC, 0X79, 0X58, 0XFC, 0X77, 0X59,
    0XFB, 0X78, 0X5B, 0XF8, 0X8A, 0X6E, 0XF3, 0XBF, 0XB2, 0XF1, 0XF5, 0XF2, 0XFE, 0XF2, 0XEE, 0XFB,
    0XF2, 0XEF, 0XFB, 0XF0, 0XF2, 0XF9, 0XF1, 0XF1, 0XF9, 0XF1, 0XF0, 0XFA, 0XF1, 0XF0, 0XF9, 0XF3,
    0XF2, 0XFB, 0XF1, 0XF0, 0XF9, 0XF2, 0XF1, 0XFA, 0XF1, 0XF0, 0XF9, 0XEF, 0XEF, 0XF6, 0XF0, 0XEF,
    0XF6, 0XEE, 0XEE, 0XF5, 0XEE, 0XEE, 0XF4, 0XEF, 0XEE, 0XF4, 0XF1, 0XEF, 0XF5, 0XF1, 0XEF, 0XF5,
    0XF1, 0XF0, 0XF5, 0XF3, 0XF1, 0XF6, 0XF4, 0XF3, 0XF6, 0XF3, 0XF2, 0XF6, 0XF1, 0XF0, 0XF5, 0XF2,
    0XF1, 0XF5, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XF1, 0XF1, 0XF0, 0XF1, 0XF1, 0XF0, 0XF2, 0XEF, 0XEE,
    0XF0, 0XF0, 0XEF, 0XF1, 0XF1, 0XF0, 0XF2, 0XEF, 0XEE, 0XF0, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1,
    0XEF, 0XEE, 0XF0, 0XF1, 0XEE, 0XF0, 0XF0, 0XED, 0XEF, 0XF0, 0XED, 0XEF, 0XEF, 0XED, 0XED, 0XEF,
    0XED, 0XED, 0XED, 0XEA, 0XEA, 0XED, 0XEA, 0XEA, 0XED, 0XE9, 0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7,
    0XE7, 0XE8, 0XE7, 0XE6, 0XE7, 0XE5, 0XE5, 0XE7, 0XE3, 0XE3, 0XE6, 0XE1, 0XE2, 0XE5, 0XDE, 0XDF,
    0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE,
    0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7,
    0XE7, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE7, 0XE4, 0XE5, 0XE7, 0XE5, 0XE5, 0XE4, 0XE3, 0XE3,
    0XE4, 0XE2, 0XE2, 0XE3, 0XDF, 0XDF, 0XE2, 0XDE, 0XDE, 0XE0, 0XDE, 0XDE, 0XDD, 0XDB, 0XDA, 0XDB,
    0XDA, 0XD7, 0XDB, 0XDA, 0XD5, 0XD8, 0XD6, 0XD0, 0XD6, 0XD3, 0XCD, 0XD4, 0XD0, 0XC9, 0XCF, 0XCC,
    0XC4, 0XCB, 0XC9, 0XBF, 0XC6, 0XC4, 0XBA, 0XC3, 0XC1, 0XB7, 0XBF, 0XBB, 0XB1, 0XBB, 0XB7, 0XAB,
    0XB5, 0XB1, 0XA2, 0XAC, 0XA9, 0X98, 0XA9, 0XA3, 0X91, 0XA3, 0X9E, 0X87, 0X9B, 0X99, 0X7A, 0X94,
    0X93, 0X71, 0X8C, 0X8B, 0X67, 0X8D, 0X8C, 0X64, 0X8A, 0X8A, 0X5B, 0X8A, 0X8D, 0X4E, 0X75, 0X7D,
    0X25, 0X69, 0X74, 0X0F, 0X6E, 0X79, 0X0C, 0X6D, 0X77, 0X08, 0X76, 0X7D, 0X11, 0X70, 0X78, 0X0A,
    0X72, 0X7C, 0X07, 0X6D, 0X78, 0X03, 0X6E, 0X77, 0X08, 0X5A, 0X61, 0X02, 0X4D, 0X58, 0X00, 0X5A,
    0X6E, 0X01, 0X5C, 0X72, 0X04, 0X52, 0X69, 0X00, 0X5C, 0X77, 0X00, 0X61, 0X7E, 0X00, 0X62, 0X81,
    0X02, 0X64, 0X85, 0X01, 0X63, 0X85, 0X00, 0X67, 0X8A, 0X00, 0X6A, 0X8B, 0X01, 0X69, 0X8A, 0X00,
    0X6A, 0X8C, 0X00, 0X6A, 0X8D, 0X00, 0X69, 0X8C, 0X00, 0X6B, 0X8E, 0X00, 0X6C, 0X90, 0X02, 0X6B,
    0X8F, 0X01, 0X6C, 0X90, 0X04, 0X6B, 0X8E, 0X01, 0X69, 0X90, 0X00, 0X69, 0X90, 0X00, 0X69, 0X90,
    0X00, 0X6F, 0X95, 0X02, 0X72, 0X97, 0X02, 0X73, 0X97, 0X00, 0X76, 0X97, 0X00, 0X76, 0X97, 0X00,
    0X7A, 0X9C, 0X02, 0X7B, 0X9F, 0X02, 0X79, 0XA0, 0X01, 0X7A, 0XA0, 0X00, 0X7C, 0X9F, 0X00, 0X81,
    0XA3, 0X01, 0X86, 0XA6, 0X02, 0X8D, 0XAB, 0X04, 0X8F, 0XAD, 0X02, 0X96, 0XB5, 0X01, 0X95, 0XB3,
    0X02, 0X99, 0XAE, 0X27, 0XDA, 0XDE, 0XA6, 0XFE, 0XFA, 0XF2, 0XF4, 0XF3, 0XEE, 0XF4, 0XF3, 0XEE,
    0XF4, 0XF3, 0XEF, 0XF4, 0XF3, 0XEF, 0XF3, 0XF1, 0XF0, 0XF3, 0XF1, 0XF0, 0XF3, 0XF1, 0XF0, 0XF3,
    0XF1, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF0, 0XEE,
    0XEE, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC,
    0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE8,
    0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE3, 0XE0, 0XDF, 0XE2, 0XDE,
    0XDD, 0XE1, 0XDD, 0XDA, 0XDF, 0XDC, 0XD8, 0XDC, 0XD9, 0XD5, 0XD9, 0XD4, 0XD1, 0XD5, 0XD0, 0XCD,
    0XD1, 0XCC, 0XC9, 0XCB, 0XC7, 0XC2, 0XBF, 0XBB, 0XB6, 0XB9, 0XB5, 0XAD, 0XB8, 0XB0, 0XA9, 0XB2,
    0XA9, 0XA3, 0XB5, 0XAB, 0XA3, 0XB4, 0XAB, 0XA2, 0XB3, 0XAB, 0XA3, 0XB4, 0XAC, 0XA5, 0XB6, 0XB0,
    0XA9, 0X7D, 0X7E, 0X7A, 0X5B, 0X60, 0X5F, 0X55, 0X5A, 0X5B, 0X55, 0X5B, 0X5A, 0X46, 0X4C, 0X4B,
    0X34, 0X3D, 0X3D, 0X2E, 0X35, 0X38, 0X2C, 0X33, 0X3B, 0X31, 0X3B, 0X48, 0X3E, 0X4B, 0X5D, 0X5E,
    0X6F, 0X86, 0X3C, 0X4F, 0X67, 0X39, 0X4A, 0X63, 0X3E, 0X4D, 0X66, 0X29, 0X34, 0X4F, 0X25, 0X30,
    0X4C, 0X29, 0X34, 0X50, 0X25, 0X32, 0X4E, 0X28, 0X38, 0X53, 0X21, 0X32, 0X4D, 0X2B, 0X3C, 0X57,
    0X2D, 0X3C, 0X59, 0X31, 0X40, 0X5D, 0X29, 0X37, 0X53, 0X37, 0X4A, 0X6A, 0X42, 0X5B, 0X83, 0X25,
    0X45, 0X74, 0X7D, 0XA2, 0XD5, 0XA1, 0XC4, 0XF4, 0X9F, 0XBE, 0XE9, 0XBA, 0XD7, 0XFF, 0X71, 0X8D,
    0XB6, 0X2D, 0X45, 0X6F, 0X46, 0X5C, 0X86, 0X52, 0X68, 0X91, 0X4D, 0X62, 0X8A, 0X4A, 0X63, 0X88,
    0X55, 0X69, 0X8C, 0XAD, 0XB4, 0XC3, 0XF4, 0XF5, 0XF4, 0XED, 0XEC, 0XF0, 0XEC, 0XEE, 0XEF, 0XF0,
    0XEF, 0XF0, 0XF1, 0XEF, 0XEF, 0XEE, 0XF0, 0XEF, 0XEF, 0XF0, 0XF0, 0XEF, 0XEE, 0XEE, 0XEF, 0XEF,
    0XEF, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEF,
    0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XED, 0XED, 0XED, 0XED, 0XED, 0XED, 0XEE,
    0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XED, 0XEC, 0XED, 0XEC, 0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XEB, 0XEA,
    0XEC, 0XEB, 0XEA, 0XEC, 0XEA, 0XE9, 0XEB, 0XE9, 0XE8, 0XEA, 0XE9, 0XE8, 0XEA, 0XE7, 0XE6, 0XEA,
    0XE6, 0XE5, 0XE9, 0XE5, 0XE4, 0XE8, 0XE3, 0XE2, 0XE6, 0XE0, 0XDE, 0XE4, 0XDD, 0XDB, 0XE1, 0XDA,
    0XD9, 0XDE, 0XD3, 0XD1, 0XDA, 0XCD, 0XCA, 0XD4, 0XC9, 0XC5, 0XD0, 0XC3, 0XBD, 0XCE, 0XBE, 0XB7,
    0XCB, 0XB7, 0XAE, 0XCA, 0XB0, 0XA7, 0XC7, 0XAA, 0X9E, 0XC9, 0XA7, 0X97, 0XDA, 0X97, 0X84, 0XE8,
    0X8D, 0X78, 0XF4, 0X8B, 0X74, 0XF6, 0X88, 0X72, 0XF2, 0X89, 0X72, 0XF5, 0X88, 0X6E, 0XF9, 0X88,
    0X6F, 0XF8, 0X79, 0X5C, 0XF1, 0X6E, 0X4D, 0XEE, 0XA1, 0X8D, 0XFC, 0X9F, 0X8D, 0XFC, 0X7E, 0X62,
    0XF2, 0X7A, 0X5B, 0XF7, 0X76, 0X56, 0XF9, 0X75, 0X59, 0XFA, 0X75, 0X58, 0XFC, 0X74, 0X56, 0XFC,
    0X76, 0X58, 0XFC, 0X74, 0X58, 0XFA, 0X74, 0X56, 0XFA, 0X76, 0X58, 0XFC, 0X75, 0X54, 0XFB, 0X72,
    0X53, 0XFA, 0X75, 0X58, 0XFA, 0X76, 0X5C, 0XF8, 0X75, 0X59, 0XF9, 0X78, 0X59, 0XFC, 0X7A, 0X5C,
    0XF7, 0X8F, 0X79, 0XF1, 0XC1, 0XB6, 0XFC, 0XC2, 0XB5, 0XFA, 0XB8, 0XAA, 0XFA, 0XAB, 0X9C, 0XFC,
    0X7D, 0X67, 0XF0, 0X7B, 0X5C, 0XFB, 0X79, 0X58, 0XF8, 0X77, 0X55, 0XF5, 0X78, 0X56, 0XF7, 0X7A,
    0X58, 0XFA, 0X78, 0X56, 0XFB, 0X76, 0X54, 0XF9, 0X77, 0X56, 0XFA, 0X75, 0X56, 0XF8, 0X79, 0X5A,
    0XF8, 0X80, 0X61, 0XF4, 0XA2, 0X8D, 0XF1, 0XE7, 0XE4, 0XFB, 0XF7, 0XF4, 0XFC, 0XF3, 0XEF, 0XFA,
    0XF3, 0XF2, 0XF7, 0XF0, 0XF3, 0XF6, 0XF1, 0XF1, 0XF8, 0XF1, 0XF0, 0XF9, 0XF0, 0XEF, 0XF8, 0XF1,
    0XF0, 0XF9, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF5, 0XF0, 0XF0, 0XF5, 0XF0, 0XEF,
    0XF5, 0XEF, 0XEF, 0XF5, 0XF0, 0XEF, 0XF5, 0XF1, 0XEF, 0XF5, 0XF1, 0XEF, 0XF5, 0XF2, 0XF0, 0XF5,
    0XF2, 0XF0, 0XF5, 0XF1, 0XF0, 0XF4, 0XF2, 0XF1, 0XF5, 0XF2, 0XF1, 0XF5, 0XF1, 0XF0, 0XF4, 0XF1,
    0XF0, 0XF3, 0XF0, 0XEF, 0XF1, 0XEF, 0XEE, 0XF0, 0XEF, 0XEE, 0XF0, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF,
    0XF1, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XEF, 0XEE, 0XF0,
    0XF0, 0XEE, 0XF0, 0XF0, 0XED, 0XEF, 0XF0, 0XED, 0XEF, 0XF0, 0XED, 0XEF, 0XEF, 0XED, 0XED, 0XEE,
    0XEC, 0XEC, 0XEE, 0XEA, 0XEA, 0XEE, 0XE9, 0XEA, 0XEB, 0XE7, 0XE8, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6,
    0XE6, 0XE7, 0XE5, 0XE5, 0XE7, 0XE4, 0XE4, 0XE6, 0XE1, 0XE2, 0XE2, 0XDC, 0XDD, 0XE0, 0XDA, 0XDB,
    0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF2, 0XF0, 0XF0, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF,
    0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA,
    0XEA, 0XEA, 0XE8, 0XE8, 0XE8, 0XE8, 0XE7, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE3,
    0XE5, 0XE2, 0XE3, 0XE3, 0XE0, 0XE2, 0XE2, 0XDE, 0XE0, 0XDF, 0XDE, 0XDF, 0XDD, 0XDD, 0XDD, 0XDD,
    0XDB, 0XDA, 0XDB, 0XD9, 0XD5, 0XDA, 0XD7, 0XD2, 0XD8, 0XD5, 0XD0, 0XD5, 0XD1, 0XCC, 0XD3, 0XD0,
    0XC9, 0XCC, 0XCB, 0XC1, 0XC8, 0XC6, 0XBC, 0XC7, 0XC5, 0XBB, 0XC4, 0XC2, 0XB8, 0XBA, 0XB7, 0XAC,
    0XB9, 0XB6, 0XA8, 0XB3, 0XB1, 0XA1, 0XAB, 0XA8, 0X94, 0XA7, 0XA3, 0X8C, 0XA0, 0X9E, 0X85, 0X97,
    0X96, 0X7A, 0X92, 0X90, 0X72, 0X8E, 0X8D, 0X6A, 0X8C, 0X8C, 0X63, 0X8B, 0X89, 0X5D, 0X8A, 0X88,
    0X50, 0X78, 0X7F, 0X2A, 0X69, 0X76, 0X08, 0X73, 0X7F, 0X0B, 0X79, 0X82, 0X10, 0X70, 0X79, 0X06,
    0X71, 0X7C, 0X00, 0X71, 0X7B, 0X03, 0X6C, 0X75, 0X03, 0X67, 0X72, 0X04, 0X58, 0X62, 0X02, 0X4F,
    0X5D, 0X00, 0X5B, 0X70, 0X05, 0X5A, 0X72, 0X02, 0X57, 0X70, 0X00, 0X5D, 0X78, 0X01, 0X60, 0X7D,
    0X03, 0X63, 0X81, 0X02, 0X64, 0X84, 0X01, 0X66, 0X87, 0X01, 0X68, 0X89, 0X00, 0X67, 0X89, 0X00,
    0X68, 0X8A, 0X00, 0X69, 0X8C, 0X00, 0X6A, 0X8D, 0X02, 0X6A, 0X8D, 0X01, 0X6B, 0X8E, 0X02, 0X6B,
    0X8D, 0X01, 0X6A, 0X8C, 0X00, 0X6A, 0X8C, 0X00, 0X6A, 0X90, 0X00, 0X6B, 0X91, 0X00, 0X6A, 0X91,
    0X01, 0X6D, 0X93, 0X01, 0X6E, 0X93, 0X00, 0X70, 0X93, 0X00, 0X75, 0X97, 0X00, 0X76, 0X97, 0X01,
    0X78, 0X99, 0X01, 0X78, 0X9D, 0X00, 0X78, 0XA1, 0X01, 0X7B, 0XA3, 0X02, 0X78, 0X9E, 0X00, 0X7B,
    0X9E, 0X00, 0X81, 0XA1, 0X03, 0X85, 0XA4, 0X01, 0X89, 0XAD, 0X01, 0X8F, 0XAE, 0X01, 0X98, 0XB3,
    0X04, 0X93, 0XAD, 0X00, 0X9C, 0XB1, 0X2D, 0XE2, 0XE7, 0XB8, 0XFC, 0XFB, 0XF3, 0XF2, 0XF3, 0XEC,
    0XF4, 0XF3, 0XEE, 0XF4, 0XF3, 0XEF, 0XF3, 0XF2, 0XF0, 0XF2, 0XF0, 0XEF, 0XF3, 0XF1, 0XF0, 0XF1,
    0XEF, 0XEE, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE,
    0XEE, 0XF1, 0XEF, 0XEF, 0XF2, 0XF0, 0XF0, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XED, 0XEB, 0XEB,
    0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE8, 0XE9,
    0XE6, 0XE7, 0XE8, 0XE6, 0XE6, 0XE6, 0XE3, 0XE4, 0XE3, 0XE1, 0XE1, 0XE4, 0XE1, 0XE0, 0XE3, 0XDF,
    0XDE, 0XE2, 0XDD, 0XDB, 0XE1, 0XDE, 0XDA, 0XDC, 0XD9, 0XD5, 0XD9, 0XD5, 0XD2, 0XD5, 0XD1, 0XCE,
    0XCF, 0XC9, 0XC7, 0XCB, 0XC7, 0XC2, 0XC2, 0XBF, 0XB9, 0XBB, 0XB6, 0XAF, 0XB7, 0XAE, 0XA9, 0XB3,
    0XAB, 0XA3, 0XB6, 0XAC, 0XA5, 0XB6, 0XAC, 0XA5, 0XB3, 0XAB, 0XA3, 0XB4, 0XAC, 0XA5, 0XB6, 0XAF,
    0XAA, 0X7E, 0X7F, 0X7B, 0X4F, 0X55, 0X53, 0X58, 0X5D, 0X5E, 0X52, 0X58, 0X57, 0X4B, 0X51, 0X50,
    0X38, 0X40, 0X3F, 0X2E, 0X34, 0X38, 0X34, 0X3C, 0X46, 0X24, 0X34, 0X42, 0X3E, 0X52, 0X65, 0X9A,
    0XB2, 0XC9, 0X82, 0X9C, 0XB5, 0X21, 0X39, 0X52, 0X31, 0X46, 0X5E, 0X34, 0X43, 0X5E, 0X25, 0X32,
    0X4D, 0X2C, 0X38, 0X54, 0X36, 0X44, 0X60, 0X2A, 0X3B, 0X56, 0X21, 0X32, 0X4C, 0X2A, 0X3B, 0X57,
    0X31, 0X43, 0X60, 0X4F, 0X61, 0X7D, 0X34, 0X44, 0X61, 0X49, 0X60, 0X80, 0X58, 0X7A, 0XA2, 0X31,
    0X59, 0X8A, 0X81, 0XAB, 0XDF, 0X97, 0XBD, 0XED, 0XA0, 0XC0, 0XEA, 0XBC, 0XDA, 0XFE, 0X7E, 0X9B,
    0XC3, 0X36, 0X4F, 0X79, 0X49, 0X5F, 0X89, 0X4A, 0X60, 0X8A, 0X4B, 0X60, 0X89, 0X4B, 0X63, 0X8B,
    0X53, 0X67, 0X8B, 0XB2, 0XB9, 0XC9, 0XF4, 0XF5, 0XF5, 0XEE, 0XED, 0XF1, 0XEE, 0XF0, 0XF1, 0XF1,
    0XF0, 0XF1, 0XF2, 0XEF, 0XF0, 0XED, 0XEF, 0XEF, 0XEE, 0XEF, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF,
    0XEF, 0XEF, 0XEF, 0XEF, 0XF0, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF,
    0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XED, 0XED, 0XED, 0XEC,
    0XEC, 0XEC, 0XEC, 0XEC, 0XEC, 0XEB, 0XEA, 0XEB, 0XEC, 0XEA, 0XED, 0XEB, 0XEA, 0XEC, 0XEA, 0XE9,
    0XEB, 0XE9, 0XE8, 0XEA, 0XE8, 0XE8, 0XE9, 0XE8, 0XE7, 0XE9, 0XE7, 0XE6, 0XE9, 0XE6, 0XE5, 0XEA,
    0XE5, 0XE4, 0XE8, 0XE4, 0XE3, 0XE6, 0XE2, 0XE0, 0XE5, 0XDE, 0XDB, 0XE2, 0XDA, 0XD8, 0XDE, 0XD6,
    0XD4, 0XDA, 0XD1, 0XCD, 0XD7, 0XCC, 0XC7, 0XD3, 0XC6, 0XC1, 0XCE, 0XC0, 0XBA, 0XCC, 0XBA, 0XB2,
    0XC9, 0XB2, 0XA8, 0XC6, 0XAE, 0XA3, 0XC6, 0XA9, 0X9C, 0XCE, 0X9E, 0X8A, 0XE2, 0X90, 0X7B, 0XEE,
    0X8B, 0X74, 0XF6, 0X85, 0X6E, 0XF1, 0X89, 0X6E, 0XF7, 0X89, 0X6E, 0XF9, 0X86, 0X70, 0XF8, 0X88,
    0X6D, 0XFE, 0X6F, 0X4E, 0XEE, 0X91, 0X7B, 0XF3, 0XAA, 0X98, 0XFD, 0X8A, 0X6E, 0XF7, 0X7B, 0X5C,
    0XF5, 0X79, 0X5C, 0XF8, 0X77, 0X57, 0XFB, 0X75, 0X58, 0XF9, 0X74, 0X57, 0XFA, 0X74, 0X56, 0XFB,
    0X74, 0X57, 0XFA, 0X74, 0X58, 0XFA, 0X75, 0X57, 0XFA, 0X75, 0X57, 0XFC, 0X75, 0X56, 0XFB, 0X75,
    0X56, 0XFC, 0X76, 0X58, 0XFB, 0X75, 0X58, 0XF8, 0X74, 0X54, 0XFA, 0X78, 0X57, 0XFA, 0X7D, 0X63,
    0XEC, 0XAB, 0X9A, 0XF7, 0XC7, 0XB9, 0XFD, 0XC3, 0XB7, 0XF8, 0XB4, 0XA8, 0XF5, 0X99, 0X86, 0XF9,
    0X74, 0X5D, 0XF2, 0X74, 0X55, 0XF8, 0X78, 0X51, 0XFB, 0X79, 0X56, 0XF9, 0X7B, 0X59, 0XFB, 0X78,
    0X56, 0XFA, 0X75, 0X54, 0XF8, 0X76, 0X56, 0XF9, 0X76, 0X57, 0XF9, 0X78, 0X58, 0XF8, 0X7C, 0X5C,
    0XF9, 0X8E, 0X73, 0XED, 0XCF, 0XCA, 0XF6, 0XF3, 0XF4, 0XFE, 0XF2, 0XEF, 0XFA, 0XF3, 0XF1, 0XF7,
    0XF3, 0XF1, 0XF9, 0XEF, 0XEF, 0XFB, 0XF0, 0XEF, 0XF9, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF1,
    0XF0, 0XF9, 0XF0, 0XEF, 0XF9, 0XF0, 0XF0, 0XF6, 0XF0, 0XF0, 0XF6, 0XEF, 0XEF, 0XF5, 0XF0, 0XEF,
    0XF5, 0XF0, 0XF0, 0XF6, 0XF0, 0XEF, 0XF5, 0XF1, 0XEE, 0XF5, 0XF1, 0XF0, 0XF5, 0XF2, 0XF1, 0XF5,
    0XF2, 0XF0, 0XF5, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1,
    0XF0, 0XF2, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XEF, 0XEE, 0XF0, 0XF0, 0XEE, 0XF1, 0XEF, 0XEE,
    0XF0, 0XEF, 0XEE, 0XF0, 0XEF, 0XEE, 0XF0, 0XF0, 0XEF, 0XF1, 0XEF, 0XEE, 0XF0, 0XEE, 0XED, 0XEF,
    0XEF, 0XED, 0XEF, 0XEE, 0XEB, 0XED, 0XEF, 0XEC, 0XEE, 0XEE, 0XEB, 0XED, 0XEC, 0XEA, 0XEA, 0XEE,
    0XEA, 0XEA, 0XEE, 0XE9, 0XEA, 0XEB, 0XE6, 0XE7, 0XEA, 0XE5, 0XE6, 0XE7, 0XE4, 0XE4, 0XE5, 0XE3,
    0XE3, 0XE4, 0XE2, 0XE2, 0XE3, 0XDF, 0XE0, 0XE3, 0XDE, 0XDF, 0XDE, 0XD9, 0XDA, 0XDC, 0XD7, 0XD8,
    0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF,
    0XED, 0XED, 0XF0, 0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA,
    0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5,
    0XE5, 0XE3, 0XE3, 0XE4, 0XE1, 0XE2, 0XE2, 0XE0, 0XE0, 0XE1, 0XE0, 0XE0, 0XDF, 0XDE, 0XDD, 0XDD,
    0XDC, 0XDA, 0XDD, 0XDB, 0XD7, 0XDD, 0XDA, 0XD5, 0XDA, 0XD6, 0XD1, 0XD9, 0XD4, 0XD1, 0XD5, 0XD1,
    0XCD, 0XD3, 0XCF, 0XCA, 0XCF, 0XCB, 0XC6, 0XCA, 0XC7, 0XBF, 0XC7, 0XC5, 0XBC, 0XC1, 0XBF, 0XB5,
    0XBA, 0XBA, 0XAD, 0XB7, 0XB7, 0XA8, 0XB2, 0XB0, 0X9E, 0XAA, 0XA8, 0X94, 0XA4, 0XA1, 0X8C, 0XA0,
    0X9C, 0X84, 0X99, 0X97, 0X7B, 0X94, 0X91, 0X72, 0X92, 0X8F, 0X6A, 0X8B, 0X88, 0X63, 0X8B, 0X87,
    0X5F, 0X86, 0X89, 0X46, 0X6F, 0X79, 0X1A, 0X6D, 0X78, 0X0A, 0X6D, 0X76, 0X05, 0X75, 0X7D, 0X08,
    0X70, 0X7A, 0X00, 0X71, 0X7C, 0X06, 0X72, 0X7D, 0X0A, 0X64, 0X71, 0X00, 0X62, 0X6C, 0X03, 0X56,
    0X5F, 0X03, 0X52, 0X60, 0X00, 0X5E, 0X73, 0X04, 0X5B, 0X73, 0X01, 0X55, 0X6E, 0X00, 0X5C, 0X75,
    0X03, 0X5E, 0X7B, 0X02, 0X61, 0X81, 0X04, 0X64, 0X86, 0X01, 0X67, 0X8B, 0X00, 0X69, 0X89, 0X01,
    0X68, 0X89, 0X01, 0X69, 0X8A, 0X00, 0X6C, 0X8D, 0X03, 0X6B, 0X8C, 0X01, 0X6B, 0X8D, 0X01, 0X6C,
    0X8E, 0X02, 0X6A, 0X8C, 0X00, 0X6B, 0X8E, 0X00, 0X69, 0X8F, 0X00, 0X6B, 0X91, 0X01, 0X6B, 0X92,
    0X01, 0X6B, 0X92, 0X00, 0X6D, 0X92, 0X00, 0X6F, 0X93, 0X00, 0X74, 0X96, 0X01, 0X72, 0X94, 0X01,
    0X73, 0X95, 0X00, 0X77, 0X9B, 0X02, 0X78, 0X9D, 0X01, 0X77, 0X9D, 0X00, 0X7B, 0XA0, 0X00, 0X7B,
    0X9F, 0X00, 0X7C, 0X9E, 0X00, 0X82, 0XA3, 0X00, 0X85, 0XA5, 0X00, 0X8C, 0XAA, 0X03, 0X92, 0XAE,
    0X02, 0X99, 0XB3, 0X02, 0X92, 0XAA, 0X05, 0XA3, 0XB2, 0X34, 0XE9, 0XED, 0XC2, 0XFA, 0XF8, 0XF4,
    0XF5, 0XF2, 0XEE, 0XF5, 0XF2, 0XF0, 0XF3, 0XF1, 0XF1, 0XF3, 0XF3, 0XEB, 0XF3, 0XF1, 0XEE, 0XF3,
    0XEF, 0XF1, 0XF1, 0XF0, 0XEE, 0XF1, 0XEF, 0XED, 0XF0, 0XEE, 0XEE, 0XF1, 0XEF, 0XEE, 0XF0, 0XEE,
    0XEF, 0XF0, 0XEF, 0XEE, 0XF1, 0XEE, 0XEF, 0XF0, 0XED, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED,
    0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEA, 0XE8, 0XE8, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE8,
    0XE6, 0XE6, 0XE8, 0XE6, 0XE6, 0XE5, 0XE3, 0XE3, 0XE3, 0XE1, 0XE0, 0XE2, 0XE0, 0XE0, 0XE1, 0XDF,
    0XDC, 0XE0, 0XDF, 0XDB, 0XE0, 0XDD, 0XDB, 0XDC, 0XD8, 0XD7, 0XD8, 0XD5, 0XD2, 0XD5, 0XD2, 0XCE,
    0XD1, 0XCE, 0XC9, 0XCB, 0XC7, 0XC2, 0XC6, 0XC1, 0XBA, 0XC2, 0XBB, 0XB5, 0XB8, 0XB1, 0XAB, 0XB5,
    0XAB, 0XA7, 0XB3, 0XA7, 0XA3, 0XB0, 0XA5, 0XA0, 0XB7, 0XAD, 0XA8, 0XB2, 0XAB, 0XA6, 0XB7, 0XB1,
    0XAC, 0X80, 0X80, 0X7E, 0X4E, 0X52, 0X52, 0X58, 0X5D, 0X5E, 0X4D, 0X56, 0X56, 0X47, 0X4F, 0X50,
    0X2F, 0X39, 0X3B, 0X2F, 0X39, 0X3D, 0X39, 0X43, 0X4D, 0X53, 0X68, 0X77, 0X69, 0X85, 0XA0, 0X7F,
    0XA1, 0XC2, 0X91, 0XB5, 0XCF, 0X5C, 0X7A, 0X97, 0X3F, 0X55, 0X71, 0X2E, 0X41, 0X5B, 0X2C, 0X38,
    0X55, 0X38, 0X46, 0X64, 0X2D, 0X42, 0X62, 0X31, 0X4A, 0X6C, 0X3C, 0X4E, 0X6C, 0X39, 0X48, 0X67,
    0X3B, 0X4E, 0X74, 0X53, 0X65, 0X83, 0X3B, 0X52, 0X6F, 0X41, 0X5E, 0X7B, 0X82, 0XA1, 0XC9, 0X60,
    0X88, 0XB8, 0X82, 0XAA, 0XD9, 0XA2, 0XC6, 0XF6, 0XA6, 0XC6, 0XEE, 0XB3, 0XD2, 0XF9, 0X79, 0X9C,
    0XD2, 0X50, 0X70, 0X9D, 0X45, 0X63, 0X89, 0X3C, 0X51, 0X7B, 0X4B, 0X5F, 0X89, 0X4A, 0X64, 0X91,
    0X59, 0X6B, 0X8F, 0XCE, 0XD6, 0XE2, 0XF1, 0XF2, 0XF8, 0XEF, 0XED, 0XF2, 0XF1, 0XF0, 0XF1, 0XEF,
    0XEF, 0XEF, 0XEF, 0XEE, 0XEF, 0XEE, 0XEE, 0XF0, 0XEF, 0XED, 0XF2, 0XF0, 0XEF, 0XF2, 0XEF, 0XEE,
    0XEF, 0XEF, 0XEE, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0, 0XF0, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEF,
    0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XED, 0XED, 0XED, 0XEE, 0XEE, 0XEE, 0XED,
    0XED, 0XED, 0XEB, 0XEB, 0XEB, 0XEB, 0XEA, 0XEC, 0XEC, 0XEB, 0XED, 0XE9, 0XE8, 0XEA, 0XE9, 0XE8,
    0XEA, 0XE9, 0XE8, 0XEA, 0XE8, 0XE7, 0XE9, 0XE8, 0XE7, 0XE8, 0XE5, 0XE4, 0XE7, 0XE5, 0XE4, 0XE8,
    0XE4, 0XE3, 0XE7, 0XE2, 0XE1, 0XE4, 0XDF, 0XDE, 0XE2, 0XDC, 0XDA, 0XE1, 0XD7, 0XD5, 0XDD, 0XD3,
    0XCF, 0XD9, 0XCB, 0XC8, 0XD3, 0XCB, 0XC5, 0XD2, 0XC2, 0XBC, 0XCE, 0XB7, 0XB5, 0XCB, 0XB3, 0XAE,
    0XC4, 0XB2, 0XA5, 0XC3, 0XAB, 0X9E, 0XCD, 0X9D, 0X8F, 0XDE, 0X91, 0X7D, 0XEE, 0X8D, 0X77, 0XF2,
    0X89, 0X71, 0XF6, 0X89, 0X70, 0XF6, 0X88, 0X6C, 0XFA, 0X85, 0X6A, 0XFA, 0X87, 0X6E, 0XFC, 0X75,
    0X55, 0XF3, 0X80, 0X61, 0XF0, 0XAA, 0X99, 0XFC, 0X98, 0X81, 0XF9, 0X7F, 0X5C, 0XF6, 0X7D, 0X5B,
    0XF9, 0X77, 0X58, 0XFB, 0X75, 0X59, 0XFC, 0X77, 0X59, 0XFD, 0X77, 0X58, 0XFB, 0X77, 0X58, 0XFA,
    0X79, 0X59, 0XFA, 0X7A, 0X5B, 0XFB, 0X77, 0X59, 0XFB, 0X74, 0X57, 0XFA, 0X73, 0X56, 0XF9, 0X75,
    0X57, 0XFB, 0X7B, 0X5A, 0XFB, 0X77, 0X58, 0XF7, 0X75, 0X58, 0XFA, 0X76, 0X57, 0XF9, 0X8B, 0X72,
    0XF2, 0XC1, 0XB6, 0XFC, 0XC6, 0XBB, 0XFA, 0XBC, 0XB3, 0XF5, 0XB3, 0XA4, 0XFB, 0X84, 0X6A, 0XF3,
    0X75, 0X56, 0XF7, 0X76, 0X55, 0XFA, 0X77, 0X52, 0XFA, 0X76, 0X54, 0XFA, 0X78, 0X58, 0XF8, 0X78,
    0X55, 0XF9, 0X77, 0X54, 0XF8, 0X76, 0X55, 0XFB, 0X73, 0X54, 0XF9, 0X77, 0X5C, 0XF8, 0X7E, 0X63,
    0XF0, 0XB1, 0XA0, 0XF0, 0XEE, 0XF1, 0XFB, 0XEF, 0XF4, 0XF6, 0XF1, 0XEF, 0XFC, 0XF2, 0XEF, 0XFA,
    0XF2, 0XF2, 0XF7, 0XF1, 0XF0, 0XFB, 0XF2, 0XF0, 0XFB, 0XF2, 0XF1, 0XFA, 0XF2, 0XF1, 0XFA, 0XF1,
    0XF0, 0XF9, 0XF0, 0XEF, 0XF7, 0XF1, 0XF0, 0XF6, 0XF1, 0XF0, 0XF6, 0XEF, 0XEE, 0XF5, 0XEF, 0XED,
    0XF4, 0XF0, 0XEF, 0XF4, 0XF0, 0XEF, 0XF5, 0XF2, 0XF0, 0XF6, 0XF2, 0XF1, 0XF5, 0XF2, 0XF1, 0XF5,
    0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XF1,
    0XF0, 0XF3, 0XF1, 0XF0, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF0, 0XEF, 0XEE, 0XF0, 0XF0, 0XEE,
    0XF0, 0XF1, 0XEF, 0XF1, 0XF1, 0XEE, 0XF0, 0XF0, 0XEE, 0XF0, 0XEF, 0XEE, 0XF0, 0XEE, 0XED, 0XEF,
    0XED, 0XEB, 0XED, 0XEE, 0XEB, 0XED, 0XED, 0XEA, 0XEC, 0XED, 0XEA, 0XEB, 0XEB, 0XE9, 0XE9, 0XEB,
    0XE8, 0XE8, 0XEA, 0XE7, 0XE7, 0XE8, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE5, 0XE3, 0XE3, 0XE2, 0XE1,
    0XE1, 0XDF, 0XDE, 0XDF, 0XDD, 0XDD, 0XDC, 0XDD, 0XDA, 0XD9, 0XDB, 0XD6, 0XD5, 0XDC, 0XD3, 0XD5,
    0XF2, 0XF0, 0XF0, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0,
    0XEE, 0XEE, 0XF1, 0XEF, 0XEF, 0XED, 0XEB, 0XEB, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XEC, 0XEA,
    0XEA, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE7, 0XE5, 0XE5, 0XE7, 0XE5, 0XE5,
    0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE4, 0XE2, 0XE2, 0XE4, 0XE2, 0XE2, 0XE1, 0XDE, 0XDE, 0XDE,
    0XDC, 0XDB, 0XE0, 0XDD, 0XD9, 0XDE, 0XDB, 0XD5, 0XDC, 0XD8, 0XD3, 0XDB, 0XD6, 0XD3, 0XD7, 0XD2,
    0XCF, 0XD5, 0XCF, 0XCC, 0XD2, 0XCE, 0XC9, 0XCD, 0XCA, 0XC4, 0XCA, 0XC7, 0XBE, 0XC5, 0XC4, 0XB9,
    0XBF, 0XBF, 0XB3, 0XBB, 0XBB, 0XAC, 0XB8, 0XB6, 0XA5, 0XB0, 0XAE, 0X9C, 0XAA, 0XA7, 0X93, 0XA3,
    0XA1, 0X8A, 0X9F, 0X9C, 0X81, 0X99, 0X95, 0X76, 0X95, 0X90, 0X6E, 0X91, 0X8E, 0X68, 0X8C, 0X8B,
    0X61, 0X8A, 0X89, 0X58, 0X84, 0X86, 0X42, 0X6D, 0X74, 0X17, 0X6C, 0X78, 0X07, 0X78, 0X81, 0X0D,
    0X75, 0X7C, 0X0E, 0X6E, 0X77, 0X0B, 0X75, 0X81, 0X12, 0X68, 0X75, 0X03, 0X61, 0X6C, 0X00, 0X60,
    0X6A, 0X04, 0X53, 0X5F, 0X01, 0X51, 0X61, 0X01, 0X5F, 0X75, 0X05, 0X58, 0X70, 0X01, 0X57, 0X6F,
    0X02, 0X5B, 0X77, 0X02, 0X5D, 0X7F, 0X00, 0X64, 0X85, 0X00, 0X68, 0X87, 0X02, 0X69, 0X88, 0X01,
    0X68, 0X89, 0X00, 0X6B, 0X8C, 0X01, 0X6C, 0X8D, 0X02, 0X6B, 0X8C, 0X02, 0X6A, 0X8B, 0X01, 0X6D,
    0X8F, 0X03, 0X6D, 0X8F, 0X02, 0X6A, 0X8D, 0X00, 0X68, 0X8D, 0X00, 0X69, 0X90, 0X00, 0X69, 0X90,
    0X00, 0X6A, 0X90, 0X00, 0X6C, 0X91, 0X00, 0X70, 0X93, 0X00, 0X72, 0X95, 0X00, 0X70, 0X93, 0X00,
    0X71, 0X93, 0X00, 0X73, 0X96, 0X00, 0X78, 0X9C, 0X01, 0X77, 0X9C, 0X00, 0X78, 0X9D, 0X00, 0X7C,
    0X9F, 0X01, 0X79, 0X9D, 0X00, 0X7D, 0X9F, 0X00, 0X82, 0XA1, 0X01, 0X88, 0XA5, 0X01, 0X8E, 0XAB,
    0X00, 0X93, 0XB0, 0X01, 0X98, 0XB0, 0X05, 0X95, 0XA9, 0X08, 0XA9, 0XBA, 0X4B, 0XED, 0XEF, 0XD4,
    0XFA, 0XF9, 0XF4, 0XF1, 0XF2, 0XEB, 0XF4, 0XF2, 0XF0, 0XF5, 0XF2, 0XEF, 0XF3, 0XF1, 0XF0, 0XF1,
    0XEF, 0XF0, 0XF3, 0XF2, 0XEE, 0XF1, 0XEF, 0XEC, 0XF1, 0XEF, 0XEE, 0XF1, 0XEF, 0XEE, 0XF1, 0XEF,
    0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEF, 0XED, 0XED,
    0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE8,
    0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE7, 0XE5, 0XE5, 0XE4, 0XE2, 0XE1, 0XE2, 0XE0, 0XDF, 0XE0, 0XDF,
    0XDC, 0XDE, 0XDD, 0XD9, 0XDE, 0XDB, 0XD9, 0XDD, 0XD9, 0XD8, 0XD9, 0XD6, 0XD2, 0XD7, 0XD4, 0XD0,
    0XD1, 0XCE, 0XC9, 0XCD, 0XC9, 0XC4, 0XC5, 0XBE, 0XB9, 0XBB, 0XB3, 0XAD, 0XB6, 0XB0, 0XAB, 0XB6,
    0XAC, 0XA9, 0XB3, 0XA8, 0XA4, 0XB5, 0XAA, 0XA6, 0XB6, 0XAC, 0XA8, 0XB4, 0XAC, 0XA9, 0XBA, 0XB5,
    0XB1, 0X93, 0X92, 0X90, 0X4B, 0X4F, 0X4D, 0X54, 0X5B, 0X5A, 0X4D, 0X55, 0X54, 0X41, 0X4A, 0X4B,
    0X2F, 0X39, 0X3C, 0X38, 0X43, 0X47, 0X43, 0X52, 0X5C, 0X6B, 0X83, 0X98, 0X8C, 0XA9, 0XCE, 0X79,
    0XA1, 0XC9, 0X92, 0XB8, 0XD6, 0XA3, 0XC3, 0XE5, 0X8B, 0XA2, 0XC4, 0X31, 0X48, 0X65, 0X27, 0X38,
    0X59, 0X4C, 0X5F, 0X80, 0X54, 0X70, 0X91, 0X4D, 0X6E, 0X92, 0X7A, 0X94, 0XB2, 0X7F, 0X94, 0XB5,
    0X2E, 0X47, 0X71, 0X50, 0X67, 0X89, 0X42, 0X61, 0X85, 0X36, 0X59, 0X7C, 0X8C, 0XAC, 0XD8, 0X8F,
    0XB5, 0XE7, 0X95, 0XBC, 0XE8, 0X9A, 0XBA, 0XEC, 0XAE, 0XCB, 0XF3, 0XAF, 0XCD, 0XF2, 0X93, 0XBB,
    0XF0, 0X6F, 0X94, 0XC3, 0X3C, 0X5B, 0X85, 0X35, 0X4A, 0X78, 0X43, 0X56, 0X85, 0X39, 0X56, 0X83,
    0X8D, 0XA1, 0XBF, 0XE7, 0XED, 0XF6, 0XEC, 0XED, 0XF5, 0XF1, 0XEE, 0XF3, 0XF1, 0XEE, 0XF0, 0XF0,
    0XEF, 0XF1, 0XEF, 0XF1, 0XF1, 0XF0, 0XF0, 0XF2, 0XEF, 0XED, 0XF3, 0XF0, 0XEE, 0XF3, 0XF0, 0XEE,
    0XF1, 0XEF, 0XEE, 0XF0, 0XED, 0XED, 0XED, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF,
    0XEE, 0XEE, 0XEE, 0XED, 0XED, 0XED, 0XF0, 0XF0, 0XF0, 0XEE, 0XEE, 0XEE, 0XED, 0XED, 0XED, 0XEC,
    0XEC, 0XEC, 0XEA, 0XEA, 0XEA, 0XEB, 0XEB, 0XEC, 0XED, 0XEC, 0XEE, 0XEA, 0XE9, 0XEB, 0XEA, 0XE9,
    0XEB, 0XEB, 0XEA, 0XEC, 0XE7, 0XE6, 0XE8, 0XE7, 0XE6, 0XE7, 0XE4, 0XE3, 0XE5, 0XE3, 0XE2, 0XE4,
    0XE2, 0XE1, 0XE3, 0XDF, 0XDF, 0XE1, 0XDD, 0XDC, 0XE1, 0XDA, 0XD7, 0XDF, 0XD3, 0XD0, 0XDA, 0XCE,
    0XCA, 0XD5, 0XC9, 0XC6, 0XD2, 0XC7, 0XC0, 0XCC, 0XC0, 0XB8, 0XCA, 0XB3, 0XAF, 0XC8, 0XB0, 0XAA,
    0XC0, 0XB0, 0XA4, 0XC1, 0XA0, 0X93, 0XCE, 0X8C, 0X7D, 0XE0, 0X8D, 0X77, 0XF6, 0X89, 0X71, 0XF4,
    0X86, 0X6D, 0XF3, 0X89, 0X71, 0XF5, 0X84, 0X6C, 0XF4, 0X87, 0X6F, 0XFA, 0X81, 0X68, 0XFA, 0X71,
    0X51, 0XEB, 0X9B, 0X83, 0XFA, 0XA4, 0X92, 0XFE, 0X85, 0X6A, 0XF6, 0X7D, 0X59, 0XFA, 0X7E, 0X5A,
    0XFD, 0X79, 0X59, 0XFA, 0X77, 0X5A, 0XF8, 0X76, 0X57, 0XFB, 0X77, 0X56, 0XFB, 0X78, 0X56, 0XF7,
    0X7B, 0X5A, 0XF9, 0X76, 0X55, 0XF6, 0X74, 0X55, 0XF7, 0X77, 0X59, 0XFC, 0X74, 0X56, 0XFA, 0X7A,
    0X5A, 0XFD, 0X7B, 0X5B, 0XFC, 0X78, 0X5A, 0XF7, 0X75, 0X59, 0XFA, 0X75, 0X57, 0XF7, 0X90, 0X7C,
    0XEC, 0XC9, 0XC2, 0XFD, 0XC3, 0XBA, 0XF9, 0XBD, 0XB0, 0XFD, 0X99, 0X84, 0XF5, 0X75, 0X57, 0XEE,
    0X78, 0X56, 0XF9, 0X78, 0X55, 0XFB, 0X76, 0X54, 0XFA, 0X74, 0X51, 0XFC, 0X75, 0X54, 0XF7, 0X7B,
    0X59, 0XF9, 0X7A, 0X57, 0XFD, 0X73, 0X53, 0XF8, 0X76, 0X58, 0XFA, 0X79, 0X5D, 0XF5, 0X90, 0X7E,
    0XEE, 0XDE, 0XD7, 0XFA, 0XF3, 0XF6, 0XFB, 0XEF, 0XF2, 0XF7, 0XF1, 0XEE, 0XFD, 0XF0, 0XEF, 0XFA,
    0XF1, 0XF3, 0XF3, 0XF2, 0XF1, 0XFA, 0XF3, 0XF1, 0XFC, 0XF2, 0XF1, 0XF9, 0XF1, 0XF0, 0XF9, 0XF0,
    0XEF, 0XF8, 0XF1, 0XF0, 0XF7, 0XF2, 0XEF, 0XF5, 0XF2, 0XEF, 0XF5, 0XF2, 0XF0, 0XF6, 0XF0, 0XEE,
    0XF4, 0XF0, 0XEE, 0XF4, 0XF2, 0XF0, 0XF5, 0XF1, 0XEF, 0XF6, 0XF1, 0XF0, 0XF5, 0XF1, 0XF0, 0XF4,
    0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XEF,
    0XEE, 0XF2, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF1, 0XEF, 0XEE, 0XF0, 0XEF, 0XED,
    0XEF, 0XF1, 0XEE, 0XF0, 0XF1, 0XEE, 0XF0, 0XEE, 0XEC, 0XEE, 0XEB, 0XEB, 0XED, 0XEC, 0XEB, 0XED,
    0XEC, 0XEA, 0XEC, 0XED, 0XEA, 0XEC, 0XEC, 0XE9, 0XEB, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE8,
    0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE4, 0XE3, 0XE3, 0XE3, 0XE1, 0XE1, 0XE4, 0XDF, 0XE0, 0XE2, 0XDD,
    0XDE, 0XDF, 0XDB, 0XDC, 0XDC, 0XD8, 0XD9, 0XD8, 0XD3, 0XD3, 0XD9, 0XD0, 0XD0, 0XD3, 0XCC, 0XCE,
    0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF2,
    0XF0, 0XF0, 0XF0, 0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XF0, 0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC,
    0XEC, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7, 0XE7,
    0XE8, 0XE6, 0XE6, 0XE5, 0XE3, 0XE3, 0XE5, 0XE3, 0XE3, 0XE4, 0XE2, 0XE3, 0XE2, 0XE0, 0XE0, 0XE0,
    0XDE, 0XDE, 0XE1, 0XDE, 0XDA, 0XE0, 0XDD, 0XD9, 0XDF, 0XDB, 0XD8, 0XDC, 0XD7, 0XD4, 0XDA, 0XD6,
    0XD2, 0XD7, 0XD3, 0XCF, 0XD5, 0XD1, 0XCB, 0XD1, 0XCF, 0XC6, 0XCD, 0XCC, 0XC1, 0XCB, 0XC9, 0XBF,
    0XC7, 0XC6, 0XB9, 0XC1, 0XC1, 0XB2, 0XBC, 0XBA, 0XAB, 0XB6, 0XB3, 0XA4, 0XB0, 0XAE, 0X9D, 0XAB,
    0XA8, 0X93, 0XA2, 0X9E, 0X85, 0X9D, 0X9A, 0X7D, 0X98, 0X95, 0X73, 0X95, 0X93, 0X6D, 0X8E, 0X8E,
    0X65, 0X8B, 0X86, 0X63, 0X8D, 0X89, 0X5B, 0X82, 0X86, 0X3C, 0X6B, 0X76, 0X11, 0X6E, 0X7A, 0X0B,
    0X74, 0X7C, 0X13, 0X6F, 0X77, 0X10, 0X71, 0X7A, 0X0F, 0X6E, 0X77, 0X08, 0X66, 0X72, 0X00, 0X63,
    0X6F, 0X01, 0X5D, 0X68, 0X03, 0X4F, 0X5A, 0X01, 0X52, 0X60, 0X02, 0X61, 0X76, 0X07, 0X59, 0X72,
    0X00, 0X56, 0X71, 0X00, 0X5D, 0X7C, 0X00, 0X5F, 0X81, 0X01, 0X64, 0X81, 0X06, 0X65, 0X86, 0X01,
    0X66, 0X87, 0X00, 0X6A, 0X8B, 0X01, 0X68, 0X89, 0X01, 0X69, 0X8A, 0X00, 0X69, 0X8A, 0X00, 0X6B,
    0X8D, 0X01, 0X6C, 0X8E, 0X02, 0X6A, 0X8D, 0X01, 0X68, 0X8E, 0X00, 0X69, 0X8F, 0X02, 0X6A, 0X90,
    0X00, 0X6C, 0X91, 0X01, 0X6A, 0X8F, 0X00, 0X6D, 0X91, 0X00, 0X74, 0X96, 0X04, 0X76, 0X97, 0X04,
    0X73, 0X95, 0X01, 0X74, 0X97, 0X01, 0X76, 0X9A, 0X01, 0X75, 0X9A, 0X00, 0X77, 0X9C, 0X00, 0X77,
    0X9C, 0X00, 0X7A, 0X9D, 0X00, 0X7B, 0X9D, 0X00, 0X7E, 0X9E, 0X02, 0X82, 0XA0, 0X01, 0X89, 0XA7,
    0X01, 0X8E, 0XAD, 0X00, 0X91, 0XAD, 0X00, 0X97, 0XAF, 0X07, 0X94, 0XAA, 0X0A, 0XB5, 0XC3, 0X62,
    0XF1, 0XF3, 0XDE, 0XF3, 0XF8, 0XED, 0XF4, 0XF2, 0XEA, 0XF7, 0XF0, 0XF1, 0XF4, 0XF2, 0XF0, 0XEF,
    0XF3, 0XEC, 0XF2, 0XF1, 0XED, 0XF3, 0XF1, 0XEE, 0XF1, 0XEF, 0XEE, 0XF1, 0XEF, 0XEE, 0XF0, 0XEE,
    0XEE, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XF0, 0XEE, 0XEE,
    0XED, 0XEB, 0XEB, 0XEE, 0XEC, 0XEC, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XE9,
    0XE7, 0XE7, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE2, 0XE0, 0XDF, 0XE1, 0XDF,
    0XDE, 0XE0, 0XDE, 0XDD, 0XE0, 0XDC, 0XDB, 0XDB, 0XD8, 0XD5, 0XDA, 0XD7, 0XD3, 0XD7, 0XD4, 0XD0,
    0XD4, 0XD1, 0XCD, 0XCD, 0XCA, 0XC5, 0XC6, 0XC2, 0XBD, 0XBF, 0XB9, 0XB4, 0XBB, 0XB4, 0XAF, 0XB5,
    0XAC, 0XA8, 0XB6, 0XAC, 0XA8, 0XB9, 0XAE, 0XAA, 0XB6, 0XAC, 0XA9, 0XB5, 0XAD, 0XAA, 0XB5, 0XB0,
    0XAD, 0X9A, 0X99, 0X96, 0X46, 0X49, 0X47, 0X48, 0X4E, 0X4D, 0X40, 0X47, 0X48, 0X46, 0X4E, 0X4F,
    0X35, 0X40, 0X44, 0X40, 0X4D, 0X55, 0X55, 0X69, 0X7A, 0X6A, 0X87, 0XA4, 0X83, 0XA5, 0XCC, 0X85,
    0XAD, 0XD8, 0X9B, 0XC0, 0XE0, 0X97, 0XB9, 0XDD, 0X99, 0XB5, 0XDB, 0X67, 0X84, 0XAA, 0X16, 0X33,
    0X59, 0X62, 0X7C, 0X9E, 0XB2, 0XD0, 0XF0, 0X7E, 0XA5, 0XC9, 0X9A, 0XC0, 0XDF, 0XAE, 0XD1, 0XF1,
    0X60, 0X81, 0XAA, 0X6E, 0X88, 0XB0, 0X49, 0X6F, 0X9E, 0X6E, 0X96, 0XC1, 0X8D, 0XB1, 0XE1, 0X81,
    0XA8, 0XDD, 0X9B, 0XBF, 0XEE, 0X99, 0XBA, 0XEC, 0XAE, 0XCC, 0XF4, 0XAC, 0XCC, 0XF2, 0X91, 0XBB,
    0XE3, 0X94, 0XBA, 0XE5, 0X46, 0X62, 0X94, 0X37, 0X4E, 0X82, 0X3D, 0X55, 0X87, 0X48, 0X66, 0X92,
    0XB8, 0XCE, 0XE1, 0XE9, 0XEF, 0XF5, 0XED, 0XEF, 0XF4, 0XF0, 0XEE, 0XF2, 0XF1, 0XEE, 0XF0, 0XEE,
    0XEF, 0XF2, 0XF0, 0XF0, 0XF3, 0XF1, 0XEF, 0XF4, 0XF0, 0XEE, 0XF4, 0XF0, 0XEE, 0XF3, 0XF0, 0XEF,
    0XF1, 0XEF, 0XEE, 0XEF, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEE, 0XEE, 0XEE,
    0XEE, 0XED, 0XEF, 0XEC, 0XEB, 0XED, 0XEE, 0XED, 0XEF, 0XED, 0XEC, 0XEE, 0XED, 0XEC, 0XEE, 0XEC,
    0XEB, 0XED, 0XEB, 0XEA, 0XEC, 0XEB, 0XEA, 0XEC, 0XEA, 0XE9, 0XEB, 0XEA, 0XE9, 0XEB, 0XEA, 0XE9,
    0XEB, 0XE9, 0XE8, 0XEA, 0XE7, 0XE6, 0XE8, 0XE6, 0XE5, 0XE7, 0XE4, 0XE3, 0XE5, 0XE2, 0XE1, 0XE3,
    0XE0, 0XDF, 0XE1, 0XDE, 0XDD, 0XDF, 0XDB, 0XDA, 0XDE, 0XD8, 0XD6, 0XDC, 0XD1, 0XCE, 0XD8, 0XCA,
    0XC6, 0XD1, 0XC4, 0XC2, 0XCE, 0XC1, 0XBB, 0XC7, 0XBE, 0XB3, 0XC7, 0XB5, 0XAA, 0XC8, 0XAF, 0XA6,
    0XBF, 0XAD, 0XA4, 0XC2, 0X94, 0X89, 0XCE, 0X88, 0X78, 0XE7, 0X8C, 0X76, 0XF5, 0X87, 0X70, 0XF4,
    0X85, 0X6C, 0XF5, 0X87, 0X6D, 0XF9, 0X87, 0X6F, 0XF9, 0X81, 0X69, 0XF8, 0X74, 0X5B, 0XF1, 0X88,
    0X6D, 0XFA, 0XA0, 0X8F, 0XFC, 0X8C, 0X77, 0XF5, 0X78, 0X5A, 0XF4, 0X7B, 0X5B, 0XFA, 0X79, 0X56,
    0XFC, 0X7B, 0X5B, 0XFB, 0X77, 0X58, 0XF7, 0X77, 0X57, 0XFB, 0X78, 0X55, 0XF9, 0X76, 0X55, 0XF8,
    0X7B, 0X59, 0XFB, 0X79, 0X57, 0XFA, 0X78, 0X57, 0XFA, 0X79, 0X58, 0XFB, 0X7A, 0X58, 0XFB, 0X7B,
    0X5A, 0XFB, 0X7A, 0X5A, 0XFB, 0X76, 0X5A, 0XF9, 0X79, 0X5C, 0XFE, 0X79, 0X5E, 0XF1, 0XAA, 0X9D,
    0XF4, 0XC9, 0XC4, 0XFD, 0XBB, 0XB4, 0XFB, 0X99, 0X86, 0XF4, 0X7B, 0X5F, 0XF1, 0X79, 0X59, 0XF9,
    0X75, 0X56, 0XF9, 0X77, 0X55, 0XFA, 0X77, 0X53, 0XFC, 0X76, 0X51, 0XFD, 0X75, 0X51, 0XF9, 0X7A,
    0X59, 0XF9, 0X74, 0X52, 0XF9, 0X77, 0X5A, 0XFB, 0X79, 0X5A, 0XFA, 0X80, 0X65, 0XEF, 0XBF, 0XB5,
    0XF5, 0XF4, 0XF5, 0XFD, 0XEF, 0XF1, 0XF9, 0XF3, 0XF1, 0XFC, 0XF1, 0XEF, 0XFD, 0XF2, 0XF3, 0XF9,
    0XF1, 0XF3, 0XF3, 0XF1, 0XF0, 0XFA, 0XF1, 0XF0, 0XFB, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF1,
    0XF0, 0XF9, 0XF0, 0XEF, 0XF8, 0XF1, 0XEE, 0XF6, 0XF1, 0XEE, 0XF6, 0XF1, 0XEF, 0XF5, 0XF3, 0XF1,
    0XF7, 0XF2, 0XF0, 0XF6, 0XF1, 0XEF, 0XF5, 0XF2, 0XF0, 0XF5, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4,
    0XF1, 0XF0, 0XF4, 0XF2, 0XF1, 0XF5, 0XF2, 0XF1, 0XF5, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XEF,
    0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEF, 0XEE, 0XF2, 0XED, 0XEC, 0XF0, 0XEF, 0XEE, 0XF0, 0XEF, 0XED,
    0XEF, 0XF0, 0XED, 0XEF, 0XEF, 0XEC, 0XEE, 0XED, 0XEA, 0XEC, 0XEA, 0XE9, 0XEB, 0XE9, 0XE9, 0XEB,
    0XEB, 0XE9, 0XEB, 0XEC, 0XE9, 0XEB, 0XEB, 0XE8, 0XEA, 0XE9, 0XE6, 0XE7, 0XE7, 0XE5, 0XE5, 0XE6,
    0XE4, 0XE4, 0XE3, 0XE1, 0XE1, 0XE1, 0XE0, 0XDF, 0XE2, 0XDE, 0XDE, 0XE2, 0XDC, 0XDD, 0XE1, 0XD9,
    0XDA, 0XDD, 0XD6, 0XD7, 0XDA, 0XD3, 0XD4, 0XD7, 0XCE, 0XCF, 0XD5, 0XC9, 0XCC, 0XCB, 0XC6, 0XC7,
    0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF2,
    0XF0, 0XF0, 0XF1, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE, 0XEC,
    0XEC, 0XEE, 0XEC, 0XEC, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9,
    0XE9, 0XE7, 0XE7, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE3, 0XE1, 0XE1, 0XE3,
    0XE1, 0XE0, 0XE0, 0XDF, 0XDD, 0XE2, 0XDF, 0XDB, 0XDF, 0XDC, 0XD8, 0XDD, 0XDA, 0XD6, 0XDC, 0XD9,
    0XD4, 0XD9, 0XD5, 0XD0, 0XD7, 0XD3, 0XCD, 0XD4, 0XD1, 0XC9, 0XD1, 0XCF, 0XC5, 0XCC, 0XCA, 0XC0,
    0XC9, 0XC8, 0XBC, 0XC6, 0XC5, 0XB6, 0XC1, 0XBE, 0XB2, 0XBC, 0XB9, 0XAE, 0XB7, 0XB3, 0XA6, 0XB0,
    0XAC, 0X9B, 0XAB, 0XA6, 0X90, 0XA4, 0XA1, 0X86, 0XA0, 0X9D, 0X7F, 0X95, 0X93, 0X72, 0X90, 0X8D,
    0X6D, 0X8E, 0X8A, 0X68, 0X89, 0X87, 0X5E, 0X8A, 0X8B, 0X53, 0X7C, 0X81, 0X36, 0X70, 0X79, 0X1C,
    0X6F, 0X7A, 0X12, 0X71, 0X7A, 0X0F, 0X76, 0X7F, 0X12, 0X6D, 0X74, 0X05, 0X6D, 0X76, 0X02, 0X66,
    0X72, 0X00, 0X61, 0X6C, 0X01, 0X5C, 0X65, 0X05, 0X4C, 0X55, 0X00, 0X53, 0X63, 0X01, 0X60, 0X78,
    0X03, 0X56, 0X70, 0X00, 0X5A, 0X74, 0X01, 0X5D, 0X7B, 0X02, 0X61, 0X7F, 0X02, 0X65, 0X86, 0X01,
    0X64, 0X86, 0X00, 0X66, 0X86, 0X00, 0X65, 0X87, 0X00, 0X66, 0X88, 0X00, 0X67, 0X89, 0X00, 0X6A,
    0X8C, 0X00, 0X6A, 0X8D, 0X01, 0X6A, 0X8D, 0X01, 0X69, 0X8E, 0X03, 0X69, 0X8E, 0X02, 0X69, 0X8F,
    0X02, 0X6A, 0X90, 0X01, 0X6A, 0X8F, 0X00, 0X6B, 0X8F, 0X00, 0X70, 0X93, 0X04, 0X71, 0X94, 0X03,
    0X6F, 0X93, 0X00, 0X72, 0X95, 0X00, 0X73, 0X96, 0X00, 0X71, 0X95, 0X00, 0X76, 0X9A, 0X00, 0X76,
    0X9B, 0X00, 0X76, 0X9B, 0X00, 0X78, 0X9E, 0X00, 0X78, 0X9B, 0X00, 0X7E, 0X9F, 0X03, 0X82, 0XA3,
    0X00, 0X89, 0XA9, 0X00, 0X8E, 0XAC, 0X00, 0X91, 0XAC, 0X00, 0X99, 0XAE, 0X06, 0X91, 0XA9, 0X0D,
    0XBB, 0XC7, 0X77, 0XF7, 0XF8, 0XE5, 0XF5, 0XF5, 0XEC, 0XF4, 0XF1, 0XF0, 0XF2, 0XF3, 0XE9, 0XF0,
    0XF2, 0XEB, 0XF2, 0XF0, 0XEE, 0XF2, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XEF, 0XED,
    0XED, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED,
    0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEA, 0XE8, 0XE8, 0XEA, 0XE8, 0XE8, 0XE8,
    0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE4, 0XE2, 0XE1, 0XE2, 0XE0,
    0XDF, 0XE0, 0XDE, 0XDD, 0XDE, 0XDC, 0XDB, 0XDB, 0XD9, 0XD6, 0XD8, 0XD7, 0XD3, 0XD5, 0XD2, 0XCE,
    0XD0, 0XCD, 0XC9, 0XCC, 0XC7, 0XC4, 0XC7, 0XC3, 0XBF, 0XC0, 0XBC, 0XB7, 0XBB, 0XB4, 0XB0, 0XB4,
    0XAA, 0XA7, 0XB3, 0XAA, 0XA6, 0XB3, 0XAA, 0XA6, 0XB6, 0XAD, 0XAA, 0XB4, 0XAC, 0XA9, 0XB5, 0XAF,
    0XAC, 0XA4, 0XA1, 0X9F, 0X3B, 0X3E, 0X3F, 0X3C, 0X45, 0X49, 0X33, 0X40, 0X45, 0X4B, 0X58, 0X5F,
    0X40, 0X4F, 0X5A, 0X2E, 0X40, 0X51, 0X64, 0X7F, 0X97, 0X8C, 0XB0, 0XD1, 0X75, 0X9C, 0XC7, 0X7F,
    0XAA, 0XD5, 0X97, 0XBE, 0XDE, 0X9C, 0XC2, 0XE5, 0X98, 0XB8, 0XE1, 0X7D, 0XA1, 0XCA, 0X23, 0X49,
    0X74, 0X88, 0XA5, 0XC6, 0XBC, 0XD8, 0XF7, 0X7E, 0XAA, 0XD0, 0X8C, 0XB9, 0XDC, 0X9B, 0XC7, 0XE9,
    0X8E, 0XB5, 0XDE, 0X9C, 0XB7, 0XE1, 0X7A, 0XA0, 0XD2, 0X9B, 0XC0, 0XED, 0X91, 0XB5, 0XE6, 0X8B,
    0XB1, 0XE5, 0XA4, 0XC6, 0XF3, 0X92, 0XB5, 0XE7, 0XA8, 0XC8, 0XF2, 0XA6, 0XCA, 0XF1, 0X8D, 0XB8,
    0XDD, 0XB2, 0XD3, 0XFC, 0X86, 0X9F, 0XCD, 0X30, 0X52, 0X83, 0X3E, 0X62, 0X96, 0X5C, 0X7A, 0XA7,
    0XC2, 0XD4, 0XE3, 0XEA, 0XF0, 0XF4, 0XED, 0XEF, 0XF3, 0XF1, 0XEE, 0XF2, 0XF2, 0XEE, 0XF3, 0XEE,
    0XEF, 0XF3, 0XEF, 0XEE, 0XF3, 0XF1, 0XEF, 0XF5, 0XF2, 0XF0, 0XF6, 0XF0, 0XEF, 0XF4, 0XF0, 0XEF,
    0XF1, 0XF0, 0XEF, 0XF1, 0XEE, 0XEE, 0XEF, 0XEE, 0XEE, 0XEE, 0XEF, 0XEF, 0XEF, 0XEE, 0XED, 0XEE,
    0XEF, 0XEE, 0XF0, 0XED, 0XEC, 0XEE, 0XEC, 0XEB, 0XED, 0XED, 0XEC, 0XEE, 0XED, 0XEC, 0XEF, 0XEC,
    0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XEB, 0XEA, 0XEC, 0XE9, 0XE8, 0XEA, 0XE9, 0XE8, 0XEA, 0XE8, 0XE7,
    0XE9, 0XE6, 0XE5, 0XE7, 0XE5, 0XE4, 0XE6, 0XE4, 0XE3, 0XE4, 0XE3, 0XE2, 0XE4, 0XDF, 0XDF, 0XE0,
    0XDE, 0XDD, 0XDF, 0XDD, 0XDC, 0XDE, 0XD9, 0XD8, 0XDA, 0XD3, 0XD1, 0XD8, 0XCE, 0XCA, 0XD5, 0XC8,
    0XC4, 0XCF, 0XC0, 0XBF, 0XCC, 0XBC, 0XB8, 0XC5, 0XBA, 0XAF, 0XC4, 0XB6, 0XA6, 0XC7, 0XAC, 0XA1,
    0XBF, 0XA3, 0X9F, 0XC3, 0X93, 0X8C, 0XE0, 0X85, 0X74, 0XF5, 0X87, 0X6F, 0XF6, 0X86, 0X6E, 0XF5,
    0X87, 0X6F, 0XF4, 0X85, 0X6B, 0XFB, 0X82, 0X68, 0XFA, 0X77, 0X5D, 0XF5, 0X76, 0X5E, 0XF5, 0X86,
    0X74, 0XFA, 0X8A, 0X7E, 0XF1, 0X82, 0X6E, 0XF5, 0X7A, 0X5E, 0XF9, 0X77, 0X5C, 0XF6, 0X79, 0X5A,
    0XFA, 0X7A, 0X57, 0XFB, 0X7C, 0X58, 0XFC, 0X7A, 0X58, 0XFB, 0X79, 0X57, 0XF9, 0X7A, 0X59, 0XFB,
    0X7C, 0X5A, 0XFC, 0X7A, 0X57, 0XFA, 0X7A, 0X57, 0XFB, 0X7A, 0X56, 0XFB, 0X7D, 0X5A, 0XFC, 0X7A,
    0X59, 0XF8, 0X78, 0X59, 0XF9, 0X78, 0X5B, 0XFD, 0X77, 0X5B, 0XF8, 0X8D, 0X7B, 0XF1, 0XC0, 0XB9,
    0XFD, 0XBD, 0XB3, 0XFC, 0X9A, 0X8D, 0XF3, 0X7B, 0X61, 0XEF, 0X76, 0X56, 0XF9, 0X78, 0X59, 0XFB,
    0X74, 0X56, 0XF8, 0X74, 0X52, 0XFA, 0X77, 0X53, 0XFC, 0X7A, 0X56, 0XFB, 0X77, 0X52, 0XFC, 0X78,
    0X54, 0XFC, 0X74, 0X54, 0XF7, 0X76, 0X59, 0XF9, 0X7C, 0X5E, 0XF5, 0XA5, 0X90, 0XF4, 0XEB, 0XE8,
    0XFD, 0XF3, 0XF5, 0XF7, 0XF2, 0XF1, 0XFA, 0XF3, 0XF0, 0XFC, 0XF2, 0XF0, 0XFA, 0XF2, 0XF2, 0XF6,
    0XF1, 0XF2, 0XF6, 0XF1, 0XF0, 0XFA, 0XF1, 0XF0, 0XFA, 0XF0, 0XEF, 0XF9, 0XEF, 0XEE, 0XF7, 0XEF,
    0XEE, 0XF7, 0XF1, 0XEF, 0XF8, 0XF2, 0XEF, 0XF8, 0XF1, 0XEE, 0XF7, 0XF2, 0XEF, 0XF6, 0XF1, 0XF0,
    0XF4, 0XF1, 0XF0, 0XF4, 0XF2, 0XF1, 0XF5, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF2, 0XF1, 0XF4,
    0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF1, 0XF1, 0XF0, 0XF2, 0XF0, 0XEF, 0XF1, 0XF0, 0XEF, 0XF1, 0XEF,
    0XEE, 0XF0, 0XEE, 0XED, 0XF0, 0XEE, 0XED, 0XF0, 0XEC, 0XEB, 0XED, 0XEE, 0XED, 0XEF, 0XEE, 0XED,
    0XEF, 0XF0, 0XED, 0XEF, 0XEF, 0XEC, 0XEE, 0XED, 0XEA, 0XEC, 0XED, 0XEA, 0XEC, 0XEB, 0XE8, 0XEA,
    0XEA, 0XE7, 0XE9, 0XEA, 0XE6, 0XE8, 0XE8, 0XE5, 0XE7, 0XE7, 0XE5, 0XE5, 0XE7, 0XE2, 0XE3, 0XE6,
    0XE2, 0XE3, 0XE4, 0XDF, 0XE0, 0XE2, 0XDE, 0XDE, 0XE0, 0XDB, 0XDC, 0XDE, 0XD7, 0XD8, 0XDC, 0XD4,
    0XD5, 0XD9, 0XD1, 0XD2, 0XD5, 0XCE, 0XD0, 0XD0, 0XC9, 0XCC, 0XCE, 0XC4, 0XC6, 0XCF, 0XC2, 0XC4,
    0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2,
    0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED,
    0XED, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9,
    0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE3,
    0XE1, 0XE1, 0XE2, 0XE0, 0XDF, 0XE1, 0XDF, 0XDD, 0XE0, 0XDD, 0XDA, 0XDF, 0XDC, 0XD8, 0XDD, 0XDA,
    0XD6, 0XDD, 0XD9, 0XD4, 0XDA, 0XD6, 0XD1, 0XD7, 0XD4, 0XCE, 0XD4, 0XD2, 0XC8, 0XD0, 0XCE, 0XC4,
    0XCD, 0XCB, 0XC0, 0XC7, 0XC5, 0XBA, 0XC4, 0XC2, 0XB8, 0XC0, 0XBC, 0XB2, 0XBD, 0XB9, 0XAD, 0XB4,
    0XB1, 0XA1, 0XAF, 0XAB, 0X98, 0XAA, 0XA5, 0X8F, 0XA2, 0X9F, 0X83, 0X9C, 0X99, 0X7D, 0X8F, 0X8B,
    0X6F, 0X8F, 0X8E, 0X6A, 0X8C, 0X8C, 0X62, 0X87, 0X88, 0X5B, 0X86, 0X86, 0X51, 0X75, 0X7B, 0X2F,
    0X6B, 0X76, 0X15, 0X69, 0X75, 0X06, 0X74, 0X7E, 0X0B, 0X6E, 0X77, 0X05, 0X6C, 0X74, 0X02, 0X69,
    0X72, 0X00, 0X65, 0X70, 0X00, 0X61, 0X6B, 0X01, 0X5A, 0X64, 0X04, 0X4D, 0X58, 0X00, 0X58, 0X68,
    0X01, 0X60, 0X76, 0X03, 0X56, 0X6E, 0X01, 0X59, 0X73, 0X01, 0X5F, 0X80, 0X00, 0X61, 0X85, 0X00,
    0X64, 0X85, 0X00, 0X64, 0X85, 0X00, 0X65, 0X86, 0X00, 0X67, 0X89, 0X00, 0X69, 0X8B, 0X00, 0X69,
    0X8C, 0X00, 0X69, 0X8C, 0X01, 0X68, 0X8C, 0X00, 0X67, 0X8B, 0X00, 0X68, 0X8C, 0X01, 0X67, 0X8D,
    0X01, 0X68, 0X8C, 0X00, 0X6B, 0X8E, 0X02, 0X6B, 0X8D, 0X01, 0X6B, 0X8D, 0X00, 0X6B, 0X8F, 0X00,
    0X6E, 0X92, 0X00, 0X6E, 0X92, 0X00, 0X70, 0X93, 0X00, 0X73, 0X96, 0X01, 0X75, 0X98, 0X00, 0X76,
    0X9B, 0X00, 0X79, 0X9F, 0X01, 0X78, 0X9F, 0X00, 0X77, 0X9D, 0X00, 0X79, 0X9D, 0X00, 0X7E, 0XA1,
    0X01, 0X82, 0XA3, 0X00, 0X89, 0XA8, 0X00, 0X8C, 0XAA, 0X00, 0X92, 0XAC, 0X02, 0X95, 0XAF, 0X03,
    0X93, 0XA8, 0X16, 0XC5, 0XCE, 0X80, 0XFA, 0XFB, 0XEC, 0XF0, 0XF1, 0XF1, 0XF2, 0XF2, 0XEC, 0XF6,
    0XF1, 0XF1, 0XF3, 0XF1, 0XEF, 0XF2, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XF3, 0XF1, 0XF0, 0XEF, 0XED,
    0XEC, 0XF0, 0XEE, 0XEE, 0XF1, 0XEF, 0XEF, 0XEE, 0XEC, 0XEB, 0XED, 0XEB, 0XEB, 0XEE, 0XEC, 0XEC,
    0XF0, 0XEE, 0XEE, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE9,
    0XE7, 0XE7, 0XE7, 0XE5, 0XE5, 0XE7, 0XE5, 0XE5, 0XE4, 0XE2, 0XE2, 0XE4, 0XE2, 0XE2, 0XE2, 0XE0,
    0XE0, 0XDF, 0XDD, 0XDC, 0XDD, 0XDC, 0XD8, 0XDA, 0XD9, 0XD5, 0XD8, 0XD6, 0XD2, 0XD7, 0XD5, 0XD1,
    0XD1, 0XCE, 0XCA, 0XCC, 0XC7, 0XC4, 0XC9, 0XC4, 0XC1, 0XC0, 0XBB, 0XB7, 0XBA, 0XB2, 0XAE, 0XB6,
    0XAD, 0XA9, 0XB5, 0XAD, 0XA9, 0XB5, 0XAD, 0XA9, 0XB4, 0XAC, 0XA9, 0XB4, 0XAD, 0XAA, 0XB5, 0XAF,
    0XAB, 0XB0, 0XAD, 0XAE, 0X6E, 0X74, 0X7C, 0X49, 0X58, 0X67, 0X4A, 0X60, 0X70, 0X53, 0X6A, 0X7C,
    0X52, 0X6A, 0X7D, 0X28, 0X43, 0X5F, 0X58, 0X7A, 0X9C, 0X8C, 0XB4, 0XD6, 0X76, 0XA1, 0XCD, 0X74,
    0XA2, 0XCD, 0X96, 0XBF, 0XDC, 0X9D, 0XC3, 0XE6, 0X9D, 0XBF, 0XE6, 0X7E, 0XA5, 0XCE, 0X45, 0X6F,
    0X9A, 0XB4, 0XCD, 0XEF, 0XBE, 0XD7, 0XF6, 0X7C, 0XAA, 0XD5, 0X74, 0XA1, 0XCB, 0X8E, 0XBB, 0XDF,
    0X93, 0XBC, 0XE6, 0XB6, 0XD0, 0XF8, 0XAA, 0XC9, 0XF4, 0XAA, 0XC9, 0XF1, 0X9C, 0XBE, 0XEA, 0X90,
    0XB6, 0XE8, 0XA4, 0XC6, 0XF2, 0X90, 0XB6, 0XE9, 0XA5, 0XC6, 0XF2, 0X9B, 0XC4, 0XF1, 0X9A, 0XC1,
    0XE9, 0XB8, 0XD2, 0XF8, 0XBB, 0XD1, 0XF7, 0X68, 0X94, 0XC1, 0X34, 0X62, 0X97, 0X7F, 0X9B, 0XC7,
    0XD6, 0XDE, 0XEE, 0XED, 0XF1, 0XF4, 0XEE, 0XED, 0XF2, 0XF1, 0XEE, 0XF3, 0XF2, 0XEF, 0XF4, 0XEF,
    0XEF, 0XF3, 0XEE, 0XEE, 0XF3, 0XF1, 0XEE, 0XF4, 0XF1, 0XEE, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0,
    0XF2, 0XF0, 0XEF, 0XF1, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XED, 0XED, 0XED,
    0XEF, 0XEE, 0XEF, 0XEE, 0XED, 0XEF, 0XEC, 0XEB, 0XED, 0XED, 0XEC, 0XEE, 0XED, 0XEC, 0XEE, 0XEB,
    0XEA, 0XEC, 0XEB, 0XEA, 0XEC, 0XEA, 0XE9, 0XEB, 0XE8, 0XE7, 0XE9, 0XE8, 0XE7, 0XE9, 0XE7, 0XE6,
    0XE8, 0XE5, 0XE4, 0XE6, 0XE4, 0XE3, 0XE5, 0XE3, 0XE2, 0XE4, 0XE0, 0XE0, 0XE1, 0XDF, 0XDE, 0XDF,
    0XDD, 0XDC, 0XDE, 0XDB, 0XDA, 0XDD, 0XD6, 0XD5, 0XDA, 0XD2, 0XCF, 0XD7, 0XCA, 0XC6, 0XD1, 0XC3,
    0XBF, 0XCB, 0XBC, 0XBA, 0XC9, 0XB7, 0XB4, 0XC3, 0XB6, 0XAB, 0XC1, 0XB3, 0XA3, 0XC3, 0XA7, 0X9D,
    0XBF, 0X9C, 0X9E, 0XCC, 0X84, 0X81, 0XE1, 0X70, 0X5F, 0XEA, 0X81, 0X67, 0XF6, 0X88, 0X6D, 0XFB,
    0X85, 0X69, 0XFC, 0X74, 0X54, 0XF6, 0X75, 0X5A, 0XF6, 0X79, 0X65, 0XF0, 0X87, 0X7E, 0XEE, 0X87,
    0X88, 0XEF, 0X84, 0X81, 0XF0, 0X83, 0X71, 0XFA, 0X75, 0X5A, 0XF7, 0X75, 0X5C, 0XFA, 0X77, 0X5B,
    0XF8, 0X7A, 0X59, 0XFA, 0X7C, 0X57, 0XFC, 0X78, 0X57, 0XF7, 0X78, 0X57, 0XF8, 0X7C, 0X5A, 0XFC,
    0X7A, 0X59, 0XFB, 0X76, 0X54, 0XF7, 0X7A, 0X57, 0XFA, 0X7D, 0X5A, 0XFC, 0X7E, 0X5B, 0XFB, 0X7B,
    0X5B, 0XF9, 0X7B, 0X5E, 0XFA, 0X7B, 0X5C, 0XFD, 0X7C, 0X64, 0XF1, 0XAC, 0XA4, 0XF7, 0XC0, 0XB9,
    0XFE, 0X9D, 0X8B, 0XF8, 0X76, 0X5C, 0XED, 0X79, 0X5A, 0XFB, 0X77, 0X56, 0XFB, 0X76, 0X57, 0XF7,
    0X76, 0X55, 0XF8, 0X78, 0X54, 0XFD, 0X78, 0X56, 0XFB, 0X78, 0X56, 0XF5, 0X79, 0X56, 0XF9, 0X75,
    0X50, 0XFA, 0X75, 0X56, 0XFA, 0X78, 0X5A, 0XF9, 0X8C, 0X74, 0XEF, 0XD5, 0XCD, 0XF9, 0XF7, 0XF4,
    0XFD, 0XF3, 0XF0, 0XFA, 0XF6, 0XF1, 0XFD, 0XF3, 0XF1, 0XFA, 0XF1, 0XF1, 0XF6, 0XF1, 0XF0, 0XF7,
    0XF1, 0XEF, 0XFA, 0XF0, 0XEF, 0XFA, 0XF1, 0XF0, 0XF9, 0XF0, 0XF0, 0XF9, 0XEF, 0XEE, 0XF7, 0XEF,
    0XEE, 0XF7, 0XF0, 0XEE, 0XF8, 0XF3, 0XF0, 0XF8, 0XF2, 0XF0, 0XF6, 0XF2, 0XF0, 0XF6, 0XF1, 0XF0,
    0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4,
    0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF2, 0XEF, 0XEE, 0XF0, 0XEF, 0XEE, 0XF0, 0XEE, 0XED, 0XEF, 0XEE,
    0XED, 0XEF, 0XEE, 0XED, 0XEF, 0XEE, 0XED, 0XEF, 0XED, 0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XED, 0XEB,
    0XED, 0XEE, 0XEB, 0XED, 0XED, 0XEA, 0XEC, 0XED, 0XE9, 0XEB, 0XEC, 0XE8, 0XEA, 0XEA, 0XE7, 0XE9,
    0XE8, 0XE5, 0XE7, 0XE7, 0XE4, 0XE6, 0XE7, 0XE3, 0XE4, 0XE6, 0XE1, 0XE2, 0XE4, 0XDF, 0XE0, 0XE2,
    0XDD, 0XDE, 0XE2, 0XDC, 0XDD, 0XDF, 0XD9, 0XDA, 0XDB, 0XD6, 0XD7, 0XD9, 0XD2, 0XD3, 0XD5, 0XCE,
    0XCF, 0XD1, 0XCB, 0XCC, 0XCD, 0XC7, 0XC8, 0XC9, 0XC1, 0XC3, 0XCE, 0XC1, 0XC3, 0XCB, 0XAC, 0XB0,
    0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2,
    0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED,
    0XED, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEE, 0XEC, 0XEC, 0XEB, 0XE9, 0XE9,
    0XEA, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7, 0XE7, 0XE7, 0XE5, 0XE5, 0XE7, 0XE5, 0XE4, 0XE5,
    0XE3, 0XE3, 0XE3, 0XE1, 0XE1, 0XE2, 0XE0, 0XE0, 0XE1, 0XDF, 0XDE, 0XDE, 0XDE, 0XD9, 0XDC, 0XDB,
    0XD5, 0XDE, 0XDB, 0XD7, 0XDB, 0XD8, 0XD4, 0XD9, 0XD5, 0XCF, 0XD6, 0XD4, 0XCB, 0XD3, 0XD1, 0XC8,
    0XD0, 0XCE, 0XC5, 0XCB, 0XC9, 0XBF, 0XC8, 0XC6, 0XBC, 0XC1, 0XBF, 0XB5, 0XC1, 0XBD, 0XB2, 0XBB,
    0XB7, 0XAA, 0XB4, 0XB0, 0XA1, 0XAE, 0XAA, 0X97, 0XA8, 0XA5, 0X90, 0XA2, 0X9E, 0X86, 0X9B, 0X97,
    0X7B, 0X94, 0X92, 0X72, 0X90, 0X90, 0X6C, 0X8B, 0X8B, 0X65, 0X87, 0X88, 0X59, 0X84, 0X87, 0X4A,
    0X75, 0X7C, 0X2F, 0X68, 0X72, 0X0B, 0X6A, 0X74, 0X02, 0X70, 0X79, 0X06, 0X6B, 0X74, 0X01, 0X6A,
    0X73, 0X00, 0X6A, 0X72, 0X01, 0X66, 0X70, 0X00, 0X62, 0X6E, 0X01, 0X58, 0X62, 0X03, 0X4C, 0X56,
    0X00, 0X5E, 0X6E, 0X04, 0X61, 0X75, 0X07, 0X56, 0X6D, 0X01, 0X59, 0X76, 0X00, 0X5E, 0X80, 0X00,
    0X63, 0X83, 0X02, 0X64, 0X84, 0X02, 0X64, 0X85, 0X00, 0X67, 0X88, 0X00, 0X67, 0X8A, 0X00, 0X68,
    0X8B, 0X00, 0X69, 0X8B, 0X01, 0X68, 0X8A, 0X00, 0X67, 0X89, 0X00, 0X68, 0X8B, 0X00, 0X69, 0X8C,
    0X01, 0X69, 0X8C, 0X00, 0X6B, 0X8C, 0X01, 0X6C, 0X8D, 0X01, 0X6C, 0X8E, 0X02, 0X6B, 0X8D, 0X00,
    0X6D, 0X91, 0X00, 0X6E, 0X92, 0X01, 0X6F, 0X92, 0X00, 0X73, 0X96, 0X01, 0X75, 0X98, 0X01, 0X74,
    0X98, 0X00, 0X79, 0X9E, 0X01, 0X7B, 0XA0, 0X00, 0X79, 0X9F, 0X00, 0X79, 0X9F, 0X00, 0X79, 0X9F,
    0X00, 0X80, 0XA2, 0X03, 0X84, 0XA4, 0X02, 0X88, 0XA7, 0X02, 0X89, 0XAA, 0X00, 0X94, 0XAF, 0X01,
    0X96, 0XAC, 0X00, 0X95, 0XA9, 0X17, 0XCB, 0XD5, 0X93, 0XFA, 0XFA, 0XF2, 0XF2, 0XEE, 0XF0, 0XF6,
    0XF0, 0XF0, 0XF3, 0XF1, 0XF0, 0XF2, 0XF1, 0XEF, 0XF2, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XF1, 0XEF,
    0XEE, 0XF0, 0XEE, 0XED, 0XEF, 0XED, 0XEC, 0XEE, 0XEC, 0XEC, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED,
    0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE9,
    0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE8, 0XE6, 0XE6, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE1, 0XDF,
    0XDF, 0XDF, 0XDE, 0XDD, 0XDE, 0XDC, 0XDA, 0XDD, 0XDC, 0XD8, 0XDB, 0XD9, 0XD5, 0XDA, 0XD6, 0XD3,
    0XD6, 0XD0, 0XCD, 0XD1, 0XCC, 0XC9, 0XC9, 0XC5, 0XC2, 0XC1, 0XBC, 0XB8, 0XBC, 0XB3, 0XAF, 0XB6,
    0XAE, 0XA9, 0XB1, 0XAA, 0XA7, 0XB3, 0XAC, 0XA9, 0XB5, 0XAE, 0XAB, 0XB4, 0XAD, 0XAA, 0XB4, 0XAD,
    0XAA, 0XB6, 0XB2, 0XB3, 0X98, 0XA0, 0XA9, 0X54, 0X6A, 0X80, 0X70, 0X8F, 0XAB, 0X63, 0X82, 0X9F,
    0X89, 0XA8, 0XC5, 0X53, 0X76, 0X9B, 0X34, 0X5B, 0X82, 0X8A, 0XB2, 0XD6, 0X6D, 0X97, 0XC6, 0X71,
    0XA0, 0XCD, 0X95, 0XBD, 0XDE, 0X96, 0XBA, 0XDE, 0X9F, 0XC0, 0XE5, 0X9B, 0XC0, 0XE5, 0X7C, 0XA4,
    0XCE, 0XB3, 0XC9, 0XEB, 0XBB, 0XD3, 0XF1, 0X75, 0XA7, 0XD7, 0X7F, 0XAA, 0XDB, 0X9C, 0XC2, 0XE8,
    0X94, 0XBC, 0XE6, 0XAF, 0XCA, 0XEE, 0XB6, 0XD2, 0XF3, 0XB8, 0XD1, 0XF3, 0XA4, 0XC7, 0XF0, 0X94,
    0XBB, 0XEC, 0XAA, 0XCC, 0XF8, 0X94, 0XBD, 0XEF, 0XA5, 0XC8, 0XF1, 0X95, 0XBF, 0XF0, 0X9F, 0XC4,
    0XEE, 0XB2, 0XCC, 0XF1, 0XC4, 0XDB, 0XFA, 0X7D, 0XA9, 0XDB, 0X41, 0X71, 0XA8, 0XA7, 0XC0, 0XE6,
    0XE4, 0XE8, 0XF4, 0XED, 0XF0, 0XF3, 0XEF, 0XEE, 0XF2, 0XF3, 0XEF, 0XF4, 0XF1, 0XEE, 0XF3, 0XEE,
    0XEF, 0XF3, 0XEF, 0XEF, 0XF4, 0XF1, 0XEE, 0XF3, 0XF1, 0XEE, 0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF,
    0XF2, 0XEF, 0XEE, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XEF, 0XED, 0XED, 0XEE, 0XEE, 0XEE, 0XEE,
    0XEE, 0XED, 0XF0, 0XEE, 0XED, 0XEF, 0XED, 0XEC, 0XEE, 0XED, 0XEC, 0XEE, 0XEC, 0XEB, 0XED, 0XEC,
    0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XE9, 0XE8, 0XEA, 0XE9, 0XE8, 0XEA, 0XE7, 0XE6, 0XE8, 0XE7, 0XE6,
    0XE8, 0XE5, 0XE4, 0XE6, 0XE4, 0XE3, 0XE5, 0XE2, 0XE1, 0XE3, 0XDF, 0XDE, 0XE0, 0XDD, 0XDC, 0XDE,
    0XDB, 0XDA, 0XDC, 0XD7, 0XD7, 0XDA, 0XD3, 0XD2, 0XD7, 0XCD, 0XC9, 0XD3, 0XC5, 0XC1, 0XCC, 0XC1,
    0XBC, 0XCA, 0XBA, 0XB6, 0XC7, 0XB2, 0XAE, 0XC1, 0XB0, 0XA7, 0XBE, 0XAE, 0XA1, 0XBE, 0XA2, 0X9D,
    0XC1, 0X92, 0X97, 0XD3, 0X76, 0X77, 0XDE, 0X71, 0X64, 0XED, 0X7B, 0X65, 0XF5, 0X7C, 0X64, 0XF9,
    0X71, 0X58, 0XF6, 0X6E, 0X55, 0XF6, 0X6D, 0X5E, 0XEB, 0X7B, 0X7A, 0XDF, 0XA4, 0XB1, 0XF0, 0X89,
    0X9F, 0XE7, 0X6C, 0X75, 0XDB, 0X80, 0X71, 0XFB, 0X75, 0X59, 0XF9, 0X72, 0X56, 0XFB, 0X75, 0X5A,
    0XFB, 0X78, 0X5C, 0XF8, 0X78, 0X58, 0XF8, 0X77, 0X59, 0XF8, 0X78, 0X5A, 0XFA, 0X76, 0X58, 0XFA,
    0X77, 0X58, 0XFA, 0X77, 0X58, 0XF8, 0X7C, 0X5B, 0XFA, 0X7E, 0X5E, 0XFC, 0X7C, 0X5C, 0XF6, 0X7C,
    0X5D, 0XFA, 0X7D, 0X61, 0XF9, 0X7C, 0X60, 0XF5, 0X9A, 0X87, 0XF6, 0XBD, 0XB7, 0XFD, 0XA5, 0X98,
    0XF9, 0X7E, 0X65, 0XF3, 0X77, 0X57, 0XFD, 0X76, 0X55, 0XFB, 0X75, 0X54, 0XF8, 0X78, 0X56, 0XF8,
    0X79, 0X56, 0XFB, 0X79, 0X56, 0XFD, 0X76, 0X54, 0XF9, 0X78, 0X57, 0XF8, 0X78, 0X57, 0XF8, 0X79,
    0X56, 0XFA, 0X78, 0X55, 0XFA, 0X7F, 0X61, 0XF2, 0XB6, 0XAA, 0XF2, 0XF2, 0XF3, 0XFB, 0XF5, 0XEF,
    0XFC, 0XF4, 0XEE, 0XFD, 0XF3, 0XF0, 0XFB, 0XF1, 0XF2, 0XF7, 0XF0, 0XF1, 0XF6, 0XF2, 0XF1, 0XFA,
    0XF1, 0XEF, 0XFB, 0XF1, 0XEE, 0XF9, 0XF1, 0XEF, 0XF8, 0XF0, 0XF0, 0XF8, 0XEF, 0XEE, 0XF7, 0XEF,
    0XEE, 0XF6, 0XEF, 0XEE, 0XF5, 0XF2, 0XF0, 0XF6, 0XF1, 0XF0, 0XF6, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0,
    0XF4, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4,
    0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF2, 0XEF, 0XEE, 0XF0, 0XEE, 0XED, 0XEF, 0XEE, 0XED, 0XEF, 0XEE,
    0XED, 0XEF, 0XEF, 0XEE, 0XF0, 0XEC, 0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XEB, 0XEA, 0XEC, 0XE9, 0XE7,
    0XE9, 0XEC, 0XE9, 0XEB, 0XEC, 0XE8, 0XEA, 0XED, 0XE7, 0XE9, 0XEA, 0XE5, 0XE7, 0XE8, 0XE5, 0XE7,
    0XE6, 0XE3, 0XE5, 0XE6, 0XE1, 0XE3, 0XE6, 0XE0, 0XE2, 0XE3, 0XDE, 0XDF, 0XE3, 0XDD, 0XDE, 0XE0,
    0XDA, 0XDB, 0XDF, 0XD9, 0XDA, 0XDB, 0XD4, 0XD5, 0XD5, 0XCF, 0XD1, 0XD4, 0XCD, 0XCE, 0XD0, 0XCA,
    0XCB, 0XCC, 0XC4, 0XC5, 0XCE, 0XC1, 0XC2, 0XD3, 0XBB, 0XBD, 0XBD, 0X9D, 0XA0, 0XA9, 0X72, 0X77,
    0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF3, 0XF1, 0XF1, 0XF3,
    0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XF1, 0XEF,
    0XEF, 0XF0, 0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA,
    0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE5, 0XE6, 0XE4, 0XE4, 0XE5,
    0XE3, 0XE3, 0XE4, 0XE2, 0XE2, 0XE3, 0XE1, 0XE1, 0XE2, 0XE0, 0XDF, 0XE1, 0XE0, 0XDC, 0XDF, 0XDE,
    0XD9, 0XDF, 0XDB, 0XD8, 0XDC, 0XDA, 0XD6, 0XDA, 0XD6, 0XD2, 0XD9, 0XD4, 0XD0, 0XD5, 0XD2, 0XCC,
    0XD3, 0XD0, 0XC8, 0XD0, 0XCE, 0XC5, 0XCB, 0XC9, 0XC0, 0XC6, 0XC4, 0XBB, 0XC5, 0XC0, 0XB7, 0XBF,
    0XBB, 0XB0, 0XBA, 0XB6, 0XAA, 0XB4, 0XB0, 0XA1, 0XAB, 0XA7, 0X96, 0XA4, 0XA0, 0X8B, 0XA2, 0X9D,
    0X82, 0X9A, 0X97, 0X79, 0X91, 0X8F, 0X71, 0X8E, 0X8D, 0X6B, 0X8A, 0X8B, 0X63, 0X89, 0X88, 0X58,
    0X88, 0X86, 0X4F, 0X76, 0X7B, 0X25, 0X68, 0X71, 0X04, 0X6A, 0X73, 0X01, 0X6A, 0X74, 0X00, 0X6B,
    0X74, 0X00, 0X6A, 0X71, 0X03, 0X66, 0X70, 0X00, 0X66, 0X71, 0X00, 0X5F, 0X69, 0X02, 0X57, 0X61,
    0X01, 0X50, 0X5B, 0X00, 0X5F, 0X70, 0X05, 0X5C, 0X73, 0X03, 0X51, 0X6B, 0X00, 0X5A, 0X76, 0X02,
    0X60, 0X7E, 0X01, 0X62, 0X81, 0X00, 0X66, 0X87, 0X02, 0X67, 0X89, 0X01, 0X67, 0X8A, 0X00, 0X68,
    0X8B, 0X00, 0X68, 0X8A, 0X01, 0X68, 0X8A, 0X01, 0X69, 0X89, 0X00, 0X67, 0X88, 0X00, 0X6B, 0X8E,
    0X03, 0X6E, 0X90, 0X05, 0X6A, 0X8B, 0X01, 0X6B, 0X8D, 0X00, 0X6C, 0X8D, 0X01, 0X6C, 0X8E, 0X00,
    0X6C, 0X8F, 0X00, 0X6C, 0X8F, 0X00, 0X6E, 0X92, 0X01, 0X6F, 0X93, 0X00, 0X72, 0X95, 0X00, 0X74,
    0X97, 0X00, 0X78, 0X9B, 0X01, 0X7F, 0X9F, 0X03, 0X7C, 0X9F, 0X00, 0X78, 0X9E, 0X00, 0X79, 0X9F,
    0X00, 0X7A, 0X9E, 0X00, 0X80, 0XA1, 0X01, 0X83, 0XA4, 0X00, 0X86, 0XA9, 0X01, 0X8B, 0XA9, 0X00,
    0X96, 0XAD, 0X02, 0X97, 0XAC, 0X03, 0X97, 0XAC, 0X22, 0XD8, 0XDE, 0XA5, 0XF9, 0XF8, 0XF0, 0XEF,
    0XF0, 0XEA, 0XF2, 0XF0, 0XEF, 0XF1, 0XEF, 0XEE, 0XF0, 0XEE, 0XED, 0XF2, 0XF0, 0XEF, 0XF2, 0XF0,
    0XEF, 0XF0, 0XEE, 0XED, 0XF0, 0XEE, 0XED, 0XF0, 0XED, 0XED, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED,
    0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEA, 0XE8, 0XE8, 0XE9,
    0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE1, 0XDF,
    0XDF, 0XE1, 0XDF, 0XDF, 0XDE, 0XDC, 0XDB, 0XDD, 0XDB, 0XD7, 0XDB, 0XD9, 0XD5, 0XDB, 0XD5, 0XD2,
    0XD8, 0XD1, 0XCE, 0XD2, 0XCA, 0XC8, 0XCA, 0XC5, 0XC4, 0XC3, 0XBD, 0XBB, 0XBE, 0XB4, 0XB1, 0XB6,
    0XAE, 0XAA, 0XB3, 0XAC, 0XA9, 0XB4, 0XAE, 0XAA, 0XB5, 0XAE, 0XAB, 0XB9, 0XB2, 0XAF, 0XBA, 0XB3,
    0XB0, 0XBA, 0XB4, 0XB2, 0XA7, 0XAD, 0XB7, 0X7B, 0X95, 0XB0, 0X72, 0X98, 0XBB, 0X6F, 0X95, 0XB7,
    0X86, 0XAA, 0XCC, 0X76, 0X9B, 0XC3, 0X5E, 0X85, 0XAF, 0X88, 0XAF, 0XD7, 0X6E, 0X97, 0XC9, 0X70,
    0X9D, 0XCF, 0X93, 0XBA, 0XE0, 0X90, 0XB3, 0XDA, 0XA3, 0XC0, 0XE7, 0XA6, 0XC7, 0XEA, 0X91, 0XB7,
    0XE0, 0XB8, 0XCC, 0XED, 0XB8, 0XD5, 0XF1, 0X71, 0XA6, 0XDA, 0X7F, 0XA5, 0XE0, 0XA6, 0XC7, 0XF0,
    0X92, 0XBE, 0XE2, 0XB0, 0XCE, 0XED, 0XB3, 0XCD, 0XEC, 0XC2, 0XDA, 0XFB, 0X98, 0XBF, 0XE9, 0X8C,
    0XB7, 0XEA, 0XA3, 0XC6, 0XF4, 0X87, 0XB3, 0XE2, 0XAD, 0XCE, 0XF4, 0XA1, 0XC6, 0XF3, 0XA9, 0XC9,
    0XEF, 0XA5, 0XC6, 0XED, 0XC3, 0XDE, 0XFC, 0X5B, 0X80, 0XBF, 0X62, 0X87, 0XC5, 0XB9, 0XD1, 0XEF,
    0XE4, 0XEA, 0XEF, 0XEF, 0XF1, 0XF5, 0XF1, 0XEF, 0XF4, 0XF3, 0XEE, 0XF5, 0XF2, 0XEF, 0XF5, 0XEF,
    0XF0, 0XF4, 0XF0, 0XF0, 0XF3, 0XF2, 0XEE, 0XF2, 0XF1, 0XEE, 0XF4, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF,
    0XF1, 0XEF, 0XEE, 0XF0, 0XEF, 0XEF, 0XEF, 0XF0, 0XF0, 0XF0, 0XEF, 0XEF, 0XEF, 0XEF, 0XEE, 0XEF,
    0XEF, 0XEE, 0XF0, 0XED, 0XEC, 0XEE, 0XEE, 0XED, 0XEF, 0XEC, 0XEB, 0XED, 0XEC, 0XEB, 0XED, 0XEB,
    0XEA, 0XEC, 0XEA, 0XE9, 0XEB, 0XEA, 0XE9, 0XEB, 0XE8, 0XE7, 0XE9, 0XE7, 0XE6, 0XE8, 0XE5, 0XE4,
    0XE6, 0XE4, 0XE3, 0XE5, 0XE2, 0XE1, 0XE3, 0XE1, 0XE0, 0XE2, 0XDE, 0XDD, 0XDF, 0XDB, 0XDA, 0XDC,
    0XDA, 0XD9, 0XDB, 0XD6, 0XD5, 0XDA, 0XD1, 0XCF, 0XD6, 0XC9, 0XC5, 0XD0, 0XC4, 0XBF, 0XCD, 0XBD,
    0XB7, 0XC7, 0XB6, 0XAF, 0XC0, 0XB0, 0XA9, 0XBF, 0XAA, 0XA2, 0XBA, 0XA7, 0X9F, 0XB6, 0X9E, 0X9D,
    0XC2, 0X81, 0X88, 0XD1, 0X72, 0X76, 0XE3, 0X6C, 0X64, 0XEB, 0X6A, 0X5B, 0XEF, 0X67, 0X59, 0XEB,
    0X68, 0X5C, 0XE7, 0X7C, 0X7A, 0XEB, 0X7C, 0X85, 0XDF, 0X87, 0X9B, 0XDE, 0X95, 0XAD, 0XE5, 0X6C,
    0X8A, 0XD4, 0X6D, 0X83, 0XD9, 0X7D, 0X73, 0XF7, 0X75, 0X5B, 0XF6, 0X73, 0X5B, 0XF6, 0X73, 0X5A,
    0XFD, 0X73, 0X59, 0XF7, 0X76, 0X59, 0XF8, 0X76, 0X5A, 0XF9, 0X76, 0X5A, 0XFA, 0X74, 0X58, 0XF9,
    0X73, 0X57, 0XF6, 0X76, 0X5A, 0XF8, 0X7E, 0X60, 0XFC, 0X7E, 0X5F, 0XF9, 0X7D, 0X5F, 0XF7, 0X7D,
    0X60, 0XFA, 0X7A, 0X5E, 0XF8, 0X8C, 0X75, 0XF0, 0XBC, 0XAD, 0XFD, 0XBA, 0XAD, 0XFE, 0X8A, 0X77,
    0XF4, 0X77, 0X5A, 0XF7, 0X7A, 0X57, 0XFB, 0X77, 0X56, 0XF8, 0X77, 0X53, 0XFA, 0X78, 0X51, 0XFD,
    0X77, 0X52, 0XFC, 0X77, 0X54, 0XF9, 0X77, 0X54, 0XF9, 0X75, 0X54, 0XF8, 0X74, 0X51, 0XF8, 0X79,
    0X55, 0XFB, 0X7B, 0X59, 0XF3, 0X97, 0X81, 0XEE, 0XE1, 0XDF, 0XFC, 0XF3, 0XF5, 0XF7, 0XF4, 0XEF,
    0XFA, 0XF3, 0XF1, 0XFB, 0XF1, 0XF1, 0XF7, 0XEF, 0XF1, 0XF7, 0XEF, 0XF0, 0XFA, 0XF0, 0XF0, 0XFA,
    0XF2, 0XF0, 0XF8, 0XF3, 0XF0, 0XF8, 0XEF, 0XEF, 0XF6, 0XEF, 0XEF, 0XF5, 0XEE, 0XEE, 0XF4, 0XEE,
    0XEE, 0XF4, 0XEF, 0XEF, 0XF5, 0XF1, 0XEF, 0XF5, 0XF1, 0XF0, 0XF5, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF,
    0XF1, 0XF0, 0XEF, 0XF0, 0XF1, 0XF0, 0XF3, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4,
    0XF1, 0XF0, 0XF4, 0XEE, 0XED, 0XF0, 0XEE, 0XEE, 0XF0, 0XEF, 0XEE, 0XF0, 0XEE, 0XED, 0XEF, 0XED,
    0XEC, 0XEE, 0XEC, 0XEB, 0XED, 0XEA, 0XEA, 0XEC, 0XEA, 0XE9, 0XEB, 0XEC, 0XEB, 0XED, 0XE7, 0XE5,
    0XE7, 0XEA, 0XE7, 0XE9, 0XEA, 0XE5, 0XE7, 0XEA, 0XE5, 0XE7, 0XE9, 0XE5, 0XE7, 0XE8, 0XE3, 0XE5,
    0XE6, 0XE2, 0XE4, 0XE3, 0XDF, 0XE1, 0XE2, 0XDD, 0XDF, 0XE0, 0XDB, 0XDC, 0XDF, 0XD8, 0XD9, 0XDD,
    0XD5, 0XD6, 0XDB, 0XD3, 0XD4, 0XD6, 0XCF, 0XD0, 0XD2, 0XCA, 0XCC, 0XD0, 0XC8, 0XC9, 0XCC, 0XC3,
    0XC4, 0XCC, 0XBF, 0XBF, 0XD0, 0XB5, 0XB7, 0XBD, 0X8E, 0X91, 0XA6, 0X65, 0X6B, 0XA6, 0X59, 0X60,
    0XF6, 0XF4, 0XF4, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF3,
    0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE,
    0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XED, 0XEB, 0XEB, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC,
    0XEC, 0XEA, 0XEA, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7, 0XE6, 0XE7, 0XE5, 0XE5, 0XE5,
    0XE3, 0XE3, 0XE5, 0XE3, 0XE3, 0XE3, 0XE1, 0XE1, 0XE2, 0XE0, 0XDF, 0XE2, 0XE0, 0XDD, 0XE0, 0XDF,
    0XDB, 0XE1, 0XDE, 0XDA, 0XDE, 0XDC, 0XD7, 0XDC, 0XD9, 0XD5, 0XDA, 0XD6, 0XD2, 0XD7, 0XD3, 0XCE,
    0XD6, 0XD2, 0XCC, 0XD2, 0XCE, 0XC7, 0XCF, 0XCC, 0XC3, 0XCC, 0XCA, 0XC0, 0XC8, 0XC4, 0XBA, 0XC5,
    0XC0, 0XB7, 0XBE, 0XBA, 0XAF, 0XB8, 0XB5, 0XA8, 0XB3, 0XAE, 0XA0, 0XAB, 0XA6, 0X95, 0XA7, 0XA3,
    0X8C, 0XA0, 0X9D, 0X81, 0X97, 0X95, 0X76, 0X8F, 0X8E, 0X6E, 0X8C, 0X8A, 0X68, 0X8A, 0X88, 0X60,
    0X8A, 0X87, 0X5B, 0X89, 0X88, 0X48, 0X6E, 0X74, 0X16, 0X68, 0X74, 0X00, 0X6C, 0X77, 0X00, 0X6B,
    0X73, 0X01, 0X6B, 0X72, 0X03, 0X6A, 0X74, 0X01, 0X68, 0X73, 0X01, 0X64, 0X6F, 0X00, 0X62, 0X6C,
    0X02, 0X51, 0X59, 0X01, 0X50, 0X5C, 0X00, 0X5F, 0X74, 0X05, 0X58, 0X6F, 0X02, 0X54, 0X6C, 0X01,
    0X5C, 0X77, 0X02, 0X61, 0X7F, 0X02, 0X62, 0X83, 0X00, 0X66, 0X88, 0X01, 0X6A, 0X8B, 0X02, 0X66,
    0X88, 0X00, 0X68, 0X89, 0X00, 0X6A, 0X8B, 0X00, 0X6C, 0X8D, 0X01, 0X6B, 0X8C, 0X01, 0X6C, 0X8C,
    0X02, 0X6C, 0X8D, 0X02, 0X68, 0X8A, 0X00, 0X6A, 0X8B, 0X00, 0X6D, 0X8D, 0X00, 0X6D, 0X8F, 0X00,
    0X6D, 0X90, 0X00, 0X6F, 0X91, 0X01, 0X70, 0X92, 0X03, 0X71, 0X93, 0X03, 0X70, 0X92, 0X00, 0X71,
    0X94, 0X00, 0X75, 0X96, 0X00, 0X79, 0X98, 0X00, 0X7A, 0X9B, 0X00, 0X7A, 0X9D, 0X00, 0X7B, 0XA1,
    0X02, 0X7C, 0XA1, 0X01, 0X7B, 0X9E, 0X00, 0X7E, 0XA2, 0X00, 0X80, 0XA3, 0X01, 0X84, 0XA4, 0X01,
    0X8C, 0XA7, 0X00, 0X94, 0XAA, 0X02, 0X91, 0XAA, 0X00, 0X9A, 0XAF, 0X30, 0XDE, 0XE5, 0XB6, 0XF6,
    0XF9, 0XED, 0XEE, 0XEF, 0XED, 0XF3, 0XF1, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XF0, 0XED, 0XF4, 0XEF,
    0XEE, 0XF3, 0XED, 0XF0, 0XEF, 0XEF, 0XEE, 0XEF, 0XEF, 0XED, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC,
    0XEE, 0XEC, 0XEC, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA,
    0XE8, 0XE8, 0XE7, 0XE5, 0XE5, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE2, 0XE0,
    0XE0, 0XE0, 0XDE, 0XDE, 0XDF, 0XDD, 0XDC, 0XDE, 0XDB, 0XD8, 0XDD, 0XD8, 0XD7, 0XDA, 0XD4, 0XD3,
    0XD7, 0XD0, 0XD0, 0XD3, 0XCC, 0XCC, 0XCE, 0XC7, 0XC7, 0XC4, 0XBF, 0XBD, 0XBE, 0XB6, 0XB2, 0XB9,
    0XB1, 0XAE, 0XB8, 0XB1, 0XAF, 0XB6, 0XB0, 0XAE, 0XB8, 0XB2, 0XAF, 0XBC, 0XB5, 0XB4, 0XBB, 0XB4,
    0XB4, 0XBB, 0XB3, 0XB0, 0XA9, 0XAD, 0XB5, 0X7F, 0X96, 0XB2, 0X74, 0X99, 0XBE, 0X77, 0X9D, 0XC3,
    0X7B, 0XA0, 0XC3, 0X80, 0XA5, 0XCE, 0X6E, 0X95, 0XC1, 0X82, 0XA6, 0XD0, 0X71, 0X98, 0XCA, 0X72,
    0XA0, 0XD3, 0X8E, 0XB2, 0XDA, 0X8C, 0XAE, 0XD7, 0XA5, 0XC2, 0XE9, 0XA9, 0XC7, 0XED, 0X92, 0XB7,
    0XE0, 0XBB, 0XD1, 0XEF, 0XBC, 0XD9, 0XF4, 0X72, 0XA6, 0XDE, 0X7D, 0XA2, 0XDA, 0X9E, 0XC0, 0XEC,
    0X8E, 0XBB, 0XE4, 0XA3, 0XC7, 0XE9, 0XB1, 0XCD, 0XED, 0XC3, 0XDE, 0XFD, 0X9E, 0XC6, 0XEF, 0X8C,
    0XB7, 0XE9, 0XA6, 0XC8, 0XF9, 0X92, 0XBB, 0XEA, 0XB2, 0XD2, 0XF5, 0X9B, 0XC0, 0XED, 0XA1, 0XC5,
    0XEE, 0XA7, 0XCC, 0XF1, 0XBA, 0XD6, 0XF8, 0X41, 0X62, 0XA3, 0X72, 0X8F, 0XCB, 0XC5, 0XDA, 0XF4,
    0XE7, 0XEE, 0XF1, 0XEF, 0XEF, 0XF4, 0XF1, 0XEF, 0XF4, 0XF3, 0XEF, 0XF4, 0XF1, 0XEE, 0XF4, 0XF0,
    0XEF, 0XF4, 0XF0, 0XF0, 0XF2, 0XF1, 0XEF, 0XF2, 0XF0, 0XEE, 0XF3, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF,
    0XF2, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XF1, 0XEE, 0XEE, 0XEF, 0XEE, 0XEE, 0XEF, 0XEF, 0XEE, 0XF0,
    0XEF, 0XEE, 0XF0, 0XED, 0XEC, 0XEE, 0XED, 0XEC, 0XEF, 0XEC, 0XEB, 0XED, 0XEA, 0XE9, 0XEB, 0XE9,
    0XE8, 0XEA, 0XE9, 0XE8, 0XEA, 0XE8, 0XE7, 0XE9, 0XE8, 0XE7, 0XE9, 0XE6, 0XE5, 0XE7, 0XE4, 0XE3,
    0XE5, 0XE4, 0XE3, 0XE5, 0XE1, 0XE0, 0XE2, 0XDF, 0XDE, 0XE0, 0XDC, 0XDC, 0XDD, 0XD9, 0XD8, 0XDA,
    0XD6, 0XD5, 0XD8, 0XD1, 0XD0, 0XD4, 0XCC, 0XC9, 0XD1, 0XC5, 0XC1, 0XCC, 0XC0, 0XBB, 0XC9, 0XB7,
    0XB2, 0XC3, 0XB2, 0XAC, 0XBD, 0XAB, 0XA5, 0XBC, 0XA6, 0XA0, 0XB9, 0XA5, 0X9E, 0XB7, 0X9B, 0X9F,
    0XC9, 0X7B, 0X89, 0XD5, 0X5F, 0X69, 0XCD, 0X6D, 0X6F, 0XDB, 0X74, 0X72, 0XEB, 0X6C, 0X67, 0XE8,
    0X66, 0X69, 0XDD, 0X71, 0X84, 0XD4, 0X87, 0XA0, 0XDC, 0X95, 0XB2, 0XE3, 0X8D, 0XA8, 0XE9, 0X55,
    0X76, 0XC4, 0X84, 0X9A, 0XE8, 0X78, 0X70, 0XF3, 0X76, 0X63, 0XF7, 0X7D, 0X68, 0XF8, 0X76, 0X5C,
    0XFC, 0X73, 0X5B, 0XF6, 0X72, 0X58, 0XF9, 0X77, 0X5C, 0XFC, 0X75, 0X5C, 0XFA, 0X72, 0X57, 0XF9,
    0X74, 0X5B, 0XF9, 0X7B, 0X62, 0XFC, 0X7D, 0X62, 0XFC, 0X7B, 0X5F, 0XF7, 0X7E, 0X63, 0XF9, 0X82,
    0X67, 0XFC, 0X7D, 0X5F, 0XF4, 0XA7, 0X96, 0XF6, 0XC5, 0XBC, 0XFE, 0X9D, 0X89, 0XF6, 0X7B, 0X61,
    0XF4, 0X78, 0X5A, 0XFB, 0X77, 0X54, 0XF5, 0X78, 0X57, 0XF5, 0X79, 0X55, 0XFB, 0X77, 0X4F, 0XFD,
    0X79, 0X53, 0XFD, 0X77, 0X54, 0XF8, 0X79, 0X55, 0XFC, 0X73, 0X54, 0XF7, 0X72, 0X4F, 0XFA, 0X7A,
    0X53, 0XFB, 0X86, 0X67, 0XEE, 0XC7, 0XBD, 0XF7, 0XF1, 0XF2, 0XFC, 0XF2, 0XF1, 0XF9, 0XF5, 0XF1,
    0XF9, 0XF2, 0XF2, 0XF8, 0XF0, 0XF2, 0XF7, 0XEF, 0XEF, 0XF9, 0XF0, 0XF0, 0XFC, 0XF0, 0XF0, 0XF9,
    0XF1, 0XF0, 0XF6, 0XF0, 0XEE, 0XF6, 0XEF, 0XEE, 0XF5, 0XEE, 0XEE, 0XF4, 0XED, 0XED, 0XF3, 0XEE,
    0XED, 0XF3, 0XEF, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE,
    0XF1, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF1, 0XF0, 0XF3, 0XEF, 0XEE, 0XF2,
    0XEF, 0XEE, 0XF1, 0XED, 0XEC, 0XEF, 0XEE, 0XEC, 0XEE, 0XED, 0XEC, 0XEE, 0XEB, 0XEA, 0XEC, 0XEB,
    0XEA, 0XEC, 0XEC, 0XEB, 0XED, 0XEA, 0XE9, 0XEB, 0XE9, 0XE8, 0XEA, 0XEA, 0XE9, 0XEB, 0XEA, 0XE8,
    0XEA, 0XEA, 0XE7, 0XE9, 0XEA, 0XE5, 0XE7, 0XE8, 0XE3, 0XE5, 0XE6, 0XE1, 0XE3, 0XE6, 0XE1, 0XE3,
    0XE4, 0XE0, 0XE2, 0XE1, 0XDC, 0XDE, 0XE1, 0XD9, 0XDC, 0XDE, 0XD7, 0XD8, 0XD9, 0XD5, 0XD6, 0XD5,
    0XD2, 0XD2, 0XD7, 0XCE, 0XCF, 0XD3, 0XC9, 0XCB, 0XCC, 0XC3, 0XC7, 0XCB, 0XC0, 0XC3, 0XCF, 0XBD,
    0XBF, 0XC6, 0XA8, 0XA8, 0XAE, 0X7C, 0X7F, 0XA5, 0X5F, 0X65, 0XAA, 0X55, 0X5D, 0XAB, 0X56, 0X5D,
    0XF6, 0XF4, 0XF4, 0XF4, 0XF2, 0XF2, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF3,
    0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE,
    0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC,
    0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE5,
    0XE3, 0XE3, 0XE5, 0XE3, 0XE3, 0XE5, 0XE3, 0XE3, 0XE4, 0XE2, 0XE2, 0XE3, 0XE1, 0XE1, 0XE2, 0XE0,
    0XDF, 0XE0, 0XE0, 0XDB, 0XDE, 0XDF, 0XD9, 0XDD, 0XDC, 0XD6, 0XDD, 0XD9, 0XD4, 0XDA, 0XD6, 0XD1,
    0XD8, 0XD3, 0XCE, 0XD6, 0XD0, 0XCA, 0XD4, 0XD0, 0XC7, 0XCF, 0XCD, 0XC3, 0XCA, 0XC8, 0XBE, 0XC8,
    0XC4, 0XBA, 0XC2, 0XBE, 0XB3, 0XBD, 0XB9, 0XAE, 0XBB, 0XB4, 0XA9, 0XB2, 0XAD, 0X9E, 0XAB, 0XA8,
    0X94, 0XA1, 0X9F, 0X88, 0X9F, 0X9D, 0X82, 0X97, 0X95, 0X76, 0X91, 0X8F, 0X6D, 0X8E, 0X8C, 0X65,
    0X8B, 0X89, 0X61, 0X8B, 0X88, 0X5C, 0X83, 0X86, 0X41, 0X67, 0X71, 0X0B, 0X69, 0X73, 0X00, 0X6D,
    0X74, 0X02, 0X6D, 0X74, 0X02, 0X6F, 0X76, 0X02, 0X6C, 0X75, 0X01, 0X6A, 0X75, 0X01, 0X65, 0X6E,
    0X01, 0X5F, 0X66, 0X03, 0X4E, 0X56, 0X00, 0X52, 0X5D, 0X02, 0X60, 0X71, 0X08, 0X59, 0X6F, 0X02,
    0X57, 0X70, 0X01, 0X5A, 0X77, 0X01, 0X5E, 0X7E, 0X00, 0X65, 0X86, 0X02, 0X67, 0X88, 0X02, 0X66,
    0X86, 0X00, 0X6A, 0X89, 0X00, 0X6D, 0X8B, 0X00, 0X72, 0X90, 0X01, 0X70, 0X8F, 0X02, 0X6B, 0X8A,
    0X00, 0X6B, 0X8A, 0X01, 0X6B, 0X8D, 0X02, 0X6D, 0X8D, 0X01, 0X70, 0X90, 0X02, 0X6E, 0X8F, 0X00,
    0X6E, 0X8F, 0X00, 0X6E, 0X8F, 0X00, 0X6F, 0X90, 0X01, 0X70, 0X91, 0X01, 0X70, 0X91, 0X00, 0X71,
    0X92, 0X02, 0X73, 0X95, 0X01, 0X76, 0X98, 0X00, 0X79, 0X9C, 0X00, 0X7C, 0X9F, 0X00, 0X7F, 0XA4,
    0X03, 0X7D, 0XA2, 0X02, 0X79, 0X9D, 0X00, 0X7B, 0X9E, 0X01, 0X7B, 0XA0, 0X02, 0X80, 0XA3, 0X01,
    0X86, 0XA5, 0X00, 0X8C, 0XA7, 0X00, 0X92, 0XAC, 0X03, 0X8C, 0XAB, 0X02, 0X9D, 0XAD, 0X3A, 0XE8,
    0XE8, 0XC1, 0XF5, 0XF8, 0XF0, 0XF1, 0XF0, 0XEC, 0XF0, 0XEF, 0XF0, 0XF1, 0XF1, 0XEB, 0XF6, 0XEE,
    0XEC, 0XF6, 0XEB, 0XF2, 0XED, 0XEE, 0XEC, 0XEB, 0XEE, 0XE8, 0XEF, 0XEE, 0XEC, 0XEF, 0XED, 0XED,
    0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEA,
    0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE8, 0XE6, 0XE6, 0XE6, 0XE5, 0XE5, 0XE4, 0XE2, 0XE2, 0XE3, 0XE1,
    0XE1, 0XE2, 0XE0, 0XE0, 0XE0, 0XDE, 0XDD, 0XDB, 0XD9, 0XD9, 0XDB, 0XD7, 0XD8, 0XD9, 0XD5, 0XD6,
    0XD6, 0XD1, 0XD2, 0XD2, 0XCC, 0XCD, 0XCD, 0XC7, 0XC8, 0XC7, 0XC2, 0XC2, 0XBD, 0XB8, 0XB5, 0XB9,
    0XB2, 0XB0, 0XB8, 0XB0, 0XB0, 0XB9, 0XB1, 0XB1, 0XBA, 0XB3, 0XB3, 0XBA, 0XB4, 0XB5, 0XBA, 0XB4,
    0XB5, 0XBA, 0XB4, 0XB2, 0XAB, 0XAC, 0XB2, 0X90, 0XA0, 0XB7, 0X8C, 0XA8, 0XCB, 0X7D, 0XA0, 0XC5,
    0X7A, 0XA0, 0XC5, 0X85, 0XAC, 0XD4, 0X71, 0X9B, 0XC7, 0X7A, 0XA0, 0XC9, 0X7C, 0XA2, 0XCE, 0X6A,
    0X9A, 0XCA, 0X96, 0XB8, 0XDF, 0X95, 0XB4, 0XDC, 0X9B, 0XBA, 0XE0, 0XA5, 0XC3, 0XEE, 0X8C, 0XB0,
    0XDC, 0XB2, 0XCD, 0XED, 0XC7, 0XE0, 0XFA, 0X72, 0XA2, 0XDA, 0X86, 0XAD, 0XDC, 0X96, 0XBC, 0XEA,
    0X85, 0XB1, 0XE2, 0X9C, 0XC1, 0XEB, 0XAA, 0XCB, 0XEE, 0XB6, 0XD2, 0XF3, 0XAC, 0XCB, 0XF5, 0X97,
    0XBD, 0XEB, 0XA6, 0XC3, 0XF2, 0X9B, 0XBE, 0XEE, 0XB1, 0XCE, 0XF4, 0X88, 0XB4, 0XE6, 0X9C, 0XC8,
    0XF2, 0XB4, 0XD2, 0XF4, 0XC3, 0XDC, 0XFC, 0X76, 0X9B, 0XCD, 0X85, 0XA5, 0XD2, 0XCA, 0XDD, 0XF9,
    0XEC, 0XEF, 0XF6, 0XED, 0XF0, 0XF4, 0XEF, 0XF0, 0XF3, 0XF1, 0XEF, 0XF3, 0XF2, 0XEF, 0XF3, 0XF2,
    0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XEF, 0XEF, 0XF3, 0XEF, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF1, 0XF0,
    0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF1,
    0XEF, 0XEE, 0XF2, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XF0, 0XEB, 0XEA, 0XED, 0XEB, 0XEA, 0XEC, 0XEA,
    0XE9, 0XEB, 0XE9, 0XE8, 0XEA, 0XE8, 0XE7, 0XE9, 0XE7, 0XE6, 0XE8, 0XE6, 0XE5, 0XE7, 0XE4, 0XE3,
    0XE5, 0XE2, 0XE1, 0XE3, 0XDF, 0XDE, 0XE0, 0XDF, 0XDE, 0XE0, 0XDB, 0XDA, 0XDC, 0XD7, 0XD6, 0XD8,
    0XD4, 0XD3, 0XD6, 0XCF, 0XCD, 0XD1, 0XC7, 0XC4, 0XCD, 0XC1, 0XBC, 0XC8, 0XBC, 0XB7, 0XC7, 0XB4,
    0XAE, 0XC1, 0XAD, 0XA9, 0XB9, 0XA8, 0XA4, 0XBA, 0XA6, 0X9F, 0XBA, 0XA2, 0X9C, 0XBC, 0X9B, 0XA4,
    0XD5, 0X77, 0X90, 0XD5, 0X77, 0X90, 0XD7, 0X8A, 0X9C, 0XDC, 0X84, 0X92, 0XDC, 0X77, 0X7A, 0XDF,
    0X73, 0X80, 0XDC, 0X7D, 0X98, 0XDC, 0X88, 0XA4, 0XD9, 0X9E, 0XBB, 0XE5, 0X72, 0X92, 0XD9, 0X65,
    0X88, 0XCB, 0X98, 0XA9, 0XEC, 0X75, 0X72, 0XF1, 0X77, 0X70, 0XFB, 0X79, 0X66, 0XF8, 0X7C, 0X61,
    0XF9, 0X7A, 0X63, 0XFA, 0X73, 0X5D, 0XFB, 0X78, 0X5E, 0XF9, 0X72, 0X5A, 0XF6, 0X70, 0X56, 0XFB,
    0X73, 0X5B, 0XFB, 0X75, 0X5D, 0XFA, 0X79, 0X5E, 0XFB, 0X7E, 0X65, 0XF7, 0X7E, 0X66, 0XF8, 0X7C,
    0X62, 0XF3, 0X90, 0X78, 0XF0, 0XBF, 0XB5, 0XFD, 0XB1, 0XA5, 0XFB, 0X7E, 0X66, 0XF2, 0X79, 0X5C,
    0XF7, 0X76, 0X54, 0XFA, 0X79, 0X56, 0XFB, 0X7A, 0X5A, 0XF6, 0X79, 0X56, 0XF8, 0X77, 0X51, 0XFD,
    0X77, 0X52, 0XFB, 0X76, 0X53, 0XFA, 0X77, 0X54, 0XFC, 0X74, 0X56, 0XFA, 0X74, 0X52, 0XFA, 0X7B,
    0X58, 0XF4, 0XA9, 0X94, 0XF2, 0XEF, 0XEB, 0XFE, 0XF2, 0XF2, 0XF7, 0XF5, 0XF1, 0XFB, 0XF4, 0XF0,
    0XFA, 0XF1, 0XF0, 0XFA, 0XF2, 0XF0, 0XFA, 0XF1, 0XF0, 0XFA, 0XF1, 0XF0, 0XFA, 0XF0, 0XEF, 0XF8,
    0XEF, 0XEE, 0XF7, 0XEF, 0XEE, 0XF7, 0XEF, 0XEE, 0XF5, 0XEE, 0XEE, 0XF4, 0XEE, 0XEE, 0XF4, 0XF1,
    0XF0, 0XF6, 0XF2, 0XF1, 0XF5, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF,
    0XF3, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF1, 0XEF, 0XEE, 0XEF, 0XEE, 0XED, 0XEF,
    0XED, 0XEC, 0XEE, 0XEE, 0XEC, 0XEE, 0XEE, 0XEB, 0XED, 0XEF, 0XEC, 0XEE, 0XEF, 0XEC, 0XEE, 0XEC,
    0XE9, 0XEB, 0XED, 0XEA, 0XEC, 0XEC, 0XE9, 0XEB, 0XEA, 0XE8, 0XEA, 0XE7, 0XE6, 0XE8, 0XE7, 0XE5,
    0XE7, 0XE7, 0XE4, 0XE6, 0XE6, 0XE3, 0XE5, 0XE5, 0XE1, 0XE3, 0XE4, 0XDF, 0XE1, 0XE3, 0XDE, 0XE0,
    0XE0, 0XDD, 0XDD, 0XE0, 0XDA, 0XDB, 0XE0, 0XD6, 0XD9, 0XDC, 0XD3, 0XD6, 0XD3, 0XCF, 0XD1, 0XCF,
    0XCC, 0XCD, 0XCF, 0XC8, 0XC9, 0XCD, 0XC3, 0XC5, 0XCB, 0XBE, 0XC3, 0XCD, 0XB9, 0XBC, 0XBC, 0X9A,
    0X9C, 0XAA, 0X70, 0X72, 0XA6, 0X5B, 0X5F, 0XA9, 0X56, 0X5D, 0XA8, 0X55, 0X5D, 0XA7, 0X54, 0X5D,
    0XF5, 0XF3, 0XF3, 0XF4, 0XF2, 0XF2, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF4, 0XF2, 0XF2, 0XF3,
    0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF,
    0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC,
    0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XE9,
    0XE7, 0XE7, 0XE6, 0XE4, 0XE4, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE5, 0XE3, 0XE3, 0XE3, 0XE1,
    0XE0, 0XE1, 0XE0, 0XDD, 0XE0, 0XDF, 0XDB, 0XDF, 0XDE, 0XD9, 0XDE, 0XDB, 0XD6, 0XDC, 0XD9, 0XD4,
    0XDB, 0XD5, 0XD1, 0XD7, 0XD2, 0XCC, 0XD5, 0XD2, 0XC9, 0XD1, 0XCF, 0XC5, 0XCE, 0XCC, 0XC2, 0XCA,
    0XC8, 0XBE, 0XC7, 0XC4, 0XB9, 0XC4, 0XC0, 0XB5, 0XBF, 0XBA, 0XAE, 0XB9, 0XB4, 0XA5, 0XB1, 0XAC,
    0X9A, 0XA9, 0XA6, 0X92, 0XA4, 0XA1, 0X89, 0X9F, 0X9C, 0X80, 0X96, 0X94, 0X74, 0X93, 0X91, 0X6C,
    0X8F, 0X8D, 0X67, 0X8A, 0X88, 0X5E, 0X8A, 0X89, 0X55, 0X7D, 0X7F, 0X38, 0X68, 0X70, 0X0C, 0X68,
    0X72, 0X00, 0X6C, 0X74, 0X01, 0X6C, 0X72, 0X02, 0X6B, 0X71, 0X03, 0X6B, 0X72, 0X03, 0X68, 0X73,
    0X00, 0X64, 0X6F, 0X00, 0X5F, 0X67, 0X05, 0X4B, 0X52, 0X01, 0X50, 0X5C, 0X02, 0X5F, 0X74, 0X04,
    0X59, 0X73, 0X00, 0X57, 0X71, 0X00, 0X5F, 0X7B, 0X04, 0X64, 0X81, 0X04, 0X66, 0X87, 0X00, 0X67,
    0X87, 0X00, 0X6B, 0X88, 0X01, 0X6C, 0X89, 0X01, 0X70, 0X8E, 0X03, 0X70, 0X8E, 0X03, 0X69, 0X89,
    0X00, 0X6A, 0X88, 0X00, 0X6C, 0X8B, 0X01, 0X6C, 0X8C, 0X01, 0X70, 0X90, 0X04, 0X6F, 0X90, 0X02,
    0X6F, 0X90, 0X01, 0X6F, 0X90, 0X02, 0X6F, 0X90, 0X01, 0X70, 0X91, 0X01, 0X70, 0X91, 0X01, 0X71,
    0X92, 0X02, 0X72, 0X93, 0X01, 0X75, 0X95, 0X00, 0X77, 0X99, 0X01, 0X78, 0X9B, 0X00, 0X7B, 0X9E,
    0X00, 0X7C, 0X9F, 0X02, 0X7C, 0XA0, 0X02, 0X7A, 0X9C, 0X00, 0X79, 0X9D, 0X00, 0X7D, 0XA2, 0X00,
    0X81, 0XA3, 0X00, 0X84, 0XA3, 0X00, 0X88, 0XA5, 0X00, 0X8D, 0XAE, 0X00, 0X8A, 0XA9, 0X04, 0XA2,
    0XB4, 0X41, 0XEF, 0XF2, 0XC7, 0XF6, 0XF6, 0XF1, 0XEF, 0XEF, 0XEE, 0XF5, 0XF1, 0XEF, 0XF3, 0XF1,
    0XE9, 0XF0, 0XF1, 0XE8, 0XF0, 0XEF, 0XEA, 0XEE, 0XEE, 0XE9, 0XEF, 0XED, 0XEB, 0XEE, 0XEC, 0XEC,
    0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA,
    0XE8, 0XE8, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2,
    0XE2, 0XE3, 0XE1, 0XE1, 0XE0, 0XDE, 0XDE, 0XDD, 0XDB, 0XDB, 0XDC, 0XD9, 0XD9, 0XDA, 0XD5, 0XD6,
    0XD7, 0XD2, 0XD3, 0XD3, 0XCD, 0XCE, 0XCF, 0XC9, 0XCA, 0XC9, 0XC3, 0XC4, 0XC1, 0XBC, 0XBA, 0XBA,
    0XB4, 0XB3, 0XB9, 0XB1, 0XB1, 0XB8, 0XB1, 0XB1, 0XB8, 0XB1, 0XB2, 0XB9, 0XB3, 0XB4, 0XB9, 0XB5,
    0XB5, 0XBD, 0XB7, 0XB5, 0XB6, 0XB5, 0XBA, 0X98, 0XA5, 0XB8, 0X83, 0X9C, 0XBD, 0X7B, 0X9E, 0XC1,
    0X7A, 0XA0, 0XC6, 0X7D, 0XA3, 0XCC, 0X67, 0X91, 0XBC, 0X78, 0XA1, 0XCC, 0X74, 0X9C, 0XCC, 0X64,
    0X96, 0XC7, 0X9B, 0XBD, 0XE7, 0X9F, 0XBF, 0XE7, 0X9F, 0XBF, 0XE5, 0X9D, 0XBC, 0XE6, 0X8A, 0XB1,
    0XDE, 0XA6, 0XC6, 0XE8, 0XBE, 0XD9, 0XF7, 0X68, 0X9A, 0XD3, 0X84, 0XAE, 0XDA, 0X9B, 0XC2, 0XEB,
    0X90, 0XBA, 0XE5, 0XA4, 0XC9, 0XF0, 0XB4, 0XD4, 0XF7, 0XAD, 0XC9, 0XEA, 0XA9, 0XC8, 0XF2, 0X9B,
    0XC1, 0XEF, 0XA1, 0XC1, 0XF1, 0X96, 0XB9, 0XEA, 0XB3, 0XD0, 0XF7, 0X9E, 0XC8, 0XF5, 0XA2, 0XCA,
    0XF2, 0XBA, 0XD6, 0XF5, 0XC2, 0XDB, 0XF9, 0XAD, 0XCF, 0XF9, 0XAE, 0XCA, 0XF0, 0XCF, 0XDD, 0XF3,
    0XEF, 0XF2, 0XF6, 0XED, 0XEF, 0XF3, 0XEF, 0XEF, 0XF4, 0XF1, 0XF0, 0XF4, 0XF2, 0XF0, 0XF4, 0XF1,
    0XEF, 0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XF0, 0XF4, 0XEF, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF,
    0XF3, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XEF, 0XEF, 0XF2,
    0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XF0, 0XEB, 0XEA, 0XED, 0XE9, 0XE8, 0XEB, 0XE9,
    0XE8, 0XEA, 0XE8, 0XE7, 0XE9, 0XE7, 0XE6, 0XE8, 0XE6, 0XE5, 0XE7, 0XE5, 0XE4, 0XE6, 0XE2, 0XE1,
    0XE3, 0XE2, 0XE1, 0XE3, 0XE1, 0XE0, 0XE2, 0XDE, 0XDD, 0XDF, 0XDA, 0XD9, 0XDB, 0XD6, 0XD5, 0XD7,
    0XD2, 0XD1, 0XD4, 0XCD, 0XCC, 0XD0, 0XC5, 0XC2, 0XCA, 0XBE, 0XB9, 0XC6, 0XB8, 0XB2, 0XC2, 0XB0,
    0XAA, 0XBC, 0XAC, 0XA5, 0XB8, 0XA9, 0XA1, 0XBA, 0XA4, 0X9F, 0XBA, 0X9E, 0X9F, 0XBF, 0X99, 0XA8,
    0XD5, 0X74, 0X91, 0XCE, 0X80, 0X9C, 0XDA, 0X88, 0XA0, 0XD6, 0X8A, 0XA1, 0XDE, 0X8A, 0X96, 0XE2,
    0X88, 0X97, 0XDA, 0X93, 0XAA, 0XDF, 0X95, 0XAE, 0XDC, 0X95, 0XB5, 0XE7, 0X5D, 0X84, 0XCD, 0X87,
    0XA7, 0XEA, 0X9A, 0XB3, 0XF7, 0X78, 0X7D, 0XEE, 0X82, 0X88, 0XF5, 0X69, 0X6A, 0XE9, 0X81, 0X6C,
    0XF9, 0X78, 0X5D, 0XF9, 0X73, 0X5C, 0XF9, 0X78, 0X5E, 0XF7, 0X79, 0X61, 0XF8, 0X77, 0X5D, 0XFB,
    0X78, 0X5E, 0XFA, 0X77, 0X5D, 0XF8, 0X79, 0X5B, 0XFA, 0X82, 0X67, 0XFB, 0X83, 0X68, 0XFA, 0X7E,
    0X64, 0XF0, 0XB1, 0XA4, 0XFA, 0XBD, 0XB6, 0XFF, 0X8A, 0X74, 0XF5, 0X78, 0X5B, 0XF6, 0X7D, 0X5F,
    0XFA, 0X78, 0X54, 0XFB, 0X7A, 0X56, 0XFD, 0X7A, 0X57, 0XF8, 0X79, 0X56, 0XFA, 0X79, 0X54, 0XFD,
    0X77, 0X55, 0XF9, 0X76, 0X56, 0XF8, 0X73, 0X52, 0XF9, 0X71, 0X50, 0XFB, 0X78, 0X57, 0XFA, 0X8E,
    0X73, 0XEF, 0XDA, 0XD2, 0XFC, 0XF3, 0XF2, 0XFC, 0XF2, 0XF1, 0XF7, 0XF2, 0XEF, 0XFA, 0XF2, 0XF0,
    0XFB, 0XF0, 0XEF, 0XF9, 0XF1, 0XF0, 0XFA, 0XF2, 0XF1, 0XFA, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF8,
    0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF7, 0XEE, 0XEE, 0XF4, 0XEF, 0XEF, 0XF5, 0XEF, 0XEF, 0XF5, 0XF0,
    0XEF, 0XF5, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF,
    0XF3, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF0, 0XEF, 0XEE, 0XF0, 0XEE, 0XED, 0XEF,
    0XEC, 0XEB, 0XED, 0XED, 0XEB, 0XED, 0XEF, 0XEC, 0XEE, 0XEE, 0XEB, 0XED, 0XED, 0XEA, 0XEC, 0XED,
    0XEA, 0XEC, 0XEC, 0XE9, 0XEB, 0XEB, 0XE8, 0XEA, 0XE8, 0XE6, 0XE8, 0XE6, 0XE4, 0XE6, 0XE5, 0XE2,
    0XE4, 0XE5, 0XE2, 0XE4, 0XE4, 0XE0, 0XE2, 0XE3, 0XDE, 0XE0, 0XE1, 0XDB, 0XDE, 0XE0, 0XDA, 0XDD,
    0XDF, 0XD9, 0XDA, 0XDB, 0XD5, 0XD6, 0XD5, 0XD1, 0XD2, 0XD4, 0XD0, 0XD1, 0XD2, 0XC9, 0XCC, 0XCF,
    0XC5, 0XC7, 0XC8, 0XC1, 0XC2, 0XCA, 0XBF, 0XBF, 0XCE, 0XAF, 0XB2, 0XB1, 0X86, 0X89, 0X9E, 0X63,
    0X66, 0XA1, 0X58, 0X5D, 0XA8, 0X56, 0X5B, 0XA6, 0X53, 0X5B, 0XA2, 0X52, 0X5B, 0XAB, 0X53, 0X5C,
    0XF6, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF3,
    0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF2, 0XF0,
    0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XF0, 0XEE, 0XEE,
    0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XEB,
    0XE9, 0XE9, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE5, 0XE3, 0XE3, 0XE4, 0XE1,
    0XE1, 0XE2, 0XE1, 0XDD, 0XE0, 0XDF, 0XDB, 0XE0, 0XDF, 0XDB, 0XDF, 0XDC, 0XD8, 0XDD, 0XDA, 0XD5,
    0XDD, 0XD9, 0XD4, 0XD9, 0XD5, 0XD0, 0XD6, 0XD3, 0XCB, 0XD4, 0XD1, 0XC8, 0XD0, 0XCE, 0XC4, 0XCE,
    0XCC, 0XC2, 0XCB, 0XC8, 0XBD, 0XC8, 0XC4, 0XB9, 0XC3, 0XBF, 0XB4, 0XBC, 0XB9, 0XAC, 0XB6, 0XB1,
    0XA3, 0XAF, 0XAC, 0X9A, 0XAA, 0XA6, 0X91, 0XA3, 0X9F, 0X87, 0X9E, 0X9B, 0X7E, 0X95, 0X92, 0X73,
    0X8D, 0X8A, 0X69, 0X8D, 0X8B, 0X64, 0X8A, 0X86, 0X61, 0X8C, 0X88, 0X5B, 0X7C, 0X7F, 0X34, 0X6A,
    0X72, 0X0C, 0X67, 0X70, 0X01, 0X6A, 0X72, 0X02, 0X6A, 0X71, 0X01, 0X6A, 0X71, 0X03, 0X69, 0X72,
    0X00, 0X6B, 0X75, 0X05, 0X62, 0X6A, 0X03, 0X5B, 0X64, 0X05, 0X4D, 0X58, 0X00, 0X54, 0X62, 0X00,
    0X5F, 0X75, 0X05, 0X59, 0X71, 0X01, 0X59, 0X73, 0X02, 0X5F, 0X7B, 0X02, 0X63, 0X83, 0X00, 0X67,
    0X88, 0X00, 0X69, 0X88, 0X02, 0X67, 0X86, 0X01, 0X6C, 0X8B, 0X01, 0X6C, 0X8B, 0X01, 0X69, 0X87,
    0X00, 0X6C, 0X8A, 0X00, 0X6B, 0X8A, 0X00, 0X6A, 0X8A, 0X00, 0X6D, 0X8F, 0X03, 0X70, 0X92, 0X04,
    0X6D, 0X8E, 0X00, 0X70, 0X91, 0X02, 0X6F, 0X90, 0X01, 0X6E, 0X8F, 0X00, 0X6F, 0X90, 0X01, 0X70,
    0X91, 0X01, 0X72, 0X93, 0X02, 0X73, 0X94, 0X01, 0X73, 0X95, 0X00, 0X76, 0X98, 0X00, 0X7A, 0X9C,
    0X01, 0X7B, 0X9F, 0X01, 0X7D, 0XA1, 0X02, 0X7C, 0X9F, 0X01, 0X7A, 0X9D, 0X00, 0X7A, 0X9F, 0X00,
    0X7F, 0XA3, 0X00, 0X82, 0XA5, 0X02, 0X83, 0XA2, 0X01, 0X88, 0XA7, 0X00, 0X8E, 0XAE, 0X00, 0X8C,
    0XA6, 0X01, 0XAB, 0XB7, 0X51, 0XF3, 0XF4, 0XDA, 0XF5, 0XF3, 0XF0, 0XF3, 0XF0, 0XEC, 0XEF, 0XF2,
    0XEB, 0XEC, 0XF3, 0XE5, 0XF3, 0XF0, 0XEB, 0XF2, 0XEE, 0XED, 0XEF, 0XED, 0XEB, 0XEE, 0XEC, 0XEB,
    0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA,
    0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE6, 0XE4, 0XE4, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2,
    0XE2, 0XE2, 0XE0, 0XE0, 0XE1, 0XDF, 0XDF, 0XDE, 0XDC, 0XDC, 0XDB, 0XD9, 0XD9, 0XDA, 0XD6, 0XD7,
    0XD7, 0XD2, 0XD3, 0XD5, 0XCF, 0XD0, 0XD1, 0XCB, 0XCC, 0XCA, 0XC4, 0XC5, 0XC4, 0XBF, 0XBE, 0XBC,
    0XB7, 0XB6, 0XB8, 0XB2, 0XB1, 0XB6, 0XB0, 0XB1, 0XBA, 0XB4, 0XB5, 0XB7, 0XB2, 0XB3, 0XB8, 0XB4,
    0XB4, 0XBC, 0XB6, 0XB5, 0XB6, 0XB5, 0XB8, 0XA7, 0XAF, 0XBE, 0X91, 0XA6, 0XC1, 0X79, 0X99, 0XBC,
    0X76, 0X9C, 0XC4, 0X7E, 0XA3, 0XCE, 0X6E, 0X97, 0XC3, 0X6D, 0X98, 0XC8, 0X64, 0X8E, 0XC1, 0X66,
    0X9A, 0XCC, 0X92, 0XB6, 0XE2, 0X9A, 0XBC, 0XE4, 0X9D, 0XBF, 0XE4, 0X98, 0XB8, 0XE1, 0X85, 0XAB,
    0XD9, 0XAB, 0XCD, 0XF2, 0XB7, 0XD5, 0XF3, 0X62, 0X93, 0XCC, 0X8B, 0XB5, 0XE2, 0XA0, 0XC8, 0XEE,
    0X99, 0XC2, 0XE7, 0X99, 0XBF, 0XE3, 0XB0, 0XCF, 0XF4, 0XBD, 0XD7, 0XF8, 0XAE, 0XCD, 0XF5, 0XA3,
    0XC7, 0XF5, 0X9F, 0XC2, 0XF1, 0X90, 0XB6, 0XE7, 0XB6, 0XD3, 0XF8, 0X9D, 0XC4, 0XEF, 0X9F, 0XC5,
    0XEB, 0XBF, 0XD9, 0XF7, 0XBE, 0XD6, 0XF5, 0XB4, 0XD1, 0XF7, 0XB8, 0XD1, 0XF1, 0XD7, 0XE3, 0XF1,
    0XF4, 0XF4, 0XF6, 0XED, 0XEE, 0XF2, 0XEE, 0XEF, 0XF4, 0XF0, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XF1,
    0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF,
    0XF3, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XF1, 0XF0, 0XF4, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1,
    0XED, 0XEC, 0XF0, 0XEE, 0XED, 0XF1, 0XEC, 0XEB, 0XEF, 0XEC, 0XEB, 0XEE, 0XEA, 0XE9, 0XEB, 0XE8,
    0XE7, 0XEA, 0XE8, 0XE7, 0XE9, 0XE7, 0XE6, 0XE8, 0XE6, 0XE5, 0XE7, 0XE2, 0XE1, 0XE3, 0XE1, 0XE0,
    0XE2, 0XE1, 0XE0, 0XE2, 0XDF, 0XDE, 0XE0, 0XDC, 0XDB, 0XDD, 0XD8, 0XD7, 0XD9, 0XD4, 0XD3, 0XD5,
    0XCF, 0XCE, 0XD1, 0XCB, 0XC9, 0XCE, 0XC3, 0XC0, 0XC9, 0XBB, 0XB6, 0XC4, 0XB1, 0XAB, 0XBC, 0XAC,
    0XA5, 0XB8, 0XAF, 0XA2, 0XB9, 0XA8, 0X9D, 0XB8, 0X9F, 0X9C, 0XB9, 0X9B, 0XA2, 0XC5, 0X8D, 0XA2,
    0XD1, 0X75, 0X95, 0XCD, 0X86, 0XA3, 0XDC, 0X8D, 0XA7, 0XDD, 0X87, 0XA2, 0XDE, 0X86, 0X99, 0XD8,
    0X95, 0XA5, 0XDE, 0X92, 0XA6, 0XD8, 0X9F, 0XB7, 0XE7, 0X7E, 0X9C, 0XDC, 0X56, 0X7F, 0XC8, 0X99,
    0XB7, 0XF7, 0X7A, 0X94, 0XE8, 0X83, 0X92, 0XED, 0X80, 0X99, 0XE9, 0X6D, 0X80, 0XE3, 0X7F, 0X78,
    0XF8, 0X79, 0X62, 0XF1, 0X78, 0X5F, 0XF9, 0X77, 0X5D, 0XFA, 0X7C, 0X66, 0XF7, 0X79, 0X60, 0XF6,
    0X79, 0X5E, 0XF9, 0X78, 0X5E, 0XF6, 0X7A, 0X5E, 0XF7, 0X80, 0X62, 0XFC, 0X82, 0X65, 0XF9, 0X9F,
    0X8B, 0XFA, 0XB0, 0XA5, 0XF9, 0X97, 0X87, 0XF2, 0X7A, 0X62, 0XF1, 0X7A, 0X5B, 0XFB, 0X7A, 0X58,
    0XFB, 0X78, 0X54, 0XFB, 0X78, 0X53, 0XFA, 0X76, 0X52, 0XF9, 0X77, 0X53, 0XFB, 0X77, 0X54, 0XFB,
    0X76, 0X57, 0XF7, 0X72, 0X53, 0XF5, 0X71, 0X50, 0XF9, 0X73, 0X4F, 0XFC, 0X79, 0X5C, 0XEE, 0XB9,
    0XAC, 0XF3, 0XF2, 0XF2, 0XFB, 0XF2, 0XF1, 0XF6, 0XF4, 0XF0, 0XFA, 0XF1, 0XF1, 0XFB, 0XEF, 0XEF,
    0XFA, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF7,
    0XEE, 0XED, 0XF6, 0XEE, 0XED, 0XF7, 0XED, 0XED, 0XF4, 0XEE, 0XEE, 0XF4, 0XED, 0XEC, 0XF2, 0XEF,
    0XED, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF1, 0XEE, 0XED,
    0XF1, 0XEE, 0XED, 0XF1, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF0, 0XEE, 0XED, 0XEF, 0XED, 0XEC, 0XEE,
    0XEB, 0XEA, 0XEC, 0XED, 0XEB, 0XED, 0XEE, 0XEA, 0XEC, 0XEB, 0XE8, 0XEA, 0XEB, 0XE8, 0XEA, 0XEB,
    0XE8, 0XEA, 0XEA, 0XE7, 0XE9, 0XE8, 0XE6, 0XE7, 0XE7, 0XE3, 0XE5, 0XE8, 0XE4, 0XE6, 0XE5, 0XE2,
    0XE4, 0XE3, 0XE0, 0XE2, 0XE3, 0XDF, 0XE0, 0XE1, 0XDB, 0XDE, 0XDE, 0XD7, 0XDA, 0XDC, 0XD5, 0XD8,
    0XD8, 0XD4, 0XD5, 0XD5, 0XCF, 0XD0, 0XD1, 0XCB, 0XCC, 0XCE, 0XCA, 0XCA, 0XCA, 0XC4, 0XC5, 0XCC,
    0XC0, 0XC1, 0XCD, 0XBA, 0XBB, 0XC4, 0XA3, 0XA5, 0XAF, 0X78, 0X7A, 0XA0, 0X5B, 0X5E, 0XA5, 0X55,
    0X5A, 0XAB, 0X58, 0X5D, 0XA9, 0X55, 0X5B, 0XA5, 0X50, 0X59, 0XA8, 0X52, 0X5D, 0XAE, 0X51, 0X5B,
    0XF6, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF4, 0XF2, 0XF2, 0XF5, 0XF3, 0XF3, 0XF4, 0XF2, 0XF2, 0XF2,
    0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF,
    0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED,
    0XEE, 0XEC, 0XEC, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XED,
    0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2,
    0XE2, 0XE3, 0XE2, 0XE0, 0XE1, 0XDF, 0XDD, 0XE2, 0XE0, 0XDD, 0XE0, 0XDE, 0XDA, 0XDE, 0XDA, 0XD7,
    0XDD, 0XD9, 0XD5, 0XDB, 0XD7, 0XD3, 0XD9, 0XD5, 0XCE, 0XD7, 0XD4, 0XCC, 0XD3, 0XD1, 0XC8, 0XD0,
    0XCE, 0XC5, 0XCF, 0XCD, 0XC3, 0XC9, 0XC7, 0XBC, 0XC5, 0XC2, 0XB7, 0XC1, 0XBD, 0XB1, 0XBB, 0XB8,
    0XAA, 0XB5, 0XB2, 0XA3, 0XAF, 0XAB, 0X9A, 0XAB, 0XA7, 0X92, 0XA4, 0XA0, 0X87, 0X9B, 0X97, 0X7C,
    0X91, 0X8D, 0X71, 0X8F, 0X8C, 0X6B, 0X8B, 0X89, 0X67, 0X8B, 0X87, 0X65, 0X8B, 0X8A, 0X58, 0X76,
    0X7A, 0X31, 0X66, 0X6E, 0X0C, 0X6A, 0X73, 0X02, 0X6B, 0X75, 0X00, 0X6B, 0X74, 0X00, 0X68, 0X6F,
    0X02, 0X70, 0X76, 0X0B, 0X68, 0X70, 0X04, 0X60, 0X6B, 0X00, 0X5D, 0X68, 0X03, 0X50, 0X58, 0X01,
    0X54, 0X64, 0X01, 0X5E, 0X74, 0X06, 0X59, 0X70, 0X00, 0X5B, 0X74, 0X00, 0X62, 0X7D, 0X02, 0X65,
    0X82, 0X02, 0X64, 0X83, 0X00, 0X66, 0X85, 0X00, 0X67, 0X88, 0X01, 0X68, 0X86, 0X00, 0X6B, 0X88,
    0X01, 0X6D, 0X8B, 0X03, 0X6C, 0X8A, 0X01, 0X6A, 0X8A, 0X00, 0X6B, 0X8B, 0X01, 0X6C, 0X8E, 0X02,
    0X6B, 0X8D, 0X00, 0X6B, 0X8D, 0X00, 0X6D, 0X8E, 0X00, 0X6D, 0X8E, 0X00, 0X6E, 0X8F, 0X00, 0X70,
    0X91, 0X00, 0X70, 0X91, 0X00, 0X73, 0X95, 0X02, 0X71, 0X93, 0X00, 0X77, 0X99, 0X02, 0X80, 0XA2,
    0X07, 0X7A, 0X9E, 0X00, 0X7A, 0X9F, 0X00, 0X7C, 0XA0, 0X00, 0X7D, 0X9F, 0X01, 0X79, 0X9B, 0X00,
    0X7A, 0X9F, 0X00, 0X7D, 0XA3, 0X00, 0X80, 0XA2, 0X01, 0X85, 0XA3, 0X03, 0X8C, 0XA5, 0X03, 0X91,
    0XA9, 0X04, 0X88, 0XA1, 0X07, 0XB4, 0XC1, 0X66, 0XFB, 0XF9, 0XE5, 0XF0, 0XF1, 0XEA, 0XEE, 0XF1,
    0XED, 0XEF, 0XEF, 0XED, 0XF4, 0XF0, 0XED, 0XF0, 0XEE, 0XEA, 0XEF, 0XED, 0XEB, 0XEF, 0XED, 0XEC,
    0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XE8,
    0XE6, 0XE6, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7, 0XE7, 0XE5, 0XE3, 0XE3, 0XE5, 0XE3, 0XE3, 0XE5, 0XE3,
    0XE3, 0XE1, 0XDF, 0XDF, 0XE0, 0XDE, 0XDE, 0XDF, 0XDD, 0XDD, 0XDC, 0XDA, 0XDA, 0XDB, 0XD7, 0XD7,
    0XD9, 0XD4, 0XD5, 0XD6, 0XD1, 0XD2, 0XD2, 0XCC, 0XCD, 0XCC, 0XC6, 0XC6, 0XC7, 0XC1, 0XC1, 0XC0,
    0XBA, 0XBA, 0XB9, 0XB4, 0XB4, 0XBB, 0XB5, 0XB6, 0XBB, 0XB4, 0XB5, 0XB7, 0XB2, 0XB3, 0XB9, 0XB4,
    0XB5, 0XBA, 0XB5, 0XB4, 0XB8, 0XB6, 0XB7, 0XAE, 0XB2, 0XBB, 0X9E, 0XAF, 0XC4, 0X81, 0XA0, 0XC2,
    0X70, 0X96, 0XC0, 0X7F, 0XA3, 0XD0, 0X7B, 0XA2, 0XCE, 0X6C, 0X9A, 0XCA, 0X5E, 0X8B, 0XBF, 0X59,
    0X8D, 0XC0, 0X8B, 0XB1, 0XE0, 0X9A, 0XBC, 0XE4, 0X98, 0XBA, 0XE0, 0XA3, 0XC3, 0XEC, 0X95, 0XB6,
    0XE2, 0XA6, 0XC2, 0XE8, 0XC1, 0XDB, 0XF9, 0X66, 0X93, 0XCB, 0X8E, 0XB7, 0XE6, 0X9B, 0XC1, 0XE9,
    0XA3, 0XC8, 0XEE, 0X9A, 0XC0, 0XE7, 0X9D, 0XBE, 0XE5, 0XC0, 0XDA, 0XF9, 0XAC, 0XC9, 0XF0, 0XA4,
    0XC5, 0XF3, 0XA5, 0XCA, 0XF9, 0X91, 0XB8, 0XE9, 0XB5, 0XD2, 0XF7, 0X9E, 0XC2, 0XEB, 0XA3, 0XC7,
    0XEF, 0XBF, 0XDA, 0XF9, 0XB8, 0XD1, 0XF2, 0XB4, 0XCE, 0XF3, 0XBD, 0XD3, 0XF1, 0XDF, 0XE9, 0XF5,
    0XF3, 0XF3, 0XF6, 0XF0, 0XF1, 0XF5, 0XEF, 0XF0, 0XF4, 0XEE, 0XEF, 0XF3, 0XEE, 0XEF, 0XF3, 0XF0,
    0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XF0, 0XEF,
    0XF3, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1,
    0XEC, 0XEB, 0XEF, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XEF, 0XEC, 0XEB, 0XEE, 0XEA, 0XE9, 0XEB, 0XE9,
    0XE8, 0XEA, 0XE7, 0XE6, 0XE8, 0XE6, 0XE5, 0XE7, 0XE5, 0XE4, 0XE6, 0XE2, 0XE1, 0XE3, 0XE1, 0XE0,
    0XE2, 0XDF, 0XDE, 0XE0, 0XDC, 0XDB, 0XDD, 0XD9, 0XD8, 0XD9, 0XD7, 0XD6, 0XD9, 0XD2, 0XD2, 0XD5,
    0XCC, 0XCB, 0XCF, 0XC6, 0XC4, 0XCB, 0XBD, 0XB9, 0XC3, 0XB8, 0XB3, 0XC2, 0XB0, 0XAA, 0XBC, 0XAB,
    0XA4, 0XB9, 0XAC, 0X9F, 0XB7, 0XA9, 0X9E, 0XB8, 0X9F, 0X9D, 0XBC, 0X96, 0XA3, 0XCC, 0X88, 0XA3,
    0XD7, 0X80, 0X9F, 0XDA, 0X83, 0X9F, 0XDB, 0X77, 0X90, 0XCE, 0X7A, 0X94, 0XD7, 0X80, 0X97, 0XD7,
    0X94, 0XA8, 0XE5, 0X94, 0XA8, 0XE2, 0X9C, 0XB5, 0XEB, 0X7E, 0X99, 0XE0, 0X74, 0X96, 0XD5, 0X97,
    0XB8, 0XF0, 0X7A, 0X95, 0XE2, 0X92, 0XB4, 0XEF, 0X71, 0X97, 0XDA, 0X7E, 0X99, 0XED, 0X68, 0X71,
    0XE4, 0X80, 0X70, 0XF6, 0X74, 0X5A, 0XF5, 0X70, 0X5B, 0XF3, 0X7A, 0X67, 0XF5, 0X7B, 0X62, 0XFC,
    0X77, 0X5A, 0XFB, 0X79, 0X5E, 0XF8, 0X7B, 0X62, 0XF7, 0X84, 0X6E, 0XFA, 0X86, 0X6F, 0XF6, 0X95,
    0X81, 0XF4, 0X89, 0X76, 0XEB, 0X83, 0X6C, 0XF0, 0X77, 0X5E, 0XF4, 0X76, 0X59, 0XFA, 0X76, 0X54,
    0XF7, 0X7B, 0X53, 0XFC, 0X7A, 0X55, 0XFB, 0X76, 0X52, 0XFB, 0X76, 0X53, 0XFC, 0X74, 0X53, 0XFA,
    0X75, 0X55, 0XF9, 0X74, 0X53, 0XF9, 0X73, 0X51, 0XFC, 0X77, 0X54, 0XF8, 0X96, 0X82, 0XEE, 0XE3,
    0XE2, 0XFD, 0XF4, 0XF4, 0XF8, 0XF5, 0XF1, 0XF6, 0XF3, 0XEF, 0XFC, 0XEF, 0XF0, 0XF9, 0XEF, 0XF1,
    0XFA, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF8, 0XEF, 0XEE, 0XF8,
    0XEE, 0XED, 0XF5, 0XEC, 0XEC, 0XF3, 0XED, 0XED, 0XF3, 0XEE, 0XEE, 0XF4, 0XEC, 0XEC, 0XF2, 0XEF,
    0XEE, 0XF4, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XEF, 0XEE,
    0XF2, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF0, 0XEC, 0XEB, 0XED, 0XEC, 0XEB, 0XED,
    0XEC, 0XEB, 0XED, 0XEB, 0XE9, 0XEB, 0XEC, 0XE9, 0XEB, 0XEA, 0XE7, 0XE9, 0XE9, 0XE7, 0XE8, 0XE9,
    0XE6, 0XE8, 0XE8, 0XE5, 0XE7, 0XE6, 0XE3, 0XE5, 0XE4, 0XE1, 0XE3, 0XE4, 0XE1, 0XE3, 0XE3, 0XE0,
    0XE1, 0XE0, 0XDC, 0XDD, 0XE1, 0XDC, 0XDE, 0XDD, 0XD7, 0XD9, 0XD9, 0XD3, 0XD4, 0XD7, 0XD0, 0XD1,
    0XD0, 0XCD, 0XCD, 0XCE, 0XC9, 0XCA, 0XCE, 0XC7, 0XC8, 0XC9, 0XC3, 0XC5, 0XC6, 0XC0, 0XC0, 0XCA,
    0XB6, 0XB7, 0XBC, 0X91, 0X94, 0XA6, 0X69, 0X6D, 0XA6, 0X5B, 0X5E, 0XA6, 0X53, 0X58, 0XA9, 0X53,
    0X58, 0XA7, 0X52, 0X58, 0XA4, 0X51, 0X59, 0XAC, 0X53, 0X5E, 0XAF, 0X4D, 0X5B, 0X9A, 0X34, 0X42,
    0XF4, 0XF2, 0XF2, 0XF6, 0XF4, 0XF4, 0XF4, 0XF2, 0XF2, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF4,
    0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0,
    0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE,
    0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC,
    0XEA, 0XEA, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4,
    0XE4, 0XE4, 0XE2, 0XE2, 0XE3, 0XE1, 0XE0, 0XE2, 0XE0, 0XE0, 0XE1, 0XE0, 0XDC, 0XE1, 0XDE, 0XDA,
    0XDF, 0XDC, 0XD8, 0XDE, 0XDA, 0XD7, 0XDB, 0XD8, 0XD2, 0XD7, 0XD4, 0XCE, 0XD5, 0XD1, 0XCB, 0XD2,
    0XCF, 0XC7, 0XD3, 0XD0, 0XC7, 0XCC, 0XCA, 0XC0, 0XC8, 0XC7, 0XBC, 0XC4, 0XC1, 0XB7, 0XBF, 0XBB,
    0XB1, 0XBC, 0XB8, 0XAB, 0XB5, 0XB1, 0XA2, 0XAE, 0XAA, 0X98, 0XA8, 0XA3, 0X8F, 0XA0, 0X9C, 0X84,
    0X9B, 0X97, 0X7E, 0X93, 0X8F, 0X73, 0X8F, 0X8E, 0X6A, 0X8D, 0X8C, 0X67, 0X88, 0X85, 0X63, 0X88,
    0X86, 0X57, 0X72, 0X77, 0X27, 0X66, 0X70, 0X04, 0X69, 0X74, 0X00, 0X69, 0X72, 0X00, 0X6A, 0X71,
    0X02, 0X69, 0X70, 0X03, 0X6A, 0X72, 0X01, 0X67, 0X72, 0X00, 0X62, 0X6C, 0X02, 0X5C, 0X62, 0X05,
    0X4F, 0X5B, 0X00, 0X57, 0X69, 0X02, 0X61, 0X75, 0X04, 0X59, 0X6F, 0X00, 0X5D, 0X74, 0X01, 0X61,
    0X7B, 0X04, 0X63, 0X80, 0X01, 0X67, 0X87, 0X01, 0X63, 0X84, 0X00, 0X65, 0X86, 0X00, 0X6A, 0X89,
    0X02, 0X6D, 0X8B, 0X03, 0X6D, 0X8B, 0X01, 0X6C, 0X8C, 0X02, 0X6B, 0X8C, 0X02, 0X6B, 0X8D, 0X01,
    0X6C, 0X8D, 0X02, 0X6B, 0X8D, 0X00, 0X6C, 0X8E, 0X00, 0X6E, 0X8F, 0X00, 0X6E, 0X8F, 0X00, 0X6F,
    0X90, 0X00, 0X6D, 0X8E, 0X00, 0X71, 0X93, 0X01, 0X72, 0X95, 0X00, 0X73, 0X95, 0X00, 0X78, 0X9A,
    0X01, 0X7B, 0X9E, 0X01, 0X7E, 0XA2, 0X01, 0X7F, 0XA1, 0X01, 0X7F, 0XA1, 0X01, 0X7D, 0X9F, 0X01,
    0X79, 0X9C, 0X02, 0X77, 0X9D, 0X00, 0X7D, 0XA2, 0X00, 0X83, 0XA3, 0X01, 0X89, 0XA3, 0X03, 0X89,
    0XA5, 0X01, 0X8C, 0XAA, 0X02, 0X8A, 0XA3, 0X06, 0XC0, 0XCC, 0X77, 0XF7, 0XFA, 0XE7, 0XF2, 0XEF,
    0XF0, 0XF3, 0XEB, 0XF2, 0XF1, 0XEF, 0XED, 0XEF, 0XEF, 0XEA, 0XEF, 0XED, 0XEB, 0XEE, 0XEC, 0XEB,
    0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XE9,
    0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE9, 0XE7, 0XE7, 0XE7, 0XE5, 0XE5, 0XE7, 0XE5, 0XE5, 0XE5, 0XE4,
    0XE4, 0XE3, 0XE1, 0XE1, 0XE1, 0XE0, 0XE0, 0XDF, 0XDD, 0XDD, 0XDD, 0XDB, 0XDB, 0XD9, 0XD7, 0XD7,
    0XD9, 0XD4, 0XD5, 0XD7, 0XD2, 0XD3, 0XD4, 0XCE, 0XCF, 0XCF, 0XC9, 0XCA, 0XC7, 0XC2, 0XC2, 0XC1,
    0XBB, 0XBC, 0XBC, 0XB6, 0XB7, 0XB9, 0XB3, 0XB4, 0XBB, 0XB5, 0XB6, 0XB8, 0XB3, 0XB4, 0XBA, 0XB6,
    0XB6, 0XB9, 0XB6, 0XB6, 0XB9, 0XB5, 0XB5, 0XB5, 0XB4, 0XB8, 0XA7, 0XB3, 0XC5, 0X89, 0XA6, 0XC8,
    0X71, 0X99, 0XC4, 0X81, 0XA5, 0XD3, 0X89, 0XAF, 0XDA, 0X6F, 0X9D, 0XCC, 0X60, 0X8D, 0XC2, 0X5A,
    0X8D, 0XC0, 0X8F, 0XB6, 0XE7, 0X9B, 0XBB, 0XE2, 0X9A, 0XBB, 0XE0, 0XA5, 0XC5, 0XED, 0XA5, 0XC3,
    0XEB, 0XA7, 0XC1, 0XE7, 0XC3, 0XDA, 0XF9, 0X6F, 0X98, 0XD0, 0X81, 0XA9, 0XDD, 0XA9, 0XCD, 0XF8,
    0X9C, 0XBE, 0XE5, 0X9E, 0XC4, 0XED, 0XA6, 0XC8, 0XEF, 0XBB, 0XD4, 0XF2, 0XB0, 0XCE, 0XF2, 0XAA,
    0XCA, 0XF5, 0X9F, 0XC6, 0XF6, 0X90, 0XB7, 0XE9, 0XB6, 0XD3, 0XF7, 0XA7, 0XCB, 0XF1, 0XA3, 0XC8,
    0XF0, 0XB7, 0XD4, 0XF8, 0XAD, 0XCA, 0XEF, 0XB8, 0XD2, 0XF5, 0XBE, 0XD4, 0XF0, 0XE3, 0XEC, 0XF9,
    0XF1, 0XF3, 0XF7, 0XF0, 0XF0, 0XF4, 0XEE, 0XF0, 0XF4, 0XEE, 0XF0, 0XF4, 0XEE, 0XF0, 0XF4, 0XEF,
    0XF0, 0XF4, 0XF0, 0XF0, 0XF3, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF,
    0XF3, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1,
    0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF0, 0XEA, 0XE9, 0XED, 0XEB, 0XEA, 0XED, 0XE9, 0XE8, 0XEA, 0XE8,
    0XE7, 0XE9, 0XE6, 0XE5, 0XE7, 0XE5, 0XE4, 0XE6, 0XE3, 0XE2, 0XE4, 0XE1, 0XE0, 0XE2, 0XDF, 0XDE,
    0XE0, 0XDE, 0XDD, 0XDF, 0XDB, 0XDA, 0XDC, 0XD8, 0XD7, 0XD8, 0XD5, 0XD4, 0XD6, 0XCF, 0XCE, 0XD3,
    0XCA, 0XC8, 0XCE, 0XC2, 0XC0, 0XC8, 0XB9, 0XB5, 0XC0, 0XB4, 0XAF, 0XBE, 0XAF, 0XA9, 0XBC, 0XAA,
    0XA3, 0XB8, 0XA3, 0X9B, 0XB1, 0XA3, 0X9B, 0XB4, 0X9D, 0X9F, 0XC0, 0X8F, 0XA0, 0XCF, 0X7D, 0X9A,
    0XD3, 0X7E, 0X9B, 0XD8, 0X72, 0X8C, 0XCE, 0X7F, 0X98, 0XDA, 0X83, 0X9D, 0XDB, 0X7A, 0X96, 0XD3,
    0X85, 0XA1, 0XDC, 0X97, 0XB3, 0XEA, 0X8F, 0XAF, 0XE4, 0X7B, 0X97, 0XD8, 0X9B, 0XB8, 0XE5, 0X8A,
    0XB0, 0XE1, 0X8F, 0XAD, 0XEB, 0X79, 0XA7, 0XDB, 0X88, 0XB2, 0XE8, 0X8E, 0XAF, 0XF8, 0X6B, 0X7F,
    0XEA, 0X66, 0X61, 0XED, 0X7E, 0X71, 0XF3, 0X75, 0X6A, 0XF4, 0X70, 0X63, 0XEF, 0X7B, 0X6A, 0XFA,
    0X7F, 0X6D, 0XFA, 0X7E, 0X69, 0XFA, 0X7E, 0X69, 0XFB, 0X82, 0X77, 0XF4, 0X8F, 0X83, 0XF8, 0X7C,
    0X68, 0XF1, 0X8D, 0X77, 0XF8, 0X81, 0X69, 0XF5, 0X78, 0X5B, 0XFC, 0X77, 0X5A, 0XFB, 0X7A, 0X58,
    0XF9, 0X7B, 0X54, 0XFB, 0X7A, 0X55, 0XFA, 0X77, 0X53, 0XFC, 0X75, 0X52, 0XFD, 0X75, 0X54, 0XFC,
    0X73, 0X51, 0XFC, 0X72, 0X50, 0XFB, 0X75, 0X53, 0XF9, 0X81, 0X64, 0XEC, 0XC8, 0XBE, 0XF7, 0XF4,
    0XF5, 0XFD, 0XF1, 0XEF, 0XFB, 0XF5, 0XEF, 0XFC, 0XF4, 0XEF, 0XFB, 0XEE, 0XEE, 0XF7, 0XEE, 0XF0,
    0XF7, 0XF1, 0XF0, 0XF9, 0XF1, 0XF0, 0XF9, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF6,
    0XEE, 0XED, 0XF3, 0XEE, 0XEE, 0XF4, 0XED, 0XED, 0XF3, 0XED, 0XED, 0XF3, 0XEC, 0XEC, 0XF2, 0XEF,
    0XED, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEF, 0XEE, 0XF2, 0XEE, 0XED,
    0XF1, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF1, 0XED, 0XEC, 0XEF, 0XEB, 0XEA, 0XEB, 0XEB, 0XEA, 0XEC,
    0XEA, 0XE9, 0XEB, 0XE9, 0XE7, 0XE9, 0XEA, 0XE7, 0XE9, 0XE9, 0XE6, 0XE8, 0XE8, 0XE5, 0XE7, 0XE8,
    0XE5, 0XE7, 0XE6, 0XE3, 0XE5, 0XE4, 0XE1, 0XE3, 0XE3, 0XDF, 0XE2, 0XE2, 0XDE, 0XE1, 0XE2, 0XDD,
    0XE0, 0XDE, 0XD9, 0XDB, 0XDE, 0XD7, 0XDA, 0XDB, 0XD4, 0XD6, 0XD7, 0XD1, 0XD1, 0XD3, 0XCC, 0XCD,
    0XD1, 0XC8, 0XCA, 0XCE, 0XC4, 0XC6, 0XCA, 0XC0, 0XC2, 0XCA, 0XBD, 0XBE, 0XC4, 0XAA, 0XAC, 0XAD,
    0X7E, 0X83, 0XA4, 0X5F, 0X65, 0XA7, 0X56, 0X5D, 0XA9, 0X54, 0X59, 0XA8, 0X51, 0X58, 0XA5, 0X4F,
    0X56, 0XA6, 0X50, 0X58, 0XA5, 0X4F, 0X57, 0XA6, 0X45, 0X52, 0X9E, 0X2F, 0X40, 0X94, 0X26, 0X36,
    0XF6, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF4,
    0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0,
    0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF1, 0XEF, 0XEF,
    0XF0, 0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC,
    0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5,
    0XE4, 0XE5, 0XE3, 0XE2, 0XE4, 0XE2, 0XE1, 0XE3, 0XE1, 0XE1, 0XE3, 0XE1, 0XDF, 0XE2, 0XDE, 0XDC,
    0XE1, 0XDD, 0XDA, 0XDF, 0XDC, 0XD8, 0XDE, 0XD9, 0XD6, 0XDB, 0XD6, 0XD3, 0XD9, 0XD4, 0XD1, 0XD5,
    0XD1, 0XCC, 0XD2, 0XCE, 0XC8, 0XD1, 0XCE, 0XC6, 0XCB, 0XC9, 0XC0, 0XC8, 0XC7, 0XBD, 0XC4, 0XC2,
    0XB8, 0XC1, 0XBD, 0XB2, 0XBB, 0XB7, 0XAA, 0XB3, 0XAF, 0X9F, 0XAF, 0XAA, 0X97, 0XA7, 0XA2, 0X8E,
    0XA1, 0X9C, 0X87, 0X9C, 0X95, 0X7D, 0X94, 0X90, 0X6F, 0X92, 0X90, 0X6D, 0X8A, 0X86, 0X68, 0X8A,
    0X88, 0X64, 0X83, 0X84, 0X46, 0X70, 0X75, 0X1C, 0X68, 0X6F, 0X06, 0X6A, 0X71, 0X01, 0X6B, 0X73,
    0X01, 0X6A, 0X73, 0X00, 0X6B, 0X74, 0X00, 0X69, 0X72, 0X01, 0X64, 0X6E, 0X02, 0X62, 0X6B, 0X04,
    0X58, 0X62, 0X03, 0X4A, 0X58, 0X00, 0X5B, 0X6B, 0X04, 0X64, 0X76, 0X08, 0X57, 0X6C, 0X00, 0X5C,
    0X76, 0X01, 0X5E, 0X7C, 0X00, 0X61, 0X83, 0X01, 0X63, 0X85, 0X01, 0X67, 0X87, 0X02, 0X6A, 0X88,
    0X01, 0X6C, 0X8A, 0X00, 0X6B, 0X8B, 0X00, 0X69, 0X8A, 0X00, 0X69, 0X8B, 0X01, 0X68, 0X8B, 0X00,
    0X68, 0X8B, 0X00, 0X6B, 0X8D, 0X01, 0X6E, 0X90, 0X02, 0X70, 0X91, 0X01, 0X6E, 0X8F, 0X00, 0X6F,
    0X90, 0X00, 0X6F, 0X90, 0X01, 0X6D, 0X8E, 0X00, 0X70, 0X92, 0X00, 0X73, 0X93, 0X00, 0X74, 0X95,
    0X00, 0X7B, 0X9D, 0X03, 0X7E, 0X9F, 0X02, 0X7E, 0X9F, 0X01, 0X7E, 0X9F, 0X01, 0X7D, 0XA1, 0X00,
    0X7C, 0X9D, 0X01, 0X7A, 0X9C, 0X03, 0X7A, 0XA0, 0X00, 0X81, 0XA4, 0X00, 0X84, 0XA4, 0X00, 0X81,
    0XA4, 0X00, 0X84, 0XA5, 0X01, 0X8C, 0XAA, 0X00, 0X88, 0XA4, 0X0D, 0XC7, 0XD2, 0X8B, 0XFA, 0XF9,
    0XEB, 0XF3, 0XEF, 0XEB, 0XF2, 0XF1, 0XEC, 0XF0, 0XF0, 0XEB, 0XEF, 0XED, 0XEC, 0XF0, 0XED, 0XED,
    0XEE, 0XEC, 0XEC, 0XEF, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEB,
    0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE5, 0XE3,
    0XE3, 0XE4, 0XE2, 0XE2, 0XE2, 0XE1, 0XE1, 0XDF, 0XDF, 0XDF, 0XDF, 0XDD, 0XDD, 0XDA, 0XD8, 0XD8,
    0XDA, 0XD4, 0XD6, 0XD8, 0XD3, 0XD4, 0XD3, 0XCE, 0XCF, 0XCD, 0XC8, 0XC9, 0XC8, 0XC3, 0XC4, 0XC1,
    0XBB, 0XBC, 0XBD, 0XB7, 0XB8, 0XB9, 0XB3, 0XB4, 0XB9, 0XB4, 0XB5, 0XBA, 0XB5, 0XB6, 0XBA, 0XB7,
    0XB7, 0XB4, 0XB3, 0XB5, 0XB8, 0XB2, 0XB2, 0XB9, 0XB4, 0XB5, 0XA9, 0XB1, 0XBF, 0X88, 0XA4, 0XC4,
    0X6F, 0X98, 0XC2, 0X80, 0XA4, 0XD0, 0X88, 0XAE, 0XD6, 0X6F, 0X9A, 0XCA, 0X6D, 0X97, 0XCD, 0X66,
    0X96, 0XC9, 0X7E, 0XA4, 0XD6, 0X9D, 0XBC, 0XE2, 0X9A, 0XBC, 0XE1, 0X9F, 0XC1, 0XE8, 0X9D, 0XBD,
    0XE6, 0X9B, 0XBB, 0XE4, 0XC2, 0XDC, 0XFC, 0X75, 0XA1, 0XD8, 0X84, 0XAD, 0XE2, 0XA2, 0XC5, 0XEF,
    0XA5, 0XC5, 0XE9, 0XA2, 0XC7, 0XF0, 0XA8, 0XC9, 0XF0, 0XC6, 0XDE, 0XFA, 0XB2, 0XD2, 0XF2, 0XAE,
    0XCE, 0XF8, 0X99, 0XC3, 0XF1, 0X8E, 0XB6, 0XE6, 0XB8, 0XD6, 0XF9, 0XAB, 0XCE, 0XEF, 0XA3, 0XC8,
    0XEE, 0XBC, 0XDB, 0XFD, 0XB2, 0XD1, 0XF8, 0XBA, 0XD2, 0XF4, 0XC1, 0XD3, 0XEF, 0XE7, 0XEE, 0XFA,
    0XEE, 0XF0, 0XF5, 0XEF, 0XF0, 0XF4, 0XEE, 0XF0, 0XF4, 0XED, 0XF0, 0XF4, 0XEE, 0XF1, 0XF5, 0XEE,
    0XF0, 0XF4, 0XF0, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF1, 0XF0, 0XF4, 0XF0, 0XEF,
    0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF0,
    0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XEF, 0XEB, 0XEA, 0XEE, 0XEA, 0XE9, 0XEC, 0XE8, 0XE7, 0XE9, 0XE7,
    0XE6, 0XE8, 0XE6, 0XE5, 0XE7, 0XE4, 0XE3, 0XE5, 0XE3, 0XE2, 0XE4, 0XE2, 0XE1, 0XE3, 0XDF, 0XDE,
    0XE0, 0XDD, 0XDC, 0XDE, 0XD9, 0XD8, 0XDA, 0XD6, 0XD5, 0XD7, 0XD2, 0XD1, 0XD3, 0XCD, 0XCC, 0XD0,
    0XC8, 0XC6, 0XCC, 0XC0, 0XBC, 0XC6, 0XB7, 0XB3, 0XBE, 0XB3, 0XAD, 0XBC, 0XAB, 0XA4, 0XB8, 0XA8,
    0XA1, 0XB7, 0XA3, 0X9E, 0XB6, 0XA0, 0X9B, 0XB5, 0X9A, 0X9D, 0XC0, 0X90, 0XA3, 0XD7, 0X7B, 0X98,
    0XD3, 0X85, 0XA2, 0XDD, 0X6F, 0X8B, 0XCB, 0X7B, 0X96, 0XD7, 0X84, 0XA0, 0XD5, 0X84, 0XA2, 0XDA,
    0X89, 0XA7, 0XDB, 0X8C, 0XAE, 0XD8, 0X88, 0XAD, 0XE0, 0X70, 0X91, 0XCD, 0XA6, 0XC3, 0XEC, 0X89,
    0XB0, 0XE4, 0X7F, 0XA3, 0XEA, 0X6C, 0X95, 0XDB, 0X99, 0XC0, 0XF1, 0X88, 0XAF, 0XEF, 0X58, 0X72,
    0XDD, 0X66, 0X73, 0XEA, 0X9D, 0XA7, 0XF9, 0X8A, 0X94, 0XF6, 0X83, 0X84, 0XF6, 0X79, 0X71, 0XF2,
    0X7B, 0X6F, 0XF5, 0X7E, 0X70, 0XF9, 0X72, 0X67, 0XED, 0X8C, 0X8F, 0XF2, 0X90, 0X8D, 0XF9, 0X74,
    0X61, 0XF5, 0X83, 0X6F, 0XF9, 0X7C, 0X62, 0XF8, 0X75, 0X56, 0XFB, 0X77, 0X59, 0XF9, 0X78, 0X56,
    0XFC, 0X75, 0X51, 0XF7, 0X78, 0X53, 0XFA, 0X77, 0X52, 0XFB, 0X76, 0X53, 0XFA, 0X75, 0X55, 0XFC,
    0X73, 0X4F, 0XFC, 0X76, 0X53, 0XFA, 0X77, 0X57, 0XEC, 0XA6, 0X95, 0XEA, 0XF0, 0XEC, 0XFD, 0XEF,
    0XF0, 0XF9, 0XEE, 0XF0, 0XF8, 0XF1, 0XED, 0XFC, 0XF0, 0XEE, 0XFA, 0XF1, 0XEE, 0XF9, 0XF1, 0XF0,
    0XF7, 0XF1, 0XF0, 0XF9, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF7, 0XEF, 0XEE, 0XF6, 0XEC, 0XED, 0XF3,
    0XEC, 0XEC, 0XF2, 0XEE, 0XEE, 0XF4, 0XED, 0XED, 0XF3, 0XEC, 0XEC, 0XF2, 0XED, 0XED, 0XF3, 0XEF,
    0XED, 0XF3, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XEC, 0XEB,
    0XEF, 0XEC, 0XEB, 0XEF, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XEE, 0XEA, 0XE9, 0XEB, 0XEB, 0XEA, 0XEC,
    0XE9, 0XE7, 0XE9, 0XE8, 0XE6, 0XE8, 0XE8, 0XE5, 0XE7, 0XE7, 0XE4, 0XE6, 0XE6, 0XE3, 0XE5, 0XE6,
    0XE3, 0XE5, 0XE4, 0XE1, 0XE3, 0XE2, 0XDF, 0XE1, 0XE1, 0XDD, 0XE0, 0XE0, 0XD9, 0XDF, 0XDE, 0XD8,
    0XDC, 0XDC, 0XD6, 0XD8, 0XDA, 0XD2, 0XD6, 0XD7, 0XCF, 0XD1, 0XD2, 0XCA, 0XCB, 0XCD, 0XC5, 0XC6,
    0XCE, 0XC3, 0XC5, 0XCD, 0XBD, 0XBF, 0XCD, 0XB7, 0XBB, 0XBC, 0X97, 0X9C, 0XA2, 0X6A, 0X71, 0XA3,
    0X5A, 0X61, 0XA6, 0X54, 0X5B, 0XA8, 0X51, 0X59, 0XAA, 0X51, 0X5B, 0XA8, 0X51, 0X5C, 0XAC, 0X54,
    0X5F, 0XAC, 0X4F, 0X5B, 0XA0, 0X3C, 0X4A, 0X92, 0X29, 0X37, 0X98, 0X2B, 0X39, 0XB9, 0X4D, 0X57,
    0XF6, 0XF4, 0XF4, 0XF5, 0XF3, 0XF3, 0XF6, 0XF4, 0XF4, 0XF5, 0XF3, 0XF3, 0XF6, 0XF4, 0XF4, 0XF5,
    0XF3, 0XF3, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0,
    0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF,
    0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XED, 0XEB, 0XEB, 0XEE, 0XEC, 0XEC, 0XED,
    0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE8, 0XE6,
    0XE6, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE3, 0XE4, 0XE2, 0XE1, 0XE4, 0XE2, 0XE1, 0XE2, 0XDF, 0XDF,
    0XE0, 0XDE, 0XDC, 0XE0, 0XDD, 0XDB, 0XDF, 0XDB, 0XDA, 0XDD, 0XD8, 0XD5, 0XDC, 0XD7, 0XD4, 0XD8,
    0XD3, 0XD0, 0XD4, 0XD0, 0XCB, 0XD3, 0XD0, 0XCA, 0XCF, 0XCC, 0XC6, 0XCC, 0XC9, 0XC1, 0XC6, 0XC5,
    0XBB, 0XC3, 0XC0, 0XB6, 0XBF, 0XBB, 0XAF, 0XBA, 0XB6, 0XA7, 0XB2, 0XAE, 0X9D, 0XAF, 0XAA, 0X97,
    0XA7, 0XA1, 0X8E, 0XA3, 0X9A, 0X84, 0X9F, 0X95, 0X7D, 0X94, 0X90, 0X74, 0X8C, 0X8B, 0X68, 0X8A,
    0X8A, 0X61, 0X89, 0X88, 0X56, 0X85, 0X84, 0X42, 0X6D, 0X71, 0X18, 0X66, 0X6F, 0X00, 0X6A, 0X70,
    0X02, 0X69, 0X71, 0X00, 0X6B, 0X73, 0X00, 0X6A, 0X74, 0X00, 0X66, 0X6F, 0X00, 0X61, 0X6C, 0X01,
    0X5D, 0X68, 0X05, 0X4F, 0X5B, 0X01, 0X4A, 0X55, 0X00, 0X5F, 0X6E, 0X07, 0X5D, 0X72, 0X04, 0X58,
    0X72, 0X00, 0X5B, 0X78, 0X00, 0X5D, 0X7D, 0X02, 0X61, 0X83, 0X00, 0X65, 0X86, 0X01, 0X69, 0X88,
    0X02, 0X6C, 0X8A, 0X00, 0X6C, 0X8A, 0X00, 0X6B, 0X8C, 0X00, 0X6C, 0X8F, 0X03, 0X6C, 0X8F, 0X02,
    0X6C, 0X8E, 0X03, 0X6E, 0X8F, 0X04, 0X6C, 0X8E, 0X02, 0X6C, 0X8E, 0X00, 0X6E, 0X8F, 0X00, 0X6F,
    0X8F, 0X00, 0X70, 0X91, 0X03, 0X6C, 0X8D, 0X01, 0X6E, 0X8E, 0X00, 0X70, 0X91, 0X01, 0X73, 0X93,
    0X01, 0X74, 0X94, 0X00, 0X76, 0X96, 0X00, 0X7B, 0X9A, 0X02, 0X80, 0X9E, 0X06, 0X80, 0XA2, 0X01,
    0X7D, 0XA0, 0X00, 0X7E, 0X9F, 0X02, 0X7C, 0X9F, 0X00, 0X7A, 0X9D, 0X00, 0X7E, 0XA0, 0X04, 0X80,
    0XA4, 0X01, 0X80, 0XA3, 0X00, 0X84, 0XA2, 0X04, 0X8A, 0XA6, 0X00, 0X8E, 0XA4, 0X17, 0XD3, 0XDC,
    0X9F, 0XF7, 0XF7, 0XF2, 0XEF, 0XEF, 0XE9, 0XF1, 0XF2, 0XE9, 0XF0, 0XEE, 0XED, 0XF0, 0XEE, 0XED,
    0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XED, 0XEC, 0XEC, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA,
    0XE8, 0XE8, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE8, 0XE6, 0XE6, 0XE6, 0XE4, 0XE4, 0XE6, 0XE4,
    0XE4, 0XE4, 0XE2, 0XE2, 0XE1, 0XE0, 0XE0, 0XE0, 0XE0, 0XE0, 0XDE, 0XDD, 0XDD, 0XDD, 0XDB, 0XDB,
    0XD9, 0XD6, 0XD6, 0XD5, 0XD0, 0XD1, 0XD4, 0XCF, 0XD0, 0XCF, 0XCA, 0XCB, 0XCA, 0XC5, 0XC6, 0XC3,
    0XBE, 0XBF, 0XBD, 0XB7, 0XB8, 0XBC, 0XB6, 0XB7, 0XBA, 0XB4, 0XB5, 0XBA, 0XB5, 0XB6, 0XBB, 0XB8,
    0XB8, 0XB4, 0XB2, 0XB6, 0XBA, 0XB4, 0XB5, 0XBB, 0XB4, 0XB3, 0XAD, 0XB3, 0XBE, 0X96, 0XB0, 0XCF,
    0X71, 0X98, 0XC3, 0X79, 0X9F, 0XC9, 0X7F, 0XA4, 0XCA, 0X6C, 0X95, 0XC3, 0X5F, 0X89, 0XBD, 0X66,
    0X95, 0XC6, 0X84, 0XA9, 0XDB, 0XA6, 0XC3, 0XE9, 0X94, 0XB5, 0XDB, 0X9F, 0XC1, 0XE8, 0X93, 0XB8,
    0XE3, 0X87, 0XAE, 0XDC, 0XB5, 0XD5, 0XF7, 0X75, 0XA5, 0XDD, 0X7D, 0XA9, 0XDE, 0X9D, 0XC1, 0XE8,
    0XA8, 0XC5, 0XE4, 0XAB, 0XCF, 0XF3, 0XA3, 0XC5, 0XEA, 0XC5, 0XDC, 0XF7, 0XB7, 0XD5, 0XF3, 0XAB,
    0XCA, 0XF1, 0X95, 0XC0, 0XEC, 0X8F, 0XB9, 0XE9, 0XB6, 0XD4, 0XF5, 0XB1, 0XD3, 0XF1, 0XA8, 0XCD,
    0XF0, 0XB8, 0XD7, 0XF9, 0XAE, 0XCB, 0XF1, 0XC1, 0XD5, 0XF4, 0XCA, 0XDA, 0XF2, 0XEA, 0XEF, 0XF9,
    0XEF, 0XF1, 0XF6, 0XEF, 0XF0, 0XF4, 0XEE, 0XF0, 0XF4, 0XED, 0XF0, 0XF4, 0XEE, 0XF1, 0XF5, 0XED,
    0XEF, 0XF3, 0XF0, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XF0, 0XEF, 0XF3, 0XF0, 0XEF,
    0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF0,
    0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XEF, 0XEB, 0XEA, 0XEE, 0XEA, 0XE9, 0XEC, 0XE9, 0XE8, 0XEA, 0XE8,
    0XE7, 0XE9, 0XE5, 0XE4, 0XE6, 0XE4, 0XE3, 0XE5, 0XE2, 0XE1, 0XE3, 0XE0, 0XDF, 0XE1, 0XDE, 0XDD,
    0XDF, 0XDC, 0XDB, 0XDD, 0XD8, 0XD7, 0XD9, 0XD4, 0XD3, 0XD5, 0XD0, 0XCF, 0XD2, 0XCB, 0XCA, 0XCF,
    0XC3, 0XC1, 0XC8, 0XBB, 0XB8, 0XC2, 0XB3, 0XAF, 0XBB, 0XB0, 0XAA, 0XBA, 0XA8, 0XA2, 0XB5, 0XA5,
    0X9D, 0XB4, 0XA1, 0X9E, 0XB8, 0X9E, 0X9B, 0XB6, 0X9A, 0X9F, 0XC3, 0X8B, 0XA0, 0XD6, 0X84, 0XA2,
    0XDD, 0X8A, 0XA6, 0XDD, 0X70, 0X8D, 0XC8, 0X70, 0X8E, 0XCC, 0X8D, 0XA6, 0XDA, 0X89, 0XA4, 0XDC,
    0X9B, 0XB6, 0XE7, 0X9B, 0XBB, 0XDE, 0X8A, 0XAF, 0XE4, 0X72, 0X98, 0XD9, 0X92, 0XB1, 0XEA, 0X85,
    0XAA, 0XE4, 0X5A, 0X89, 0XD6, 0X7F, 0XA5, 0XE4, 0X8A, 0XAB, 0XE7, 0X83, 0XA6, 0XF0, 0X53, 0X72,
    0XDD, 0X8A, 0XA4, 0XF8, 0X8D, 0XA3, 0XED, 0X8A, 0XA3, 0XE9, 0X98, 0XAB, 0XF5, 0X84, 0X86, 0XF2,
    0X72, 0X6A, 0XEF, 0X75, 0X6E, 0XEF, 0X80, 0X82, 0XF0, 0X99, 0XA6, 0XFA, 0X7A, 0X7E, 0XEF, 0X6C,
    0X5E, 0XF0, 0X7A, 0X65, 0XF7, 0X79, 0X5B, 0XFA, 0X76, 0X54, 0XFA, 0X74, 0X57, 0XF4, 0X75, 0X52,
    0XFA, 0X77, 0X51, 0XFC, 0X78, 0X53, 0XFC, 0X77, 0X53, 0XFB, 0X75, 0X55, 0XF7, 0X74, 0X53, 0XF8,
    0X75, 0X51, 0XFB, 0X76, 0X54, 0XF3, 0X88, 0X6F, 0XEC, 0XDC, 0XD4, 0XFA, 0XF6, 0XF4, 0XFD, 0XF0,
    0XF0, 0XFB, 0XEE, 0XF1, 0XF6, 0XEF, 0XF0, 0XF8, 0XF1, 0XEF, 0XFA, 0XF4, 0XF0, 0XF9, 0XF2, 0XEF,
    0XF9, 0XEF, 0XEE, 0XF7, 0XEF, 0XEE, 0XF7, 0XEF, 0XEE, 0XF7, 0XEE, 0XED, 0XF5, 0XED, 0XED, 0XF3,
    0XED, 0XED, 0XF3, 0XEC, 0XEC, 0XF2, 0XED, 0XED, 0XF3, 0XEC, 0XEC, 0XF2, 0XEC, 0XEC, 0XF2, 0XEF,
    0XEC, 0XF3, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XEC, 0XEB,
    0XEF, 0XEB, 0XEA, 0XEE, 0XEB, 0XEA, 0XEE, 0XEA, 0XE9, 0XEC, 0XE8, 0XE8, 0XE9, 0XE8, 0XE7, 0XE9,
    0XE7, 0XE6, 0XE8, 0XE8, 0XE5, 0XE7, 0XE7, 0XE4, 0XE6, 0XE4, 0XE1, 0XE3, 0XE3, 0XE0, 0XE2, 0XE2,
    0XDF, 0XE1, 0XE0, 0XDD, 0XDF, 0XDE, 0XDB, 0XDD, 0XDE, 0XDB, 0XDD, 0XDC, 0XD7, 0XDC, 0XD9, 0XD3,
    0XD7, 0XDA, 0XD2, 0XD5, 0XD3, 0XCD, 0XCF, 0XD0, 0XC9, 0XCA, 0XCE, 0XC5, 0XC6, 0XC6, 0XBE, 0XBF,
    0XC4, 0XBE, 0XBE, 0XC4, 0XB0, 0XB3, 0XB5, 0X87, 0X8E, 0XA5, 0X62, 0X6C, 0X9F, 0X51, 0X5A, 0XA4,
    0X51, 0X5B, 0XAA, 0X55, 0X5C, 0XA9, 0X52, 0X5A, 0XA8, 0X50, 0X5E, 0XAA, 0X52, 0X60, 0XAA, 0X4B,
    0X5A, 0X9C, 0X33, 0X43, 0X96, 0X25, 0X35, 0X9D, 0X31, 0X40, 0XBC, 0X58, 0X64, 0XCE, 0X6F, 0X71,
    0XF6, 0XF4, 0XF4, 0XF5, 0XF3, 0XF3, 0XF7, 0XF5, 0XF5, 0XF5, 0XF3, 0XF3, 0XF5, 0XF4, 0XF4, 0XF4,
    0XF4, 0XF4, 0XF3, 0XF2, 0XF2, 0XF3, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0,
    0XF0, 0XF3, 0XF1, 0XF1, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF,
    0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE,
    0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7,
    0XE7, 0XE7, 0XE5, 0XE5, 0XE5, 0XE3, 0XE3, 0XE5, 0XE3, 0XE3, 0XE4, 0XE2, 0XE1, 0XE2, 0XE0, 0XDF,
    0XE1, 0XE0, 0XDD, 0XE0, 0XDF, 0XDB, 0XDF, 0XDE, 0XD9, 0XDD, 0XDB, 0XD6, 0XDC, 0XD8, 0XD5, 0XD9,
    0XD5, 0XD3, 0XD7, 0XD2, 0XD0, 0XD4, 0XD0, 0XCC, 0XD3, 0XCE, 0XCB, 0XCF, 0XCB, 0XC5, 0XC9, 0XC7,
    0XBE, 0XC7, 0XC4, 0XBB, 0XC3, 0XBF, 0XB5, 0XBD, 0XBA, 0XAD, 0XBA, 0XB6, 0XA7, 0XB1, 0XAD, 0X9C,
    0XAA, 0XA6, 0X94, 0XA6, 0XA2, 0X8C, 0XA1, 0X9C, 0X83, 0X9A, 0X94, 0X79, 0X8F, 0X8D, 0X6D, 0X8C,
    0X8C, 0X66, 0X85, 0X86, 0X5B, 0X86, 0X87, 0X54, 0X7E, 0X82, 0X3F, 0X6B, 0X73, 0X16, 0X68, 0X70,
    0X04, 0X6C, 0X72, 0X01, 0X6A, 0X70, 0X00, 0X68, 0X71, 0X01, 0X67, 0X72, 0X00, 0X66, 0X71, 0X00,
    0X61, 0X6C, 0X04, 0X5F, 0X6B, 0X03, 0X53, 0X5D, 0X00, 0X4C, 0X56, 0X00, 0X61, 0X71, 0X08, 0X5B,
    0X72, 0X02, 0X56, 0X6F, 0X00, 0X5C, 0X77, 0X04, 0X5F, 0X7E, 0X00, 0X63, 0X82, 0X00, 0X68, 0X87,
    0X01, 0X6A, 0X8A, 0X00, 0X6C, 0X8C, 0X00, 0X6D, 0X8E, 0X00, 0X6B, 0X8B, 0X01, 0X6A, 0X8A, 0X00,
    0X6C, 0X8C, 0X02, 0X6C, 0X8D, 0X02, 0X6A, 0X8B, 0X00, 0X69, 0X8A, 0X00, 0X6E, 0X8D, 0X02, 0X6E,
    0X8C, 0X01, 0X70, 0X8E, 0X03, 0X6F, 0X8F, 0X01, 0X6E, 0X8E, 0X00, 0X6E, 0X8F, 0X00, 0X71, 0X91,
    0X01, 0X72, 0X94, 0X00, 0X72, 0X96, 0X00, 0X78, 0X9B, 0X01, 0X7E, 0X9F, 0X03, 0X84, 0XA6, 0X03,
    0X82, 0XA5, 0X00, 0X81, 0XA1, 0X03, 0X7C, 0X9F, 0X00, 0X78, 0X9D, 0X00, 0X79, 0X9D, 0X01, 0X7F,
    0XA3, 0X00, 0X84, 0XA3, 0X00, 0X83, 0XA1, 0X01, 0X89, 0XA2, 0X05, 0X89, 0XA1, 0X00, 0X90, 0XA3,
    0X23, 0XDA, 0XE0, 0XAE, 0XF9, 0XF7, 0XF0, 0XEF, 0XEF, 0XEA, 0XED, 0XED, 0XEC, 0XED, 0XED, 0XEC,
    0XEF, 0XED, 0XEC, 0XEF, 0XEC, 0XEB, 0XEF, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEB, 0XEA, 0XEB, 0XEC,
    0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE6, 0XE4,
    0XE4, 0XE5, 0XE3, 0XE3, 0XE3, 0XE2, 0XE2, 0XE1, 0XE0, 0XE0, 0XDF, 0XDD, 0XDD, 0XDC, 0XDA, 0XDA,
    0XDA, 0XD8, 0XD8, 0XD7, 0XD4, 0XD4, 0XD4, 0XD1, 0XD2, 0XCE, 0XCB, 0XCB, 0XCB, 0XC5, 0XC6, 0XC4,
    0XBF, 0XC0, 0XBE, 0XB9, 0XBA, 0XB9, 0XB5, 0XB5, 0XBA, 0XB7, 0XB8, 0XBA, 0XB7, 0XB8, 0XBA, 0XB8,
    0XB7, 0XB8, 0XB5, 0XB2, 0XB8, 0XB5, 0XB5, 0XB9, 0XB4, 0XB7, 0XAF, 0XB0, 0XB8, 0X9D, 0XAE, 0XC5,
    0X74, 0X97, 0XBF, 0X72, 0X98, 0XC5, 0X86, 0XA9, 0XD3, 0X77, 0X9F, 0XCE, 0X52, 0X84, 0XBC, 0X61,
    0X8F, 0XC8, 0X88, 0XAA, 0XD6, 0XA2, 0XC2, 0XE4, 0X95, 0XB5, 0XE0, 0XA5, 0XC4, 0XE8, 0X99, 0XC0,
    0XE8, 0X83, 0XAA, 0XDC, 0XB8, 0XD5, 0XFA, 0X7C, 0XA6, 0XD7, 0X88, 0XAF, 0XE1, 0X9E, 0XC3, 0XED,
    0XA8, 0XC6, 0XE4, 0XAA, 0XCD, 0XF2, 0X9E, 0XC3, 0XE9, 0XB4, 0XD1, 0XEF, 0XBA, 0XD4, 0XF4, 0XAF,
    0XCD, 0XF3, 0X8D, 0XBC, 0XEC, 0X90, 0XBD, 0XE9, 0XBA, 0XD6, 0XF8, 0XB7, 0XD3, 0XF3, 0XAF, 0XCD,
    0XF0, 0XB7, 0XD3, 0XF6, 0XB9, 0XD2, 0XF6, 0XC3, 0XD6, 0XF3, 0XD4, 0XE0, 0XF4, 0XEC, 0XF1, 0XF9,
    0XEF, 0XF1, 0XF6, 0XF0, 0XEF, 0XF7, 0XEF, 0XEF, 0XF6, 0XEC, 0XEF, 0XF3, 0XED, 0XF0, 0XF5, 0XED,
    0XF0, 0XF3, 0XEF, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XEF, 0XF2, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE,
    0XF2, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEF, 0XEE, 0XF2, 0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0,
    0XEE, 0XEB, 0XF2, 0XEB, 0XEA, 0XEF, 0XEA, 0XE9, 0XEC, 0XE9, 0XE8, 0XEA, 0XE8, 0XE7, 0XE9, 0XE6,
    0XE5, 0XE7, 0XE5, 0XE4, 0XE7, 0XE4, 0XE3, 0XE6, 0XE1, 0XE0, 0XE2, 0XDE, 0XDD, 0XDF, 0XDC, 0XDB,
    0XDD, 0XDA, 0XD9, 0XDB, 0XD6, 0XD5, 0XD7, 0XD1, 0XD0, 0XD4, 0XCE, 0XCD, 0XD1, 0XCA, 0XC8, 0XCE,
    0XC4, 0XBE, 0XC8, 0XBC, 0XB6, 0XC2, 0XAF, 0XAD, 0XBB, 0XA6, 0XA7, 0XB6, 0XA5, 0XA2, 0XB5, 0XA6,
    0X9D, 0XB4, 0XA8, 0X9E, 0XB7, 0XA0, 0XA0, 0XB5, 0X96, 0XA6, 0XD3, 0X80, 0X9A, 0XD4, 0X91, 0XAA,
    0XDF, 0X7B, 0X94, 0XD5, 0X71, 0X8E, 0XCF, 0X86, 0XA4, 0XDD, 0X89, 0XA0, 0XD6, 0X96, 0XAC, 0XDF,
    0X89, 0XAA, 0XE2, 0X94, 0XB5, 0XDF, 0X85, 0XA7, 0XDC, 0X71, 0X9A, 0XDE, 0X7C, 0XA3, 0XDC, 0X79,
    0XA2, 0XE3, 0X70, 0XA0, 0XE0, 0X8F, 0XB4, 0XE9, 0X74, 0X96, 0XD9, 0X71, 0X95, 0XE9, 0X72, 0X8D,
    0XE9, 0X8B, 0XA6, 0XF3, 0X85, 0XA5, 0XE8, 0X93, 0XAF, 0XEC, 0X94, 0XAC, 0XF1, 0X8B, 0X9A, 0XEC,
    0X90, 0X98, 0XF5, 0X84, 0X8C, 0XE8, 0X9D, 0XAF, 0XF4, 0XA3, 0XB8, 0XF3, 0X8A, 0X97, 0XE8, 0X7A,
    0X75, 0XEF, 0X78, 0X65, 0XF9, 0X78, 0X5F, 0XF8, 0X7A, 0X59, 0XFB, 0X77, 0X54, 0XFA, 0X74, 0X51,
    0XF8, 0X75, 0X50, 0XFA, 0X76, 0X52, 0XFB, 0X76, 0X54, 0XFA, 0X75, 0X56, 0XF9, 0X73, 0X50, 0XFA,
    0X76, 0X4F, 0XFC, 0X7C, 0X59, 0XEE, 0XBA, 0XAC, 0XF4, 0XF5, 0XF4, 0XFE, 0XF0, 0XEE, 0XFA, 0XF1,
    0XF1, 0XFB, 0XF1, 0XF1, 0XF8, 0XEF, 0XF0, 0XF6, 0XF1, 0XF0, 0XF9, 0XF3, 0XF1, 0XFA, 0XF0, 0XEE,
    0XF8, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF7, 0XEF, 0XEE, 0XF7, 0XED, 0XED, 0XF5, 0XEE, 0XEE, 0XF5,
    0XEF, 0XEF, 0XF5, 0XEC, 0XEC, 0XF2, 0XEE, 0XED, 0XF2, 0XF0, 0XEF, 0XF3, 0XED, 0XEC, 0XF1, 0XEE,
    0XED, 0XF1, 0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XEF, 0XED, 0XEC,
    0XF0, 0XEB, 0XEA, 0XEE, 0XEB, 0XEA, 0XEE, 0XE9, 0XE7, 0XEA, 0XE9, 0XE6, 0XE8, 0XE8, 0XE5, 0XE7,
    0XE6, 0XE3, 0XE5, 0XE7, 0XE3, 0XE5, 0XE7, 0XE3, 0XE5, 0XE4, 0XE0, 0XE2, 0XE1, 0XDE, 0XE0, 0XDD,
    0XDE, 0XDF, 0XDD, 0XDC, 0XDE, 0XDB, 0XD9, 0XDB, 0XDC, 0XD7, 0XD9, 0XDB, 0XD3, 0XD5, 0XD4, 0XCE,
    0XD0, 0XD2, 0XCC, 0XCE, 0XCE, 0XC7, 0XC8, 0XCC, 0XC1, 0XC3, 0XCC, 0XBE, 0XC1, 0XC8, 0XB9, 0XBC,
    0XC1, 0XA2, 0XA8, 0XA9, 0X77, 0X7F, 0XA1, 0X5E, 0X66, 0XA5, 0X54, 0X5D, 0XA8, 0X53, 0X5C, 0XA5,
    0X4E, 0X5A, 0XA8, 0X4F, 0X5D, 0XAC, 0X51, 0X60, 0XAD, 0X50, 0X60, 0XA5, 0X42, 0X52, 0X92, 0X2B,
    0X38, 0X94, 0X29, 0X36, 0XAE, 0X43, 0X4E, 0XC8, 0X62, 0X6A, 0XCD, 0X6F, 0X71, 0XCA, 0X62, 0X5B,
    0XF7, 0XF5, 0XF5, 0XF6, 0XF4, 0XF4, 0XF7, 0XF5, 0XF5, 0XF6, 0XF4, 0XF4, 0XF4, 0XF3, 0XF3, 0XF3,
    0XF4, 0XF4, 0XF3, 0XF3, 0XF3, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF4, 0XF2,
    0XF2, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0,
    0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF,
    0XED, 0XED, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6,
    0XE6, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5, 0XE5, 0XE3, 0XE3, 0XE3, 0XE1, 0XE1,
    0XE2, 0XE0, 0XDD, 0XE2, 0XE1, 0XDC, 0XE0, 0XE0, 0XDA, 0XDF, 0XDF, 0XD9, 0XDD, 0XDB, 0XD7, 0XDB,
    0XD7, 0XD5, 0XDA, 0XD5, 0XD4, 0XD7, 0XD2, 0XD0, 0XD6, 0XD1, 0XCD, 0XD2, 0XCE, 0XC8, 0XCD, 0XCA,
    0XC2, 0XCC, 0XC8, 0XC0, 0XC7, 0XC2, 0XB9, 0XC2, 0XBE, 0XB4, 0XBF, 0XBB, 0XAE, 0XB8, 0XB2, 0XA4,
    0XB3, 0XAF, 0X9E, 0XAB, 0XA8, 0X95, 0XA4, 0X9F, 0X89, 0XA1, 0X9A, 0X80, 0X99, 0X93, 0X79, 0X8F,
    0X8C, 0X6F, 0X88, 0X88, 0X63, 0X87, 0X88, 0X5D, 0X87, 0X88, 0X55, 0X80, 0X83, 0X3F, 0X68, 0X6E,
    0X10, 0X6B, 0X73, 0X00, 0X6B, 0X73, 0X00, 0X68, 0X70, 0X01, 0X67, 0X71, 0X02, 0X66, 0X71, 0X00,
    0X64, 0X70, 0X01, 0X61, 0X6E, 0X03, 0X5E, 0X69, 0X01, 0X4F, 0X58, 0X00, 0X4F, 0X58, 0X00, 0X5D,
    0X6F, 0X05, 0X58, 0X71, 0X00, 0X57, 0X72, 0X00, 0X5C, 0X79, 0X00, 0X61, 0X7E, 0X03, 0X64, 0X82,
    0X02, 0X67, 0X86, 0X00, 0X6A, 0X8A, 0X00, 0X6E, 0X8D, 0X01, 0X6E, 0X8C, 0X02, 0X6B, 0X89, 0X00,
    0X6C, 0X8B, 0X01, 0X69, 0X8A, 0X00, 0X6A, 0X8B, 0X01, 0X6A, 0X8B, 0X00, 0X6C, 0X8A, 0X00, 0X6F,
    0X8B, 0X02, 0X70, 0X8C, 0X02, 0X6E, 0X8E, 0X00, 0X6D, 0X8E, 0X00, 0X6E, 0X8F, 0X00, 0X70, 0X91,
    0X01, 0X76, 0X98, 0X03, 0X75, 0X99, 0X01, 0X75, 0X9B, 0X00, 0X7B, 0XA0, 0X00, 0X7E, 0XA1, 0X00,
    0X7F, 0XA2, 0X00, 0X85, 0XA6, 0X06, 0X81, 0XA3, 0X04, 0X7B, 0X9E, 0X02, 0X7B, 0X9B, 0X04, 0X7B,
    0X9B, 0X01, 0X80, 0XA0, 0X01, 0X82, 0XA8, 0X01, 0X81, 0XA8, 0X00, 0X80, 0XA4, 0X02, 0X7E, 0X9F,
    0X00, 0X89, 0XA5, 0X29, 0XDA, 0XE5, 0XBC, 0XF5, 0XF5, 0XF1, 0XEE, 0XEE, 0XE9, 0XEE, 0XED, 0XEC,
    0XEE, 0XEC, 0XEC, 0XF1, 0XED, 0XEC, 0XF1, 0XED, 0XEC, 0XEE, 0XEC, 0XEC, 0XEC, 0XEA, 0XEC, 0XEC,
    0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE8, 0XE9, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE6, 0XE4,
    0XE4, 0XE5, 0XE3, 0XE3, 0XE4, 0XE1, 0XE1, 0XE2, 0XE0, 0XE0, 0XE0, 0XDE, 0XDE, 0XDD, 0XDB, 0XDB,
    0XDA, 0XD8, 0XD8, 0XD7, 0XD5, 0XD5, 0XD3, 0XD2, 0XD1, 0XD0, 0XCE, 0XCE, 0XCD, 0XC8, 0XC9, 0XC7,
    0XC2, 0XC3, 0XBD, 0XB8, 0XB9, 0XBA, 0XB7, 0XB7, 0XB8, 0XB6, 0XB6, 0XB5, 0XB4, 0XB4, 0XB9, 0XB7,
    0XB7, 0XB9, 0XB6, 0XB2, 0XB5, 0XB4, 0XB4, 0XB6, 0XB3, 0XB8, 0XB4, 0XB2, 0XB8, 0XA2, 0XAE, 0XC0,
    0X84, 0XA4, 0XC7, 0X6D, 0X93, 0XC0, 0X84, 0XA4, 0XD0, 0X7E, 0XA3, 0XCF, 0X4F, 0X82, 0XBB, 0X60,
    0X8C, 0XC8, 0X7B, 0X9E, 0XC7, 0X9D, 0XBE, 0XE2, 0X8C, 0XAF, 0XDF, 0X9C, 0XBD, 0XE6, 0X97, 0XBE,
    0XE6, 0X87, 0XAD, 0XDF, 0XB8, 0XD5, 0XF9, 0X7C, 0XA3, 0XD2, 0X8B, 0XAF, 0XE0, 0X9D, 0XC4, 0XEF,
    0XB0, 0XD0, 0XED, 0XA9, 0XCC, 0XF4, 0XA4, 0XCA, 0XEF, 0XB7, 0XD6, 0XF6, 0XB6, 0XCF, 0XF1, 0XB4,
    0XD2, 0XF7, 0X8B, 0XBD, 0XEF, 0X92, 0XC0, 0XEB, 0XB3, 0XCF, 0XF3, 0XB6, 0XD0, 0XF2, 0XBB, 0XD7,
    0XF7, 0XBA, 0XD4, 0XF9, 0XBF, 0XD6, 0XF7, 0XC8, 0XD8, 0XF3, 0XDF, 0XE8, 0XF8, 0XED, 0XF2, 0XFA,
    0XED, 0XF0, 0XF6, 0XEE, 0XF0, 0XF8, 0XEE, 0XF0, 0XF6, 0XED, 0XF0, 0XF4, 0XEE, 0XF1, 0XF5, 0XEE,
    0XF0, 0XF3, 0XEE, 0XF0, 0XF0, 0XEE, 0XEF, 0XF1, 0XEF, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE,
    0XF2, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0,
    0XEC, 0XEA, 0XF0, 0XEB, 0XEA, 0XEE, 0XEB, 0XEA, 0XED, 0XE8, 0XE7, 0XE8, 0XE6, 0XE5, 0XE7, 0XE5,
    0XE4, 0XE6, 0XE5, 0XE4, 0XE7, 0XE4, 0XE3, 0XE5, 0XE0, 0XDF, 0XE1, 0XDE, 0XDD, 0XDF, 0XDC, 0XDC,
    0XDC, 0XD8, 0XD7, 0XD9, 0XD4, 0XD3, 0XD5, 0XD0, 0XCF, 0XD3, 0XC8, 0XC7, 0XCB, 0XC6, 0XC3, 0XC8,
    0XC1, 0XBA, 0XC5, 0XB8, 0XB1, 0XBF, 0XAE, 0XAD, 0XBB, 0XA5, 0XA6, 0XB5, 0XA3, 0XA2, 0XB4, 0XA5,
    0X9D, 0XB4, 0XA9, 0X9D, 0XB5, 0XA2, 0XA6, 0XBD, 0X87, 0X9D, 0XCE, 0X81, 0X9C, 0XD7, 0X8F, 0XA6,
    0XDC, 0X6F, 0X88, 0XCD, 0X61, 0X80, 0XC1, 0X84, 0XA2, 0XD9, 0X8B, 0XA2, 0XD7, 0X9F, 0XB7, 0XE6,
    0X88, 0XAA, 0XE1, 0X91, 0XB1, 0XE3, 0X87, 0XA9, 0XE0, 0X76, 0X9C, 0XD9, 0X91, 0XB8, 0XF0, 0X65,
    0X91, 0XD9, 0X78, 0XA3, 0XE4, 0X6A, 0X98, 0XDA, 0X76, 0XA1, 0XE5, 0X81, 0XA5, 0XEB, 0X97, 0XB0,
    0XF6, 0X82, 0X9F, 0XED, 0X89, 0XA9, 0XE9, 0X99, 0XB3, 0XEF, 0X94, 0XA9, 0XF0, 0XA7, 0XBD, 0XFB,
    0X9B, 0XAD, 0XF0, 0X96, 0XA8, 0XED, 0XAA, 0XC0, 0XF5, 0XA5, 0XBB, 0XED, 0X97, 0XAB, 0XEB, 0X89,
    0X8C, 0XF7, 0X67, 0X5A, 0XEC, 0X72, 0X5A, 0XF7, 0X76, 0X58, 0XFD, 0X75, 0X54, 0XFA, 0X75, 0X53,
    0XF7, 0X75, 0X52, 0XF9, 0X76, 0X52, 0XFB, 0X74, 0X52, 0XFB, 0X71, 0X4F, 0XF9, 0X72, 0X50, 0XF9,
    0X74, 0X4F, 0XF4, 0X9A, 0X80, 0XF0, 0XE9, 0XE6, 0XFC, 0XEF, 0XEF, 0XF9, 0XF2, 0XF1, 0XFC, 0XF1,
    0XF0, 0XF9, 0XF0, 0XEF, 0XF8, 0XF2, 0XF1, 0XFA, 0XF0, 0XEF, 0XF8, 0XF1, 0XF0, 0XF9, 0XF0, 0XEF,
    0XF7, 0XEF, 0XEF, 0XF6, 0XEF, 0XEE, 0XF7, 0XEE, 0XED, 0XF6, 0XEC, 0XEB, 0XF4, 0XEC, 0XEC, 0XF3,
    0XEE, 0XEE, 0XF3, 0XEC, 0XEC, 0XF1, 0XEE, 0XED, 0XF1, 0XF0, 0XEF, 0XF3, 0XEE, 0XED, 0XF1, 0XED,
    0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XEE, 0XED, 0XF0, 0XED, 0XEC, 0XF0, 0XEB, 0XEA, 0XEE, 0XEA, 0XE9,
    0XED, 0XEA, 0XE9, 0XED, 0XE9, 0XE8, 0XEC, 0XE8, 0XE6, 0XE8, 0XE7, 0XE4, 0XE6, 0XE6, 0XE4, 0XE6,
    0XE6, 0XE3, 0XE4, 0XE2, 0XE1, 0XE3, 0XE3, 0XDF, 0XE1, 0XE3, 0XDD, 0XE0, 0XE0, 0XDB, 0XDE, 0XDC,
    0XDA, 0XDC, 0XDA, 0XD7, 0XD9, 0XD9, 0XD4, 0XD6, 0XD7, 0XD0, 0XD3, 0XD3, 0XCE, 0XCF, 0XD3, 0XCA,
    0XCD, 0XCE, 0XC6, 0XC7, 0XC7, 0XC0, 0XC1, 0XC7, 0XBC, 0XBE, 0XCA, 0XB3, 0XB6, 0XB7, 0X92, 0X96,
    0XA8, 0X6A, 0X73, 0XA0, 0X55, 0X60, 0XA2, 0X53, 0X5C, 0XA6, 0X52, 0X5A, 0XA6, 0X51, 0X5A, 0XA5,
    0X4E, 0X59, 0XAA, 0X4E, 0X5D, 0XA9, 0X4A, 0X5A, 0X9D, 0X38, 0X48, 0X91, 0X27, 0X34, 0X9C, 0X32,
    0X3A, 0XB7, 0X52, 0X56, 0XCC, 0X6C, 0X6E, 0XCD, 0X6C, 0X68, 0XBE, 0X57, 0X50, 0XAD, 0X37, 0X2B,
    0XF6, 0XF4, 0XF4, 0XF7, 0XF5, 0XF5, 0XF6, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF4, 0XF3, 0XF3, 0XF3,
    0XF3, 0XF3, 0XF4, 0XF4, 0XF4, 0XF5, 0XF3, 0XF3, 0XF4, 0XF2, 0XF2, 0XF4, 0XF2, 0XF2, 0XF4, 0XF2,
    0XF2, 0XF3, 0XF1, 0XF1, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF,
    0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE,
    0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEE, 0XEC, 0XEC, 0XEC, 0XEA, 0XEA, 0XEA, 0XE8, 0XE8, 0XE9, 0XE7,
    0XE7, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE7, 0XE5, 0XE5, 0XE6, 0XE4, 0XE4, 0XE6, 0XE3, 0XE3,
    0XE3, 0XE2, 0XDF, 0XE2, 0XE1, 0XDD, 0XE1, 0XE0, 0XDC, 0XE2, 0XE0, 0XDC, 0XE0, 0XDD, 0XD9, 0XDF,
    0XDA, 0XD9, 0XDD, 0XD8, 0XD5, 0XDB, 0XD4, 0XD1, 0XD8, 0XD3, 0XD0, 0XD5, 0XD1, 0XCC, 0XD0, 0XCD,
    0XC6, 0XCC, 0XC9, 0XC2, 0XCA, 0XC5, 0XBE, 0XC7, 0XC2, 0XB9, 0XC3, 0XBE, 0XB4, 0XBD, 0XB7, 0XAB,
    0XB7, 0XB2, 0XA4, 0XB0, 0XAB, 0X9C, 0XAB, 0XA4, 0X94, 0XA5, 0X9C, 0X88, 0X9E, 0X98, 0X81, 0X95,
    0X91, 0X77, 0X8E, 0X8D, 0X6E, 0X8C, 0X8A, 0X65, 0X8A, 0X87, 0X5D, 0X89, 0X86, 0X59, 0X7D, 0X7E,
    0X39, 0X68, 0X6F, 0X07, 0X69, 0X75, 0X00, 0X69, 0X73, 0X01, 0X68, 0X70, 0X04, 0X69, 0X72, 0X00,
    0X67, 0X75, 0X00, 0X63, 0X6F, 0X01, 0X61, 0X6B, 0X01, 0X5F, 0X68, 0X02, 0X4E, 0X56, 0X00, 0X53,
    0X60, 0X01, 0X60, 0X77, 0X03, 0X5A, 0X75, 0X00, 0X57, 0X71, 0X00, 0X5E, 0X78, 0X03, 0X63, 0X7E,
    0X04, 0X63, 0X81, 0X02, 0X68, 0X87, 0X03, 0X6A, 0X8A, 0X01, 0X6A, 0X8C, 0X00, 0X6A, 0X8A, 0X00,
    0X6D, 0X8C, 0X01, 0X6A, 0X8A, 0X00, 0X6A, 0X8B, 0X01, 0X6C, 0X8B, 0X01, 0X6B, 0X8A, 0X00, 0X6F,
    0X8C, 0X02, 0X6F, 0X8C, 0X02, 0X6D, 0X8E, 0X01, 0X6F, 0X8F, 0X02, 0X6E, 0X8E, 0X00, 0X70, 0X91,
    0X00, 0X73, 0X96, 0X01, 0X74, 0X98, 0X00, 0X77, 0X9D, 0X00, 0X7A, 0X9C, 0X02, 0X7E, 0X9D, 0X05,
    0X7C, 0X9B, 0X02, 0X81, 0XA3, 0X03, 0X87, 0XAA, 0X06, 0X81, 0XA2, 0X01, 0X7D, 0X9E, 0X01, 0X7D,
    0X99, 0X03, 0X7D, 0X96, 0X05, 0X7E, 0XA1, 0X01, 0X7F, 0XA6, 0X00, 0X7F, 0XA2, 0X00, 0X81, 0XA6,
    0X01, 0X79, 0XA0, 0X00, 0XA8, 0XB5, 0X74, 0XF2, 0XF0, 0XEB, 0XF1, 0XEE, 0XE9, 0XF1, 0XEF, 0XED,
    0XEE, 0XEC, 0XEC, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEF, 0XEC, 0XEC, 0XEF, 0XEB, 0XEC, 0XED,
    0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE8, 0XE8, 0XE9, 0XE7, 0XE7, 0XE7, 0XE5,
    0XE5, 0XE5, 0XE3, 0XE3, 0XE4, 0XE2, 0XE2, 0XE2, 0XE0, 0XE0, 0XE0, 0XDE, 0XDE, 0XDE, 0XDC, 0XDC,
    0XDA, 0XD8, 0XD8, 0XD8, 0XD6, 0XD6, 0XD5, 0XD3, 0XD3, 0XD2, 0XCF, 0XD0, 0XCD, 0XC8, 0XC9, 0XC9,
    0XC4, 0XC5, 0XC3, 0XC0, 0XC0, 0XBC, 0XBA, 0XBA, 0XB8, 0XB6, 0XB6, 0XBA, 0XB8, 0XB8, 0XB6, 0XB3,
    0XB3, 0XBA, 0XB9, 0XB8, 0XB4, 0XB4, 0XB4, 0XB5, 0XB2, 0XB4, 0XB6, 0XB4, 0XB7, 0XA8, 0XB2, 0XBE,
    0X96, 0XB2, 0XCF, 0X65, 0X8B, 0XB6, 0X86, 0XA6, 0XD1, 0X87, 0XA7, 0XD1, 0X4E, 0X7B, 0XB5, 0X6C,
    0X93, 0XCF, 0X7D, 0XA2, 0XCE, 0XA1, 0XC2, 0XED, 0X85, 0XAD, 0XE0, 0X87, 0XAE, 0XDC, 0X92, 0XB9,
    0XE2, 0X8B, 0XAF, 0XDE, 0XAC, 0XCA, 0XF0, 0X75, 0X9E, 0XCF, 0X80, 0XA7, 0XD9, 0X97, 0XBF, 0XEA,
    0XB1, 0XD1, 0XEF, 0XA5, 0XC7, 0XEE, 0XA3, 0XC6, 0XEA, 0XBB, 0XD9, 0XF7, 0XB0, 0XCD, 0XF2, 0XAD,
    0XCE, 0XF6, 0X85, 0XB5, 0XE9, 0X8D, 0XBC, 0XE8, 0XB5, 0XD3, 0XF6, 0XBB, 0XD6, 0XF5, 0XBC, 0XD8,
    0XF7, 0XB9, 0XD5, 0XF7, 0XBD, 0XD4, 0XF4, 0XC8, 0XD7, 0XF0, 0XE4, 0XEA, 0XF9, 0XEE, 0XF1, 0XF9,
    0XEC, 0XEF, 0XF5, 0XED, 0XF0, 0XF7, 0XEE, 0XF1, 0XF5, 0XED, 0XF0, 0XF5, 0XED, 0XF1, 0XF4, 0XEC,
    0XEF, 0XF3, 0XEC, 0XEE, 0XF1, 0XED, 0XEE, 0XF2, 0XEF, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE,
    0XF2, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XEC, 0XEB, 0XEF, 0XEC, 0XEB, 0XEF,
    0XEC, 0XEA, 0XEF, 0XEB, 0XEA, 0XEE, 0XEB, 0XEA, 0XED, 0XE8, 0XE7, 0XE9, 0XE6, 0XE5, 0XE7, 0XE5,
    0XE4, 0XE7, 0XE4, 0XE3, 0XE7, 0XE2, 0XE1, 0XE4, 0XDF, 0XDE, 0XE0, 0XDD, 0XDD, 0XDD, 0XDB, 0XDB,
    0XDB, 0XD7, 0XD7, 0XD7, 0XD3, 0XD2, 0XD4, 0XCE, 0XCD, 0XCF, 0XC8, 0XC7, 0XCC, 0XC3, 0XC1, 0XC7,
    0XBC, 0XB6, 0XC0, 0XB5, 0XAF, 0XBD, 0XAB, 0XA9, 0XB7, 0XA6, 0XA6, 0XB3, 0XA1, 0XA0, 0XB0, 0XA2,
    0X9D, 0XB2, 0XA2, 0X9A, 0XB3, 0X9C, 0XA6, 0XC6, 0X86, 0X9D, 0XD0, 0X80, 0X9A, 0XD2, 0X80, 0X9C,
    0XD6, 0X71, 0X8C, 0XCD, 0X81, 0X9F, 0XD9, 0X81, 0X9E, 0XD5, 0X88, 0XA4, 0XD5, 0X8D, 0XAC, 0XD6,
    0X8F, 0XAF, 0XDE, 0X97, 0XB5, 0XEC, 0X84, 0XA9, 0XE6, 0X89, 0XAF, 0XE5, 0X84, 0XA7, 0XE5, 0X6D,
    0X96, 0XDD, 0X76, 0X9F, 0XE4, 0X5F, 0X8F, 0XD2, 0X82, 0XAB, 0XE6, 0X9B, 0XBB, 0XF1, 0X91, 0XB1,
    0XE9, 0X85, 0XA8, 0XEC, 0X98, 0XB3, 0XF4, 0XA5, 0XBA, 0XF7, 0X90, 0XA5, 0XE3, 0XA4, 0XBC, 0XF1,
    0X9E, 0XB6, 0XEB, 0XAC, 0XC0, 0XF8, 0XA9, 0XBE, 0XF3, 0X9E, 0XB3, 0XEB, 0X9D, 0XB5, 0XF4, 0X82,
    0X8C, 0XF0, 0X68, 0X5E, 0XEE, 0X6F, 0X58, 0XFB, 0X70, 0X53, 0XFA, 0X73, 0X53, 0XF8, 0X72, 0X51,
    0XF9, 0X74, 0X4E, 0XFC, 0X77, 0X52, 0XFA, 0X73, 0X50, 0XF8, 0X6F, 0X4D, 0XF9, 0X72, 0X4F, 0XF8,
    0X7F, 0X63, 0XEA, 0XCD, 0XC5, 0XF7, 0XF3, 0XF6, 0XF8, 0XEF, 0XEE, 0XF7, 0XF1, 0XEF, 0XFA, 0XF0,
    0XEF, 0XF9, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE,
    0XF6, 0XEE, 0XEE, 0XF5, 0XEC, 0XEB, 0XF4, 0XEE, 0XED, 0XF6, 0XEE, 0XED, 0XF6, 0XED, 0XEC, 0XF4,
    0XED, 0XED, 0XF3, 0XED, 0XEE, 0XF2, 0XEE, 0XED, 0XF1, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XED,
    0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XEB, 0XEA, 0XEE, 0XEC, 0XEB, 0XEE, 0XEB, 0XEA, 0XEE, 0XE9, 0XE8,
    0XEA, 0XE8, 0XE7, 0XE9, 0XE5, 0XE3, 0XE6, 0XE8, 0XE5, 0XE7, 0XE6, 0XE3, 0XE5, 0XE4, 0XE1, 0XE4,
    0XE2, 0XDF, 0XE1, 0XE0, 0XDE, 0XE1, 0XE0, 0XDD, 0XDF, 0XE1, 0XDA, 0XDD, 0XDE, 0XD6, 0XD9, 0XDC,
    0XD5, 0XD8, 0XDB, 0XD3, 0XD6, 0XDA, 0XD0, 0XD3, 0XD4, 0XCC, 0XCF, 0XCA, 0XC8, 0XCA, 0XCA, 0XC1,
    0XC4, 0XCB, 0XBE, 0XC1, 0XC9, 0XBB, 0XBD, 0XC0, 0XAB, 0XAD, 0XAB, 0X82, 0X87, 0X9D, 0X5D, 0X66,
    0XA5, 0X55, 0X5F, 0XA6, 0X51, 0X5B, 0XA8, 0X52, 0X5D, 0XA6, 0X4F, 0X5A, 0XA8, 0X50, 0X5B, 0XB1,
    0X54, 0X5F, 0XAA, 0X45, 0X51, 0X99, 0X2E, 0X3A, 0X92, 0X26, 0X32, 0XA8, 0X40, 0X46, 0XC8, 0X63,
    0X63, 0XCD, 0X6D, 0X69, 0XC7, 0X64, 0X5E, 0XB4, 0X4A, 0X40, 0X9D, 0X2C, 0X1B, 0XA1, 0X27, 0X16,
    0XF4, 0XF4, 0XF4, 0XF5, 0XF4, 0XF4, 0XF5, 0XF4, 0XF4, 0XF3, 0XF3, 0XF3, 0XF4, 0XF4, 0XF4, 0XF3,
    0XF3, 0XF3, 0XF3, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1,
    0XF1, 0XF3, 0XF1, 0XF1, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF,
    0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0,
    0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA,
    0XEA, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE6, 0XE4, 0XE4,
    0XE4, 0XE2, 0XE1, 0XE3, 0XE1, 0XE0, 0XE1, 0XE0, 0XDD, 0XE1, 0XDF, 0XDB, 0XE2, 0XDE, 0XDB, 0XE1,
    0XDC, 0XD9, 0XE1, 0XDB, 0XD7, 0XDD, 0XD6, 0XD3, 0XDB, 0XD4, 0XD1, 0XD7, 0XD2, 0XCF, 0XD3, 0XCF,
    0XCA, 0XCF, 0XCC, 0XC7, 0XCE, 0XCA, 0XC5, 0XCC, 0XC5, 0XBF, 0XC6, 0XC0, 0XB8, 0XC1, 0XBB, 0XB1,
    0XBF, 0XB9, 0XAE, 0XB6, 0XB0, 0XA3, 0XB1, 0XAA, 0X9B, 0XAB, 0XA2, 0X91, 0XA3, 0X9C, 0X87, 0X9C,
    0X98, 0X81, 0X94, 0X91, 0X76, 0X8E, 0X8B, 0X6A, 0X8F, 0X89, 0X66, 0X87, 0X84, 0X63, 0X8A, 0X87,
    0X55, 0X78, 0X7B, 0X2A, 0X65, 0X70, 0X05, 0X66, 0X73, 0X00, 0X66, 0X72, 0X00, 0X6A, 0X72, 0X00,
    0X6B, 0X75, 0X00, 0X68, 0X74, 0X00, 0X66, 0X6F, 0X03, 0X64, 0X6B, 0X03, 0X61, 0X6C, 0X05, 0X50,
    0X5A, 0X00, 0X55, 0X64, 0X03, 0X61, 0X78, 0X05, 0X5A, 0X71, 0X00, 0X59, 0X71, 0X00, 0X61, 0X7B,
    0X04, 0X5F, 0X7A, 0X01, 0X61, 0X7D, 0X01, 0X66, 0X86, 0X02, 0X67, 0X88, 0X00, 0X6A, 0X89, 0X00,
    0X6B, 0X8A, 0X00, 0X6C, 0X8B, 0X00, 0X6D, 0X8C, 0X01, 0X6B, 0X8A, 0X00, 0X6C, 0X8B, 0X00, 0X6E,
    0X8B, 0X00, 0X6E, 0X8C, 0X00, 0X6D, 0X8C, 0X00, 0X6F, 0X8F, 0X01, 0X6D, 0X8D, 0X00, 0X6F, 0X90,
    0X00, 0X72, 0X95, 0X00, 0X71, 0X95, 0X00, 0X78, 0X9D, 0X00, 0X7A, 0X9A, 0X00, 0X78, 0X97, 0X00,
    0X79, 0X9B, 0X00, 0X7D, 0XA1, 0X00, 0X83, 0XA5, 0X01, 0X86, 0XA7, 0X01, 0X7E, 0XA2, 0X00, 0X7D,
    0X9F, 0X00, 0X7C, 0X9B, 0X02, 0X79, 0X9A, 0X03, 0X7B, 0XA0, 0X01, 0X7E, 0X9F, 0X03, 0X7F, 0XA1,
    0X06, 0X70, 0X98, 0X08, 0X98, 0XAF, 0X71, 0XDB, 0XDF, 0XDA, 0XF0, 0XF0, 0XEC, 0XEF, 0XED, 0XEA,
    0XF0, 0XEE, 0XEE, 0XEE, 0XED, 0XEF, 0XEC, 0XEB, 0XED, 0XEE, 0XEB, 0XEB, 0XF0, 0XEC, 0XEC, 0XEF,
    0XEB, 0XEC, 0XEE, 0XEA, 0XEB, 0XEC, 0XE8, 0XE9, 0XEC, 0XE7, 0XE8, 0XEC, 0XE7, 0XE8, 0XE9, 0XE5,
    0XE5, 0XE6, 0XE1, 0XE2, 0XE5, 0XE2, 0XE2, 0XE3, 0XE1, 0XE1, 0XE1, 0XDF, 0XDF, 0XDF, 0XDD, 0XDD,
    0XDC, 0XDA, 0XDA, 0XDA, 0XD8, 0XD8, 0XD7, 0XD5, 0XD5, 0XD3, 0XD0, 0XD0, 0XD1, 0XCC, 0XCD, 0XC9,
    0XC5, 0XC6, 0XC1, 0XBF, 0XBF, 0XBC, 0XBA, 0XBA, 0XBC, 0XBA, 0XBA, 0XBA, 0XB8, 0XB8, 0XBA, 0XB7,
    0XB7, 0XB5, 0XB6, 0XB7, 0XB2, 0XB1, 0XB3, 0XB7, 0XB5, 0XB5, 0XB6, 0XB3, 0XB4, 0XAC, 0XB1, 0XB9,
    0XA1, 0XB4, 0XCC, 0X73, 0X96, 0XBE, 0X86, 0XA6, 0XD1, 0X8E, 0XAD, 0XD9, 0X4F, 0X7B, 0XB8, 0X60,
    0X86, 0XC3, 0X78, 0XA0, 0XCE, 0X9A, 0XBA, 0XE8, 0X87, 0XB2, 0XE5, 0X8C, 0XB4, 0XE3, 0X96, 0XBB,
    0XE4, 0X90, 0XB4, 0XE1, 0XA5, 0XC5, 0XEB, 0X7D, 0XAA, 0XDA, 0X88, 0XB2, 0XE4, 0X92, 0XBB, 0XE8,
    0XA9, 0XCA, 0XE9, 0XA8, 0XC8, 0XF1, 0XAA, 0XC8, 0XEB, 0XB6, 0XD2, 0XF3, 0XA3, 0XC3, 0XEE, 0XB1,
    0XD3, 0XFC, 0X8A, 0XB9, 0XEB, 0X89, 0XB9, 0XE6, 0XB5, 0XD5, 0XF7, 0XC0, 0XDB, 0XF8, 0XBB, 0XD7,
    0XF5, 0XBA, 0XD6, 0XF8, 0XC2, 0XD8, 0XF6, 0XD1, 0XDD, 0XF3, 0XEB, 0XEF, 0XFB, 0XEF, 0XF1, 0XFA,
    0XEE, 0XF1, 0XF8, 0XED, 0XF0, 0XF5, 0XEC, 0XF0, 0XF4, 0XEB, 0XF1, 0XF3, 0XEC, 0XF1, 0XF4, 0XEB,
    0XEF, 0XF3, 0XEB, 0XEE, 0XF2, 0XEE, 0XF0, 0XF4, 0XEF, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE,
    0XF2, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XEF,
    0XEC, 0XEB, 0XEF, 0XEA, 0XE9, 0XED, 0XEB, 0XEA, 0XED, 0XE8, 0XE7, 0XE9, 0XE5, 0XE4, 0XE6, 0XE5,
    0XE4, 0XE7, 0XE4, 0XE3, 0XE7, 0XE1, 0XE0, 0XE3, 0XDE, 0XDD, 0XDE, 0XDC, 0XDC, 0XDC, 0XD9, 0XDA,
    0XD9, 0XD5, 0XD4, 0XD5, 0XD1, 0XD0, 0XD2, 0XCD, 0XCC, 0XCE, 0XC7, 0XC6, 0XCB, 0XC0, 0XBD, 0XC6,
    0XB9, 0XB4, 0XC0, 0XB2, 0XAD, 0XBC, 0XA8, 0XA6, 0XB4, 0XA2, 0XA3, 0XAE, 0XA1, 0XA1, 0XAF, 0X9F,
    0X9C, 0XAE, 0X9E, 0X9B, 0XB4, 0X97, 0XA7, 0XD0, 0X7F, 0X9A, 0XCF, 0X7E, 0X98, 0XCF, 0X72, 0X90,
    0XCE, 0X72, 0X8F, 0XCE, 0X8D, 0XA9, 0XDF, 0X84, 0XA1, 0XD7, 0X94, 0XB0, 0XE1, 0X96, 0XB5, 0XE1,
    0X8A, 0XAD, 0XDD, 0X8E, 0XB0, 0XE6, 0X76, 0X9E, 0XDE, 0X82, 0XAC, 0XE8, 0X6D, 0X96, 0XD8, 0X80,
    0XA7, 0XE6, 0X75, 0X9B, 0XDF, 0X83, 0XA9, 0XE7, 0XAF, 0XC7, 0XF5, 0X93, 0XB3, 0XEF, 0X85, 0XAE,
    0XE7, 0X88, 0XAC, 0XE9, 0X98, 0XAF, 0XF1, 0X9E, 0XB4, 0XEE, 0XA0, 0XB7, 0XEF, 0X95, 0XAF, 0XE1,
    0X9A, 0XB7, 0XE5, 0XA0, 0XBB, 0XEB, 0X9A, 0XB3, 0XE6, 0XA6, 0XBE, 0XF4, 0XA0, 0XB6, 0XFC, 0X7F,
    0X89, 0XF1, 0X6F, 0X66, 0XF2, 0X70, 0X5B, 0XF9, 0X71, 0X55, 0XF9, 0X73, 0X51, 0XF9, 0X71, 0X4E,
    0XF8, 0X74, 0X4F, 0XFB, 0X75, 0X51, 0XFA, 0X73, 0X50, 0XF6, 0X72, 0X4E, 0XF9, 0X72, 0X50, 0XF2,
    0XB1, 0XA2, 0XF2, 0XF1, 0XF3, 0XFC, 0XF0, 0XEF, 0XF8, 0XF2, 0XF0, 0XFA, 0XF1, 0XF0, 0XFA, 0XF0,
    0XEF, 0XF9, 0XF1, 0XF0, 0XF9, 0XEF, 0XEE, 0XF7, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF7, 0XEE, 0XED,
    0XF5, 0XEF, 0XED, 0XF3, 0XEE, 0XEC, 0XF3, 0XEF, 0XED, 0XF5, 0XEF, 0XEC, 0XF4, 0XEE, 0XED, 0XF3,
    0XEE, 0XEC, 0XF1, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF0, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XED,
    0XEC, 0XF0, 0XEC, 0XEB, 0XEF, 0XEA, 0XE9, 0XED, 0XEA, 0XE9, 0XED, 0XE9, 0XE8, 0XEB, 0XE9, 0XE7,
    0XE9, 0XE6, 0XE5, 0XE7, 0XE7, 0XE4, 0XE6, 0XE5, 0XE2, 0XE4, 0XE4, 0XE1, 0XE3, 0XE3, 0XDF, 0XE1,
    0XE0, 0XDC, 0XDE, 0XDF, 0XDE, 0XDF, 0XDF, 0XDB, 0XDD, 0XDF, 0XD7, 0XDA, 0XDD, 0XD3, 0XD7, 0XD7,
    0XD1, 0XD4, 0XD4, 0XCF, 0XD2, 0XD1, 0XC9, 0XCC, 0XCF, 0XC5, 0XC9, 0XC6, 0XBF, 0XC3, 0XC5, 0XBC,
    0XBF, 0XC8, 0XB6, 0XBA, 0XBC, 0X9C, 0XA1, 0XA7, 0X74, 0X7C, 0X9F, 0X5C, 0X65, 0XA3, 0X53, 0X5D,
    0XA4, 0X54, 0X5D, 0XA3, 0X50, 0X5C, 0XA8, 0X4F, 0X5D, 0XB0, 0X51, 0X62, 0XB1, 0X4E, 0X5E, 0X9F,
    0X38, 0X45, 0X95, 0X26, 0X31, 0X9F, 0X2D, 0X36, 0XB9, 0X4C, 0X54, 0XC8, 0X6A, 0X69, 0XC5, 0X6D,
    0X65, 0XC4, 0X61, 0X55, 0XAC, 0X38, 0X2C, 0XA0, 0X27, 0X16, 0XA2, 0X2D, 0X16, 0XA4, 0X2D, 0X17,
    0XF4, 0XF4, 0XF4, 0XF4, 0XF4, 0XF4, 0XF5, 0XF5, 0XF5, 0XF4, 0XF4, 0XF4, 0XF4, 0XF3, 0XF3, 0XF3,
    0XF3, 0XF3, 0XF3, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF6, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF4, 0XF2,
    0XF2, 0XF3, 0XF1, 0XF1, 0XF4, 0XF2, 0XF2, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF3, 0XF1, 0XF1,
    0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0,
    0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XEA,
    0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE5,
    0XE5, 0XE3, 0XE3, 0XE4, 0XE2, 0XE1, 0XE3, 0XE2, 0XE1, 0XE4, 0XE0, 0XDF, 0XE3, 0XDF, 0XDD, 0XE1,
    0XDD, 0XDA, 0XE1, 0XDC, 0XD9, 0XDD, 0XD8, 0XD5, 0XDC, 0XD7, 0XD4, 0XD9, 0XD4, 0XD1, 0XD7, 0XD3,
    0XCE, 0XD3, 0XCF, 0XCA, 0XD0, 0XCC, 0XC7, 0XCE, 0XC9, 0XC4, 0XCA, 0XC4, 0XBE, 0XC6, 0XC0, 0XB8,
    0XC2, 0XBC, 0XB2, 0XBC, 0XB7, 0XAB, 0XB7, 0XB1, 0XA1, 0XB2, 0XAB, 0X98, 0XA9, 0XA2, 0X8F, 0X9F,
    0X9B, 0X84, 0X99, 0X96, 0X7C, 0X95, 0X90, 0X72, 0X8E, 0X8A, 0X68, 0X89, 0X88, 0X64, 0X8A, 0X87,
    0X5D, 0X8C, 0X89, 0X54, 0X74, 0X78, 0X2B, 0X61, 0X6E, 0X03, 0X66, 0X75, 0X00, 0X6A, 0X73, 0X00,
    0X6B, 0X73, 0X00, 0X68, 0X71, 0X00, 0X67, 0X6D, 0X03, 0X66, 0X6E, 0X01, 0X65, 0X71, 0X01, 0X59,
    0X63, 0X02, 0X48, 0X51, 0X00, 0X58, 0X65, 0X06, 0X63, 0X75, 0X05, 0X5B, 0X71, 0X00, 0X5D, 0X76,
    0X00, 0X5F, 0X7A, 0X02, 0X5B, 0X77, 0X00, 0X61, 0X80, 0X01, 0X66, 0X86, 0X00, 0X68, 0X89, 0X00,
    0X69, 0X89, 0X00, 0X6B, 0X8A, 0X01, 0X6D, 0X8C, 0X01, 0X6C, 0X8B, 0X01, 0X6C, 0X8C, 0X01, 0X6D,
    0X8D, 0X01, 0X6C, 0X8C, 0X00, 0X6D, 0X8D, 0X01, 0X6F, 0X8F, 0X02, 0X70, 0X90, 0X01, 0X71, 0X92,
    0X01, 0X74, 0X97, 0X02, 0X74, 0X97, 0X00, 0X76, 0X9A, 0X01, 0X78, 0X98, 0X03, 0X74, 0X95, 0X00,
    0X78, 0X9E, 0X00, 0X85, 0XA9, 0X03, 0X89, 0XAB, 0X04, 0X84, 0XA6, 0X01, 0X7B, 0XA3, 0X00, 0X79,
    0XA4, 0X01, 0X7A, 0XA2, 0X00, 0X7D, 0XA3, 0X00, 0X7B, 0X9D, 0X00, 0X80, 0X9F, 0X03, 0X76, 0X9A,
    0X03, 0X85, 0XAA, 0X44, 0X8F, 0XAD, 0X8B, 0XBA, 0XC9, 0XC8, 0XE5, 0XE9, 0XEC, 0XF0, 0XEF, 0XEE,
    0XEF, 0XED, 0XEC, 0XEE, 0XED, 0XEF, 0XED, 0XEC, 0XEF, 0XEE, 0XEB, 0XEC, 0XEF, 0XEB, 0XEA, 0XEF,
    0XEA, 0XEB, 0XEE, 0XEA, 0XEB, 0XED, 0XE9, 0XEA, 0XED, 0XE8, 0XE9, 0XED, 0XE8, 0XE9, 0XEB, 0XE6,
    0XE7, 0XE7, 0XE3, 0XE3, 0XE4, 0XE2, 0XE2, 0XE3, 0XE1, 0XE1, 0XE1, 0XDF, 0XDF, 0XE0, 0XDE, 0XDE,
    0XDD, 0XDB, 0XDB, 0XDB, 0XD9, 0XD9, 0XD7, 0XD6, 0XD6, 0XD5, 0XD3, 0XD3, 0XD1, 0XCF, 0XCF, 0XCA,
    0XC8, 0XC8, 0XC3, 0XC1, 0XC1, 0XBE, 0XBC, 0XBC, 0XBC, 0XBA, 0XBA, 0XB8, 0XB8, 0XB8, 0XB8, 0XB8,
    0XB8, 0XB3, 0XB5, 0XB7, 0XB4, 0XB3, 0XB6, 0XB7, 0XB5, 0XB5, 0XB6, 0XB4, 0XB7, 0XAF, 0XB1, 0XB8,
    0XA9, 0XB5, 0XC6, 0X80, 0X9E, 0XC1, 0X77, 0X99, 0XC4, 0X8A, 0XAB, 0XDA, 0X47, 0X76, 0XB7, 0X62,
    0X8A, 0XC8, 0X75, 0X9E, 0XCC, 0X91, 0XB0, 0XDE, 0X8A, 0XB3, 0XE2, 0X94, 0XB9, 0XE3, 0XA4, 0XC8,
    0XF0, 0X93, 0XB8, 0XE5, 0XA2, 0XC4, 0XEB, 0X7A, 0XA9, 0XDB, 0X86, 0XB2, 0XE4, 0X90, 0XBA, 0XE7,
    0XAD, 0XCC, 0XEC, 0XA9, 0XC7, 0XEF, 0XB1, 0XCD, 0XF0, 0XBD, 0XDB, 0XFB, 0X9B, 0XBF, 0XEB, 0XAE,
    0XCF, 0XF7, 0XA3, 0XCC, 0XF9, 0X8D, 0XBC, 0XE9, 0XAF, 0XD1, 0XF3, 0XC5, 0XDF, 0XFB, 0XBE, 0XD9,
    0XF8, 0XB7, 0XD2, 0XF5, 0XC1, 0XD6, 0XF3, 0XD5, 0XDF, 0XF1, 0XEF, 0XF2, 0XFA, 0XEF, 0XF0, 0XF7,
    0XEE, 0XF0, 0XF7, 0XED, 0XF0, 0XF5, 0XEC, 0XEF, 0XF4, 0XEB, 0XF0, 0XF3, 0XEB, 0XF1, 0XF3, 0XEB,
    0XEF, 0XF3, 0XEC, 0XEF, 0XF3, 0XEE, 0XF0, 0XF4, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF2, 0XEE, 0XED,
    0XF1, 0XEF, 0XEE, 0XF1, 0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XEE, 0XED, 0XF1, 0XEC, 0XEB, 0XEF,
    0XEA, 0XE9, 0XEE, 0XE8, 0XE7, 0XEB, 0XEA, 0XE9, 0XEB, 0XE9, 0XE8, 0XE9, 0XE5, 0XE4, 0XE7, 0XE3,
    0XE2, 0XE6, 0XE3, 0XE2, 0XE6, 0XE0, 0XDF, 0XE2, 0XDD, 0XDC, 0XDE, 0XDB, 0XDB, 0XDC, 0XD9, 0XD9,
    0XD9, 0XD4, 0XD4, 0XD4, 0XD0, 0XCF, 0XD1, 0XCB, 0XCA, 0XCE, 0XC5, 0XC4, 0XC9, 0XBD, 0XBA, 0XC3,
    0XB4, 0XB1, 0XBE, 0XAD, 0XAA, 0XB9, 0XA7, 0XA4, 0XB2, 0XA3, 0XA1, 0XAD, 0XA0, 0X9F, 0XAD, 0XA0,
    0X9E, 0XB0, 0X9E, 0XA1, 0XBC, 0X91, 0XA3, 0XD5, 0X7C, 0X98, 0XCF, 0X8B, 0XA6, 0XDD, 0X6D, 0X8D,
    0XCA, 0X85, 0XA6, 0XE1, 0X85, 0XA2, 0XD7, 0X84, 0XA2, 0XD8, 0X99, 0XB2, 0XE3, 0X94, 0XAE, 0XE1,
    0X7F, 0XA3, 0XD9, 0X8C, 0XB2, 0XE6, 0X6D, 0X99, 0XDA, 0X4F, 0X7D, 0XC5, 0X64, 0X96, 0XDC, 0X7A,
    0XA9, 0XE6, 0X5A, 0X8B, 0XD7, 0X65, 0X92, 0XE0, 0X95, 0XAE, 0XEB, 0X87, 0XA5, 0XEA, 0X8B, 0XB5,
    0XF4, 0X8C, 0XB0, 0XEE, 0X97, 0XAD, 0XEC, 0X9E, 0XB9, 0XEE, 0XA6, 0XC1, 0XF5, 0X93, 0XB0, 0XE5,
    0X9E, 0XBD, 0XF1, 0X97, 0XB5, 0XE9, 0X99, 0XB5, 0XEC, 0XA1, 0XBD, 0XF1, 0X74, 0X84, 0XDC, 0X74,
    0X7B, 0XE6, 0X84, 0X80, 0XF5, 0X77, 0X63, 0XFA, 0X71, 0X55, 0XF8, 0X72, 0X54, 0XF6, 0X72, 0X52,
    0XF7, 0X71, 0X51, 0XFB, 0X6E, 0X4B, 0XFB, 0X72, 0X50, 0XF9, 0X6D, 0X4B, 0XED, 0X8F, 0X77, 0XEA,
    0XE6, 0XE3, 0XFD, 0XF0, 0XF4, 0XF7, 0XF2, 0XEE, 0XF9, 0XF1, 0XEE, 0XFB, 0XF1, 0XF0, 0XFA, 0XF0,
    0XEF, 0XF9, 0XF0, 0XEF, 0XF8, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF7, 0XEE, 0XED, 0XF6, 0XEE, 0XED,
    0XF5, 0XF0, 0XEE, 0XF4, 0XF0, 0XEE, 0XF4, 0XEF, 0XED, 0XF3, 0XEC, 0XEA, 0XF0, 0XEE, 0XEC, 0XF2,
    0XEC, 0XEB, 0XEF, 0XEC, 0XEC, 0XEF, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XEF, 0XEC, 0XEB, 0XEF, 0XEC,
    0XEB, 0XEF, 0XEB, 0XEA, 0XEE, 0XE9, 0XE8, 0XEC, 0XE8, 0XE7, 0XEB, 0XE7, 0XE5, 0XE9, 0XE6, 0XE3,
    0XE5, 0XE5, 0XE2, 0XE4, 0XE4, 0XE1, 0XE3, 0XE2, 0XDF, 0XE2, 0XE1, 0XDE, 0XE1, 0XE2, 0XDD, 0XDF,
    0XE0, 0XDB, 0XDE, 0XDD, 0XDA, 0XDC, 0XDE, 0XD7, 0XDA, 0XDB, 0XD2, 0XD5, 0XD8, 0XD0, 0XD3, 0XD3,
    0XCE, 0XD0, 0XCD, 0XC9, 0XCB, 0XC8, 0XC3, 0XC5, 0XC6, 0XBE, 0XC0, 0XC8, 0XBB, 0XBE, 0XC5, 0XAE,
    0XB3, 0XB0, 0X88, 0X90, 0XA2, 0X67, 0X70, 0XA0, 0X56, 0X62, 0XA6, 0X53, 0X5F, 0XA8, 0X50, 0X5D,
    0XA2, 0X51, 0X5D, 0XA4, 0X4E, 0X5C, 0XAF, 0X4D, 0X60, 0XAB, 0X43, 0X57, 0X98, 0X2D, 0X3F, 0X8D,
    0X24, 0X32, 0XA3, 0X3A, 0X42, 0XC4, 0X5C, 0X62, 0XCD, 0X6C, 0X6D, 0XC4, 0X69, 0X64, 0XBC, 0X5D,
    0X52, 0XA3, 0X35, 0X28, 0XA4, 0X25, 0X18, 0XAB, 0X2B, 0X1A, 0XA3, 0X2B, 0X15, 0X9E, 0X2A, 0X13,
    0XF7, 0XF5, 0XF5, 0XF7, 0XF5, 0XF5, 0XF5, 0XF3, 0XF3, 0XF6, 0XF3, 0XF3, 0XF6, 0XF5, 0XF5, 0XF5,
    0XF5, 0XF5, 0XF4, 0XF4, 0XF4, 0XF5, 0XF4, 0XF4, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF4, 0XF2,
    0XF2, 0XF4, 0XF2, 0XF2, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF4, 0XF2, 0XF2, 0XF2, 0XF0, 0XF0,
    0XF2, 0XF0, 0XF0, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0,
    0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEF, 0XED, 0XED, 0XEE, 0XEC,
    0XEC, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE8, 0XE9, 0XE6, 0XE7, 0XE8, 0XE6, 0XE6,
    0XE8, 0XE6, 0XE6, 0XE5, 0XE3, 0XE2, 0XE4, 0XE2, 0XE2, 0XE3, 0XE1, 0XE1, 0XE3, 0XE0, 0XDF, 0XE3,
    0XDF, 0XDC, 0XE0, 0XDC, 0XD9, 0XE0, 0XDB, 0XD8, 0XE0, 0XDB, 0XD8, 0XDC, 0XD7, 0XD4, 0XD9, 0XD6,
    0XD1, 0XD6, 0XD2, 0XCD, 0XD2, 0XCE, 0XC9, 0XD0, 0XCB, 0XC6, 0XCD, 0XC7, 0XC2, 0XCA, 0XC5, 0XBD,
    0XC6, 0XC0, 0XB7, 0XBF, 0XBC, 0XB1, 0XBC, 0XB8, 0XA9, 0XB4, 0XAF, 0X9C, 0XAE, 0XA9, 0X95, 0XA4,
    0XA0, 0X8B, 0X9E, 0X9C, 0X84, 0X9D, 0X98, 0X7C, 0X91, 0X8E, 0X6E, 0X8E, 0X8E, 0X68, 0X8D, 0X89,
    0X65, 0X8B, 0X84, 0X61, 0X86, 0X85, 0X52, 0X6E, 0X78, 0X22, 0X64, 0X71, 0X04, 0X67, 0X71, 0X01,
    0X6A, 0X72, 0X02, 0X65, 0X6C, 0X01, 0X68, 0X6F, 0X02, 0X6A, 0X74, 0X00, 0X67, 0X6F, 0X00, 0X62,
    0X6C, 0X02, 0X57, 0X5F, 0X04, 0X4D, 0X53, 0X01, 0X5E, 0X6C, 0X03, 0X64, 0X76, 0X05, 0X59, 0X71,
    0X00, 0X5E, 0X78, 0X01, 0X60, 0X7B, 0X04, 0X5F, 0X7C, 0X01, 0X65, 0X83, 0X01, 0X68, 0X88, 0X00,
    0X67, 0X88, 0X00, 0X6A, 0X8A, 0X00, 0X6D, 0X8C, 0X01, 0X6F, 0X8C, 0X02, 0X6E, 0X8C, 0X00, 0X6D,
    0X8D, 0X00, 0X6E, 0X8E, 0X03, 0X6E, 0X8D, 0X02, 0X71, 0X91, 0X04, 0X71, 0X92, 0X03, 0X72, 0X93,
    0X02, 0X74, 0X95, 0X03, 0X72, 0X94, 0X00, 0X74, 0X97, 0X03, 0X73, 0X95, 0X05, 0X72, 0X96, 0X03,
    0X77, 0X9D, 0X01, 0X80, 0XA2, 0X03, 0X92, 0XB4, 0X09, 0X7F, 0XA3, 0X03, 0X84, 0XAA, 0X2A, 0X85,
    0XAC, 0X35, 0X8B, 0XAF, 0X32, 0X73, 0X9E, 0X0A, 0X79, 0XA2, 0X14, 0X75, 0X9C, 0X0E, 0X6E, 0X98,
    0X12, 0X90, 0XB2, 0X7B, 0XA6, 0XC5, 0XCD, 0XAC, 0XC3, 0XD3, 0XCA, 0XD6, 0XE2, 0XEB, 0XEF, 0XF2,
    0XEF, 0XED, 0XEC, 0XEE, 0XED, 0XEF, 0XEB, 0XED, 0XF0, 0XEE, 0XED, 0XEE, 0XEF, 0XEB, 0XEB, 0XED,
    0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7, 0XE9, 0XE7,
    0XE7, 0XE8, 0XE5, 0XE5, 0XE4, 0XE3, 0XE3, 0XE2, 0XE3, 0XE3, 0XE1, 0XE1, 0XE1, 0XDE, 0XDE, 0XDE,
    0XDC, 0XDC, 0XDC, 0XDA, 0XDA, 0XDA, 0XD6, 0XD6, 0XD6, 0XD4, 0XD3, 0XD3, 0XD0, 0XCE, 0XCE, 0XCC,
    0XCA, 0XCA, 0XC6, 0XC4, 0XC4, 0XC2, 0XC0, 0XC0, 0XBD, 0XBC, 0XBC, 0XB5, 0XB5, 0XB5, 0XB3, 0XB2,
    0XB3, 0XB5, 0XB5, 0XB9, 0XB7, 0XB5, 0XB8, 0XB5, 0XB4, 0XB6, 0XB2, 0XB3, 0XB7, 0XB1, 0XB1, 0XB8,
    0XAC, 0XB2, 0XC0, 0X81, 0X9A, 0XB9, 0X73, 0X96, 0XC1, 0X88, 0XAB, 0XDC, 0X46, 0X76, 0XB9, 0X5A,
    0X87, 0XC2, 0X7B, 0XA3, 0XD0, 0X84, 0XA4, 0XD3, 0X95, 0XBC, 0XE7, 0X9C, 0XBF, 0XE5, 0XA1, 0XC2,
    0XED, 0X8C, 0XB2, 0XE0, 0X9C, 0XBF, 0XE7, 0X78, 0XAA, 0XDE, 0X7E, 0XAC, 0XE1, 0X8A, 0XB4, 0XE1,
    0XBA, 0XD6, 0XF6, 0XAA, 0XC6, 0XEF, 0XAC, 0XC8, 0XEA, 0XC2, 0XE0, 0XFA, 0X9F, 0XC4, 0XEE, 0XA9,
    0XC7, 0XEF, 0XAB, 0XCE, 0XF5, 0X98, 0XC3, 0XEF, 0XAD, 0XD0, 0XF4, 0XB7, 0XD1, 0XEF, 0XBD, 0XD7,
    0XF8, 0XB9, 0XD4, 0XF7, 0XC2, 0XD6, 0XF3, 0XDD, 0XE6, 0XF4, 0XF3, 0XF3, 0XF9, 0XF0, 0XF1, 0XF6,
    0XEC, 0XEE, 0XF5, 0XEC, 0XEF, 0XF4, 0XED, 0XF0, 0XF5, 0XEC, 0XF0, 0XF3, 0XEC, 0XEF, 0XF3, 0XEC,
    0XEE, 0XF2, 0XED, 0XEE, 0XF2, 0XEE, 0XEE, 0XF3, 0XEF, 0XEE, 0XF3, 0XEF, 0XEE, 0XF2, 0XEF, 0XEE,
    0XF2, 0XF0, 0XEF, 0XF3, 0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XED, 0XEC, 0XF0, 0XEB, 0XEA, 0XEE,
    0XEA, 0XE9, 0XEE, 0XEA, 0XE9, 0XEB, 0XE8, 0XE7, 0XE9, 0XE7, 0XE6, 0XE7, 0XE4, 0XE3, 0XE6, 0XE4,
    0XE3, 0XE7, 0XE2, 0XE1, 0XE6, 0XDF, 0XDE, 0XE1, 0XDD, 0XDC, 0XDE, 0XD9, 0XD8, 0XDA, 0XD7, 0XD6,
    0XD8, 0XD4, 0XD3, 0XD5, 0XCF, 0XCE, 0XD0, 0XCA, 0XCA, 0XCE, 0XC4, 0XC1, 0XC7, 0XBB, 0XB8, 0XC2,
    0XB0, 0XAF, 0XBC, 0XA9, 0XA8, 0XB7, 0XA6, 0XA2, 0XB1, 0XA3, 0X9E, 0XAD, 0XA0, 0X9E, 0XAE, 0X9D,
    0X9E, 0XB1, 0XA0, 0XA8, 0XC5, 0X86, 0X97, 0XCB, 0X81, 0X9D, 0XD5, 0X89, 0XA6, 0XDE, 0X72, 0X90,
    0XCE, 0X84, 0XA5, 0XE0, 0X80, 0X9E, 0XD5, 0X8C, 0XA9, 0XDD, 0X8D, 0XA6, 0XD9, 0X8E, 0XA9, 0XE0,
    0X7E, 0XA2, 0XDA, 0X90, 0XB7, 0XEB, 0X73, 0X9E, 0XE1, 0X5F, 0X8B, 0XD6, 0X6C, 0X9F, 0XE4, 0X51,
    0X8A, 0XD3, 0X54, 0X90, 0XE7, 0X32, 0X6D, 0XCE, 0X77, 0X9F, 0XEE, 0X95, 0XB0, 0XF2, 0X90, 0XB0,
    0XF0, 0X88, 0XAA, 0XEE, 0X9D, 0XB4, 0XEF, 0XA6, 0XC2, 0XF5, 0X9D, 0XBB, 0XED, 0X9E, 0XBC, 0XF4,
    0X8E, 0XAD, 0XE6, 0X91, 0XB1, 0XE7, 0X9E, 0XBB, 0XF3, 0X93, 0XAF, 0XE6, 0X81, 0X91, 0XE3, 0X97,
    0XA4, 0XF2, 0XA9, 0XAE, 0XFE, 0X75, 0X64, 0XF3, 0X6E, 0X54, 0XF9, 0X71, 0X57, 0XFA, 0X6D, 0X51,
    0XFA, 0X6A, 0X4C, 0XFD, 0X6C, 0X51, 0XF8, 0X70, 0X52, 0XF1, 0X80, 0X66, 0XE4, 0XCF, 0XC7, 0XF5,
    0XF2, 0XF4, 0XFC, 0XF0, 0XF0, 0XF7, 0XF1, 0XF0, 0XF7, 0XF1, 0XEF, 0XF9, 0XF1, 0XF0, 0XFA, 0XF0,
    0XEF, 0XF8, 0XF0, 0XEF, 0XF8, 0XEF, 0XEE, 0XF7, 0XF0, 0XEF, 0XF7, 0XED, 0XEC, 0XF5, 0XEE, 0XED,
    0XF5, 0XF1, 0XEF, 0XF5, 0XF0, 0XEE, 0XF4, 0XED, 0XEB, 0XF1, 0XEC, 0XEA, 0XF0, 0XEE, 0XEC, 0XF1,
    0XED, 0XEB, 0XF0, 0XEC, 0XEC, 0XEF, 0XEB, 0XEA, 0XEE, 0XED, 0XEC, 0XF0, 0XEB, 0XEA, 0XEE, 0XEA,
    0XE9, 0XED, 0XEA, 0XE9, 0XED, 0XE8, 0XE7, 0XEB, 0XE5, 0XE4, 0XE8, 0XE4, 0XE2, 0XE6, 0XE5, 0XE2,
    0XE4, 0XE4, 0XE1, 0XE3, 0XE2, 0XDF, 0XE2, 0XE1, 0XDD, 0XE2, 0XDF, 0XDA, 0XDF, 0XDE, 0XD8, 0XDD,
    0XDC, 0XD6, 0XDC, 0XDA, 0XD5, 0XD8, 0XD9, 0XD2, 0XD5, 0XD6, 0XCE, 0XD1, 0XD2, 0XCB, 0XCE, 0XCB,
    0XC5, 0XC8, 0XC7, 0XC0, 0XC2, 0XC6, 0XBA, 0XBD, 0XCA, 0XB9, 0XBD, 0XC1, 0XA5, 0XAA, 0XAB, 0X7A,
    0X82, 0XA2, 0X5D, 0X68, 0XA3, 0X54, 0X61, 0XA2, 0X52, 0X5F, 0XA5, 0X4F, 0X5D, 0XA8, 0X4B, 0X5A,
    0XAC, 0X4E, 0X5E, 0XAC, 0X49, 0X5B, 0XA5, 0X3A, 0X4D, 0X94, 0X26, 0X39, 0X93, 0X28, 0X37, 0XAE,
    0X4B, 0X54, 0XC8, 0X6B, 0X6F, 0XC5, 0X6A, 0X69, 0XC5, 0X68, 0X63, 0XBB, 0X54, 0X4A, 0XA2, 0X30,
    0X22, 0X9F, 0X27, 0X18, 0XA5, 0X2A, 0X1B, 0XA3, 0X27, 0X16, 0XA2, 0X26, 0X13, 0XA1, 0X2B, 0X16,
    0XF8, 0XF6, 0XF6, 0XF7, 0XF5, 0XF5, 0XF5, 0XF3, 0XF3, 0XF7, 0XF5, 0XF5, 0XF6, 0XF5, 0XF5, 0XF4,
    0XF4, 0XF4, 0XF4, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF5, 0XF2,
    0XF2, 0XF5, 0XF3, 0XF3, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1,
    0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF2, 0XF0, 0XF0, 0XF1, 0XF0, 0XF0, 0XF1,
    0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XEF, 0XED, 0XED, 0XEE, 0XEC, 0XEC, 0XEE, 0XEC,
    0XEC, 0XED, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8, 0XE9, 0XEA, 0XE7, 0XE9, 0XE9, 0XE6, 0XE7,
    0XE9, 0XE7, 0XE7, 0XE6, 0XE4, 0XE4, 0XE4, 0XE3, 0XE4, 0XE4, 0XE2, 0XE3, 0XE3, 0XE1, 0XE1, 0XE4,
    0XE1, 0XDD, 0XE3, 0XE0, 0XDC, 0XE0, 0XDD, 0XD9, 0XE0, 0XDD, 0XD9, 0XDD, 0XDA, 0XD5, 0XDA, 0XD7,
    0XD3, 0XD8, 0XD4, 0XCF, 0XD6, 0XD2, 0XCD, 0XD3, 0XCE, 0XC9, 0XD1, 0XCB, 0XC5, 0XCE, 0XC8, 0XC1,
    0XCB, 0XC6, 0XBE, 0XC3, 0XC1, 0XB8, 0XBE, 0XBB, 0XB0, 0XBB, 0XB7, 0XA6, 0XB5, 0XAF, 0X9E, 0XAE,
    0XA9, 0X97, 0XA2, 0X9E, 0X8B, 0X9F, 0X9A, 0X83, 0X9B, 0X95, 0X7A, 0X93, 0X90, 0X6E, 0X8F, 0X89,
    0X6A, 0X8C, 0X87, 0X67, 0X89, 0X87, 0X60, 0X7D, 0X7E, 0X45, 0X6C, 0X72, 0X20, 0X65, 0X6D, 0X06,
    0X6A, 0X71, 0X07, 0X65, 0X6C, 0X01, 0X6B, 0X74, 0X01, 0X6D, 0X74, 0X01, 0X6B, 0X71, 0X03, 0X69,
    0X70, 0X01, 0X67, 0X6F, 0X03, 0X56, 0X5B, 0X00, 0X50, 0X55, 0X00, 0X62, 0X6E, 0X05, 0X62, 0X76,
    0X02, 0X57, 0X70, 0X00, 0X5D, 0X77, 0X02, 0X64, 0X80, 0X05, 0X65, 0X84, 0X01, 0X67, 0X87, 0X00,
    0X68, 0X88, 0X00, 0X6B, 0X8A, 0X00, 0X6E, 0X8B, 0X00, 0X6F, 0X8B, 0X00, 0X6E, 0X8B, 0X00, 0X6E,
    0X8E, 0X01, 0X6F, 0X8F, 0X03, 0X6F, 0X8F, 0X03, 0X6F, 0X8F, 0X02, 0X6E, 0X8F, 0X00, 0X6D, 0X8E,
    0X00, 0X71, 0X91, 0X02, 0X72, 0X92, 0X02, 0X71, 0X92, 0X01, 0X6E, 0X93, 0X00, 0X6E, 0X94, 0X01,
    0X72, 0X97, 0X00, 0X7B, 0X99, 0X03, 0X93, 0XB5, 0X07, 0X8E, 0XAE, 0X22, 0XC3, 0XD9, 0XA3, 0XA4,
    0XC0, 0X9A, 0XA3, 0XC0, 0X95, 0X99, 0XC1, 0X87, 0X8A, 0XB4, 0X7D, 0X89, 0XB3, 0X7E, 0X93, 0XBA,
    0X93, 0X9C, 0XBE, 0XC2, 0X90, 0XB2, 0XDA, 0X9A, 0XB9, 0XDD, 0XB1, 0XC5, 0XD8, 0XE1, 0XE9, 0XEE,
    0XF1, 0XF0, 0XEE, 0XEF, 0XED, 0XED, 0XED, 0XEF, 0XF0, 0XEB, 0XED, 0XEE, 0XEF, 0XEE, 0XEE, 0XEF,
    0XED, 0XED, 0XEC, 0XEA, 0XEA, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XE9, 0XE7,
    0XE7, 0XE9, 0XE6, 0XE6, 0XE6, 0XE6, 0XE6, 0XE4, 0XE4, 0XE4, 0XE2, 0XE2, 0XE2, 0XDF, 0XDF, 0XDF,
    0XDD, 0XDD, 0XDD, 0XDB, 0XDB, 0XDB, 0XD7, 0XD7, 0XD7, 0XD2, 0XD2, 0XD2, 0XD3, 0XD0, 0XD0, 0XCD,
    0XCA, 0XCA, 0XCA, 0XC8, 0XC8, 0XC4, 0XC3, 0XC3, 0XBC, 0XBC, 0XBC, 0XB9, 0XB9, 0XB9, 0XB6, 0XB6,
    0XB6, 0XBA, 0XB7, 0XBB, 0XBB, 0XB7, 0XB9, 0XB5, 0XB6, 0XB8, 0XB0, 0XB3, 0XBB, 0XAE, 0XAE, 0XB7,
    0XAE, 0XB0, 0XBB, 0X8F, 0XA5, 0XC0, 0X77, 0X9A, 0XC0, 0X88, 0XA9, 0XD6, 0X4D, 0X7B, 0XBE, 0X5C,
    0X8D, 0XC6, 0X7F, 0XA5, 0XD2, 0X8C, 0XAE, 0XDE, 0X8C, 0XB5, 0XE0, 0X9E, 0XC2, 0XE8, 0X96, 0XB9,
    0XE4, 0X92, 0XB8, 0XE9, 0X9A, 0XBF, 0XE9, 0X76, 0XAA, 0XDE, 0X7C, 0XAC, 0XE2, 0X86, 0XB1, 0XDF,
    0XBC, 0XD7, 0XF4, 0XAE, 0XC9, 0XF2, 0XB0, 0XCC, 0XF0, 0XBC, 0XD9, 0XF3, 0XA5, 0XCA, 0XF2, 0XB5,
    0XCE, 0XF1, 0XB2, 0XCE, 0XF0, 0X99, 0XC3, 0XEE, 0XAF, 0XD2, 0XF7, 0XBD, 0XD6, 0XF6, 0XB9, 0XD3,
    0XF7, 0XB8, 0XD3, 0XF8, 0XC0, 0XD6, 0XF3, 0XE0, 0XEA, 0XF7, 0XF4, 0XF4, 0XF5, 0XF1, 0XF1, 0XF4,
    0XEE, 0XF1, 0XF8, 0XEE, 0XF0, 0XF5, 0XEC, 0XEF, 0XF3, 0XEC, 0XEF, 0XF3, 0XED, 0XF0, 0XF4, 0XED,
    0XEF, 0XF3, 0XED, 0XEE, 0XF3, 0XED, 0XED, 0XF4, 0XEF, 0XEE, 0XF3, 0XEE, 0XED, 0XF1, 0XEF, 0XEE,
    0XF3, 0XEE, 0XED, 0XF1, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XEF, 0XED, 0XEC, 0XF0, 0XEC, 0XEB, 0XEF,
    0XEB, 0XEA, 0XED, 0XE9, 0XE8, 0XEA, 0XE8, 0XE7, 0XE8, 0XE6, 0XE5, 0XE7, 0XE5, 0XE4, 0XE7, 0XE3,
    0XE2, 0XE6, 0XE1, 0XDF, 0XE5, 0XDF, 0XDD, 0XE2, 0XDD, 0XDC, 0XE0, 0XD8, 0XD7, 0XDA, 0XD4, 0XD3,
    0XD6, 0XD3, 0XD2, 0XD6, 0XCE, 0XCC, 0XD1, 0XC9, 0XC7, 0XCC, 0XC1, 0XBE, 0XC4, 0XB7, 0XB4, 0XBD,
    0XAD, 0XAC, 0XB9, 0XA8, 0XA7, 0XB6, 0XA5, 0XA0, 0XB0, 0XA2, 0X9C, 0XAC, 0XA0, 0X9C, 0XAE, 0X9C,
    0X9D, 0XB1, 0X9F, 0XAA, 0XC8, 0X95, 0XA5, 0XDB, 0X86, 0XA2, 0XDB, 0X70, 0X8F, 0XC9, 0X76, 0X93,
    0XD0, 0X71, 0X94, 0XCE, 0X7A, 0X9A, 0XD3, 0X97, 0XB0, 0XE2, 0X8E, 0XAD, 0XE3, 0X7D, 0XA0, 0XD5,
    0X9B, 0XBC, 0XEF, 0X92, 0XB5, 0XEC, 0X69, 0X92, 0XD6, 0X84, 0XA8, 0XE7, 0X7D, 0XA5, 0XE7, 0X55,
    0X88, 0XD9, 0X59, 0X91, 0XE3, 0X5B, 0X90, 0XE4, 0X91, 0XB6, 0XF6, 0XA1, 0XC0, 0XF4, 0X91, 0XAE,
    0XEB, 0X92, 0XAE, 0XF0, 0XAA, 0XC2, 0XF6, 0X92, 0XAB, 0XE1, 0XA1, 0XBE, 0XF0, 0X98, 0XB6, 0XEC,
    0X93, 0XB3, 0XE6, 0X9D, 0XBE, 0XEF, 0X98, 0XB1, 0XEE, 0X95, 0XAC, 0XE8, 0X99, 0XAF, 0XEA, 0X9F,
    0XB2, 0XF0, 0X8E, 0X94, 0XF2, 0X6B, 0X5F, 0XE9, 0X73, 0X60, 0XF8, 0X6A, 0X55, 0XF8, 0X62, 0X4F,
    0XF6, 0X66, 0X55, 0XF3, 0X73, 0X67, 0XF3, 0X84, 0X78, 0XEA, 0XC6, 0XC1, 0XF7, 0XF5, 0XF5, 0XFA,
    0XF1, 0XEF, 0XF5, 0XF1, 0XEE, 0XF9, 0XF0, 0XF0, 0XF9, 0XEF, 0XEF, 0XF8, 0XF0, 0XEF, 0XF9, 0XF0,
    0XEF, 0XF9, 0XF0, 0XEF, 0XF8, 0XEE, 0XED, 0XF6, 0XEE, 0XED, 0XF6, 0XEE, 0XED, 0XF6, 0XED, 0XEC,
    0XF5, 0XF0, 0XEE, 0XF4, 0XED, 0XEB, 0XF1, 0XED, 0XEB, 0XF1, 0XEE, 0XEC, 0XF2, 0XEB, 0XEA, 0XEF,
    0XEC, 0XEB, 0XEF, 0XEB, 0XEA, 0XEE, 0XEC, 0XEB, 0XEE, 0XEB, 0XEB, 0XEF, 0XE9, 0XE8, 0XEC, 0XE8,
    0XE7, 0XEB, 0XE9, 0XE8, 0XEC, 0XE7, 0XE6, 0XEA, 0XE3, 0XE2, 0XE6, 0XE1, 0XE0, 0XE4, 0XE4, 0XE0,
    0XE5, 0XE2, 0XDE, 0XE3, 0XDF, 0XDC, 0XE1, 0XDF, 0XDA, 0XDF, 0XDD, 0XD7, 0XDD, 0XDB, 0XD4, 0XDB,
    0XD9, 0XD2, 0XD9, 0XD6, 0XCF, 0XD4, 0XD3, 0XCC, 0XCF, 0XD1, 0XCA, 0XCD, 0XCA, 0XC4, 0XC7, 0XC6,
    0XBE, 0XC1, 0XC8, 0XB9, 0XBE, 0XCC, 0XB1, 0XB7, 0XB9, 0X93, 0X9B, 0XA4, 0X6C, 0X75, 0X9E, 0X59,
    0X63, 0XA6, 0X55, 0X62, 0XA6, 0X50, 0X5E, 0XA6, 0X4F, 0X5D, 0XA6, 0X4D, 0X5C, 0XAB, 0X4D, 0X5D,
    0XAE, 0X46, 0X57, 0X9F, 0X31, 0X43, 0X91, 0X24, 0X33, 0X9F, 0X34, 0X40, 0XBF, 0X5A, 0X61, 0XCB,
    0X6C, 0X6E, 0XC5, 0X6A, 0X68, 0XC7, 0X66, 0X62, 0XB6, 0X49, 0X3F, 0XA0, 0X2B, 0X1B, 0XA5, 0X28,
    0X16, 0XA8, 0X2A, 0X1A, 0XA2, 0X28, 0X18, 0XA2, 0X28, 0X19, 0XA4, 0X27, 0X16, 0XA6, 0X2E, 0X1C,
    0XF6, 0XF4, 0XF4, 0XF7, 0XF5, 0XF5, 0XF5, 0XF3, 0XF3, 0XF6, 0XF3, 0XF3, 0XF5, 0XF4, 0XF4, 0XF4,
    0XF4, 0XF4, 0XF5, 0XF5, 0XF5, 0XF6, 0XF4, 0XF4, 0XF5, 0XF4, 0XF4, 0XF6, 0XF4, 0XF4, 0XF5, 0XF4,
    0XF4, 0XF5, 0XF4, 0XF4, 0XF5, 0XF4, 0XF4, 0XF4, 0XF2, 0XF2, 0XF4, 0XF2, 0XF2, 0XF2, 0XF0, 0XF0,
    0XF3, 0XF1, 0XF1, 0XF3, 0XF1, 0XF1, 0XF2, 0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XF1,
    0XEF, 0XEF, 0XF1, 0XEF, 0XEF, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEF, 0XED, 0XED, 0XEE, 0XEC,
    0XEC, 0XED, 0XEB, 0XEB, 0XED, 0XEB, 0XEB, 0XEC, 0XE9, 0XEA, 0XEA, 0XE7, 0XE9, 0XE9, 0XE6, 0XE8,
    0XE9, 0XE7, 0XE7, 0XE8, 0XE6, 0XE6, 0XE6, 0XE4, 0XE5, 0XE4, 0XE3, 0XE3, 0XE5, 0XE3, 0XE1, 0XE5,
    0XE2, 0XDF, 0XE3, 0XE0, 0XDD, 0XE1, 0XDF, 0XDB, 0XE1, 0XDE, 0XDA, 0XDE, 0XDB, 0XD7, 0XDC, 0XD9,
    0XD3, 0XDA, 0XD7, 0XD2, 0XD9, 0XD5, 0XD0, 0XD5, 0XD2, 0XCD, 0XD4, 0XCF, 0XC9, 0XD0, 0XCB, 0XC3,
    0XCC, 0XC8, 0XBF, 0XC7, 0XC4, 0XBB, 0XC4, 0XC2, 0XB7, 0XBE, 0XBA, 0XAD, 0XB9, 0XB5, 0XA6, 0XAF,
    0XAD, 0X9D, 0XAB, 0XA7, 0X95, 0XA7, 0XA2, 0X8D, 0X9F, 0X9A, 0X81, 0X99, 0X95, 0X79, 0X91, 0X8C,
    0X6F, 0X8E, 0X8A, 0X68, 0X89, 0X87, 0X62, 0X84, 0X82, 0X59, 0X81, 0X81, 0X45, 0X69, 0X6F, 0X18,
    0X6A, 0X6F, 0X0E, 0X6B, 0X73, 0X06, 0X69, 0X72, 0X00, 0X6A, 0X70, 0X02, 0X69, 0X70, 0X01, 0X69,
    0X71, 0X00, 0X69, 0X71, 0X00, 0X63, 0X6A, 0X01, 0X51, 0X56, 0X02, 0X4F, 0X58, 0X00, 0X61, 0X71,
    0X04, 0X5D, 0X73, 0X01, 0X59, 0X72, 0X00, 0X5F, 0X7A, 0X01, 0X63, 0X80, 0X01, 0X67, 0X87, 0X01,
    0X67, 0X88, 0X00, 0X6A, 0X88, 0X00, 0X6C, 0X8A, 0X00, 0X6E, 0X8C, 0X01, 0X6C, 0X8A, 0X00, 0X6B,
    0X8A, 0X00, 0X6D, 0X8C, 0X00, 0X6F, 0X8F, 0X02, 0X6E, 0X8D, 0X00, 0X6E, 0X8E, 0X00, 0X6D, 0X8D,
    0X00, 0X6E, 0X8F, 0X00, 0X6E, 0X8F, 0X01, 0X6E, 0X8F, 0X01, 0X6B, 0X8F, 0X00, 0X6C, 0X90, 0X02,
    0X6F, 0X94, 0X01, 0X75, 0X95, 0X04, 0X8B, 0XAD, 0X03, 0XA0, 0XBE, 0X36, 0XCF, 0XDD, 0XC8, 0XAE,
    0XC2, 0XC6, 0XAB, 0XC3, 0XBB, 0XB8, 0XD5, 0XD4, 0XAB, 0XCB, 0XDA, 0XAB, 0XCC, 0XDE, 0XAB, 0XCA,
    0XE4, 0XAB, 0XCA, 0XE9, 0X9B, 0XBD, 0XDA, 0X96, 0XB7, 0XDB, 0XA5, 0XC0, 0XDB, 0XCB, 0XD8, 0XE3,
    0XF0, 0XF1, 0XF1, 0XED, 0XEE, 0XEC, 0XEE, 0XEE, 0XEE, 0XEE, 0XEE, 0XEF, 0XEC, 0XED, 0XEE, 0XEF,
    0XEE, 0XEE, 0XED, 0XEC, 0XEC, 0XEB, 0XEA, 0XEA, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEA, 0XE8,
    0XE8, 0XE9, 0XE7, 0XE7, 0XE5, 0XE5, 0XE5, 0XE4, 0XE4, 0XE4, 0XE1, 0XE1, 0XE1, 0XDF, 0XDF, 0XDF,
    0XDE, 0XDE, 0XDE, 0XDA, 0XDA, 0XDA, 0XD7, 0XD7, 0XD7, 0XD5, 0XD5, 0XD5, 0XD3, 0XD2, 0XD2, 0XD0,
    0XCE, 0XCE, 0XCA, 0XC8, 0XC8, 0XC3, 0XC2, 0XC3, 0XBE, 0XBE, 0XBF, 0XBC, 0XBC, 0XBC, 0XB5, 0XB6,
    0XB6, 0XB9, 0XB6, 0XB8, 0XBD, 0XB9, 0XBB, 0XB4, 0XB4, 0XB9, 0XAE, 0XB1, 0XBB, 0XB0, 0XB0, 0XB9,
    0XAE, 0XAE, 0XB9, 0X9B, 0XAE, 0XC6, 0X76, 0X99, 0XBD, 0X74, 0X97, 0XC4, 0X55, 0X82, 0XBE, 0X54,
    0X83, 0XBB, 0X7A, 0XA0, 0XD1, 0X87, 0XAE, 0XDE, 0X8B, 0XB3, 0XDC, 0XA2, 0XC4, 0XE8, 0X92, 0XB9,
    0XE6, 0X8C, 0XB6, 0XE8, 0X95, 0XBD, 0XE9, 0X68, 0X9D, 0XD5, 0X82, 0XB0, 0XE5, 0X82, 0XAB, 0XDB,
    0XB2, 0XCE, 0XF0, 0XAF, 0XC9, 0XF1, 0XB4, 0XCF, 0XF0, 0XC1, 0XDC, 0XF5, 0XAC, 0XCA, 0XF2, 0XBB,
    0XD1, 0XF1, 0XBA, 0XD5, 0XF7, 0X99, 0XC3, 0XEE, 0XA9, 0XCC, 0XF3, 0XBB, 0XD4, 0XF4, 0XBA, 0XD5,
    0XF9, 0XB3, 0XCE, 0XF4, 0XC4, 0XD8, 0XF2, 0XE7, 0XED, 0XF9, 0XF0, 0XF2, 0XF4, 0XEE, 0XF0, 0XF3,
    0XEE, 0XF1, 0XF6, 0XEF, 0XF0, 0XF4, 0XEC, 0XEF, 0XF2, 0XEB, 0XEE, 0XF2, 0XEB, 0XEE, 0XF2, 0XEB,
    0XED, 0XF1, 0XED, 0XEE, 0XF2, 0XEF, 0XEE, 0XF3, 0XEE, 0XED, 0XF1, 0XEE, 0XED, 0XF1, 0XED, 0XEC,
    0XEF, 0XED, 0XEC, 0XF0, 0XEE, 0XED, 0XF1, 0XEC, 0XEB, 0XEF, 0XEB, 0XEA, 0XEE, 0XEA, 0XE9, 0XED,
    0XE9, 0XE8, 0XEC, 0XE8, 0XE7, 0XE9, 0XE7, 0XE6, 0XE8, 0XE6, 0XE5, 0XE7, 0XE5, 0XE4, 0XE7, 0XE2,
    0XE0, 0XE5, 0XE0, 0XDE, 0XE4, 0XDF, 0XDD, 0XE2, 0XDC, 0XDB, 0XDF, 0XD6, 0XD5, 0XD9, 0XD3, 0XD2,
    0XD5, 0XD1, 0XD0, 0XD4, 0XCB, 0XCA, 0XD0, 0XC5, 0XC3, 0XCB, 0XBD, 0XBB, 0XC3, 0XB6, 0XB4, 0XBD,
    0XAB, 0XAA, 0XB7, 0XA3, 0XA4, 0XB5, 0XA1, 0X9F, 0XB1, 0XA2, 0X9C, 0XAB, 0XA1, 0X9D, 0XAF, 0X9A,
    0X9E, 0XB7, 0X9C, 0XAC, 0XD0, 0X93, 0XA4, 0XDA, 0X8B, 0XA4, 0XDE, 0X6D, 0X8D, 0XCB, 0X87, 0XA2,
    0XDC, 0X70, 0X93, 0XCC, 0X7F, 0XA2, 0XDB, 0X9C, 0XB4, 0XE6, 0X91, 0XAF, 0XE4, 0X7F, 0XA7, 0XDA,
    0X9D, 0XBB, 0XE6, 0X99, 0XBA, 0XF3, 0X57, 0X82, 0XC8, 0X7F, 0XA4, 0XDF, 0X7B, 0X9F, 0XE3, 0X72,
    0X9F, 0XEA, 0X78, 0XA4, 0XEA, 0X8B, 0XAE, 0XEE, 0XA6, 0XBF, 0XEE, 0X9D, 0XBF, 0XEC, 0X8C, 0XAB,
    0XE5, 0XA0, 0XBB, 0XF4, 0X94, 0XAD, 0XE1, 0X9E, 0XB7, 0XED, 0XA3, 0XC0, 0XF2, 0X95, 0XB3, 0XE7,
    0X99, 0XB7, 0XE8, 0XA0, 0XBC, 0XED, 0X98, 0XAE, 0XE9, 0X99, 0XAF, 0XEC, 0X9E, 0XB8, 0XED, 0X95,
    0XA9, 0XF1, 0X7E, 0X84, 0XEC, 0X86, 0X82, 0XF8, 0X75, 0X6C, 0XF5, 0X65, 0X5C, 0XF3, 0X71, 0X71,
    0XF4, 0X7D, 0X84, 0XF0, 0X76, 0X7B, 0XDE, 0XAD, 0XB2, 0XEB, 0XEE, 0XF5, 0XFC, 0XF1, 0XF2, 0XF3,
    0XF3, 0XF0, 0XF8, 0XEF, 0XEE, 0XF9, 0XED, 0XED, 0XF9, 0XF0, 0XEF, 0XFA, 0XF0, 0XEF, 0XF8, 0XEF,
    0XEF, 0XF8, 0XEF, 0XEE, 0XF7, 0XEF, 0XED, 0XF6, 0XEF, 0XEE, 0XF6, 0XEE, 0XED, 0XF5, 0XED, 0XEC,
    0XF3, 0XEF, 0XED, 0XF2, 0XED, 0XEB, 0XF1, 0XEC, 0XEB, 0XF0, 0XEC, 0XEA, 0XF1, 0XEB, 0XE9, 0XEE,
    0XEB, 0XEA, 0XEE, 0XEB, 0XEA, 0XED, 0XEA, 0XE8, 0XEC, 0XEA, 0XE7, 0XEC, 0XE9, 0XE8, 0XEB, 0XE7,
    0XE6, 0XEA, 0XE6, 0XE5, 0XE8, 0XE5, 0XE3, 0XE7, 0XE3, 0XE1, 0XE5, 0XE2, 0XDF, 0XE3, 0XE1, 0XDD,
    0XE2, 0XDE, 0XDC, 0XE0, 0XDB, 0XD9, 0XDE, 0XDC, 0XD6, 0XDC, 0XDB, 0XD2, 0XD8, 0XD9, 0XD0, 0XD7,
    0XD5, 0XCE, 0XD5, 0XCF, 0XCA, 0XCD, 0XCD, 0XC6, 0XC9, 0XC8, 0XC0, 0XC4, 0XC5, 0XBC, 0XC0, 0XC9,
    0XBB, 0XBF, 0XC6, 0XAB, 0XAF, 0XB0, 0X83, 0X8A, 0X9F, 0X61, 0X69, 0XA3, 0X56, 0X61, 0XA2, 0X53,
    0X5F, 0XA3, 0X52, 0X5F, 0XA4, 0X4C, 0X5C, 0XA8, 0X4A, 0X5D, 0XAA, 0X49, 0X5D, 0XA0, 0X3F, 0X50,
    0X90, 0X2A, 0X38, 0X90, 0X26, 0X34, 0XB1, 0X49, 0X54, 0XC8, 0X65, 0X6C, 0XC7, 0X68, 0X69, 0XCD,
    0X6C, 0X68, 0XC9, 0X61, 0X5C, 0XAE, 0X3C, 0X34, 0XA0, 0X26, 0X16, 0XA6, 0X2B, 0X17, 0XA8, 0X29,
    0X16, 0XA7, 0X29, 0X16, 0XA6, 0X2B, 0X1A, 0XA3, 0X2A, 0X1A, 0XA2, 0X28, 0X18, 0XA2, 0X29, 0X1A,
    0XF6, 0XF4, 0XF4, 0XF7, 0XF5, 0XF5, 0XF8, 0XF5, 0XF5, 0XF7, 0XF2, 0XF3, 0XF6, 0XF4, 0XF4, 0XF6,
    0XF6, 0XF6, 0XF4, 0XF3, 0XF3, 0XF4, 0XF4, 0XF4, 0XF5, 0XF4, 0XF4, 0XF5, 0XF4, 0XF4, 0XF4, 0XF4,
    0XF4, 0XF4, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF5, 0XF3, 0XF3, 0XF3, 0XF1, 0XF1,
    0XF2, 0XF0, 0XF0, 0XF4, 0XF2, 0XF2, 0XF3, 0XF1, 0XF1, 0XF1, 0XEF, 0XEF, 0XF2, 0XF0, 0XF0, 0XF2,
    0XF0, 0XF0, 0XF1, 0XEF, 0XEF, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XF0, 0XEE, 0XEE, 0XEE, 0XEC,
    0XEC, 0XEE, 0XEC, 0XEC, 0XED, 0XEB, 0XEB, 0XEC, 0XEA, 0XEA, 0XEB, 0XE9, 0XE9, 0XEB, 0XE9, 0XE8,
    0XEA, 0XE8, 0XE8, 0XEA, 0XE8, 0XE8, 0XE8, 0XE6, 0XE6, 0XE7, 0XE5, 0XE4, 0XE6, 0XE4, 0XE3, 0XE4,
    0XE2, 0XE2, 0XE2, 0XE0, 0XDF, 0XE2, 0XE1, 0XDE, 0XE0, 0XDF, 0XDC, 0XDF, 0XDE, 0XD9, 0XDF, 0XDC,
    0XD6, 0XDD, 0XD9, 0XD4, 0XDA, 0XD6, 0XD1, 0XD8, 0XD4, 0XCF, 0XD5, 0XD1, 0XCB, 0XD1, 0XCF, 0XC6,
    0XCD, 0XCB, 0XC1, 0XCB, 0XCA, 0XBD, 0XC8, 0XC6, 0XB9, 0XC1, 0XBF, 0XB4, 0XBA, 0XB8, 0XAC, 0XB3,
    0XB3, 0XA5, 0XAF, 0XAD, 0X9B, 0XAA, 0XA8, 0X92, 0XA3, 0XA0, 0X89, 0X9F, 0X9B, 0X83, 0X97, 0X94,
    0X76, 0X8F, 0X8D, 0X6C, 0X8E, 0X8B, 0X6A, 0X8B, 0X87, 0X64, 0X88, 0X87, 0X58, 0X7B, 0X7E, 0X40,
    0X69, 0X6E, 0X17, 0X6D, 0X71, 0X0C, 0X68, 0X6E, 0X04, 0X68, 0X71, 0X00, 0X69, 0X72, 0X00, 0X69,
    0X70, 0X01, 0X6A, 0X6E, 0X02, 0X63, 0X6A, 0X01, 0X5B, 0X67, 0X03, 0X4B, 0X54, 0X00, 0X4F, 0X5B,
    0X00, 0X61, 0X71, 0X05, 0X5E, 0X72, 0X00, 0X59, 0X70, 0X00, 0X5F, 0X78, 0X02, 0X61, 0X80, 0X01,
    0X64, 0X84, 0X00, 0X68, 0X86, 0X00, 0X69, 0X87, 0X00, 0X6D, 0X8B, 0X01, 0X6E, 0X8D, 0X03, 0X69,
    0X88, 0X00, 0X6B, 0X89, 0X01, 0X6F, 0X8A, 0X00, 0X6E, 0X8B, 0X00, 0X6D, 0X8A, 0X00, 0X6E, 0X8D,
    0X01, 0X6D, 0X8E, 0X02, 0X6A, 0X8B, 0X00, 0X6B, 0X8D, 0X02, 0X6D, 0X8E, 0X04, 0X6B, 0X8F, 0X00,
    0X6D, 0X93, 0X00, 0X6F, 0X94, 0X00, 0X7F, 0XA2, 0X01, 0X90, 0XAE, 0X1B, 0XBD, 0XCF, 0X9D, 0XB8,
    0XCC, 0XD5, 0XC0, 0XD7, 0XE5, 0XBC, 0XD3, 0XE6, 0XB8, 0XD0, 0XE9, 0XA8, 0XC3, 0XE3, 0X9C, 0XBC,
    0XE0, 0XA4, 0XC3, 0XE7, 0XA9, 0XC4, 0XEA, 0X9C, 0XB8, 0XE2, 0XA9, 0XC6, 0XEB, 0XB4, 0XC8, 0XE0,
    0XDE, 0XE4, 0XEE, 0XF0, 0XF1, 0XF0, 0XF1, 0XEF, 0XEA, 0XEF, 0XEE, 0XEF, 0XEA, 0XED, 0XF0, 0XEC,
    0XED, 0XED, 0XEC, 0XEC, 0XEC, 0XEB, 0XEB, 0XEB, 0XE9, 0XE9, 0XE9, 0XE9, 0XE9, 0XE9, 0XE7, 0XE7,
    0XE7, 0XE7, 0XE7, 0XE7, 0XE6, 0XE6, 0XE6, 0XE4, 0XE4, 0XE4, 0XE1, 0XE1, 0XE1, 0XDF, 0XDF, 0XDF,
    0XDF, 0XDF, 0XDF, 0XDC, 0XDC, 0XDC, 0XD9, 0XD9, 0XD9, 0XD5, 0XD5, 0XD5, 0XD2, 0XD2, 0XD1, 0XCD,
    0XCD, 0XCE, 0XC9, 0XC8, 0XCB, 0XC5, 0XC4, 0XC7, 0XBF, 0XBE, 0XC2, 0XBA, 0XBA, 0XBB, 0XB8, 0XB8,
    0XB8, 0XB8, 0XB7, 0XB7, 0XB9, 0XB6, 0XB9, 0XB4, 0XB4, 0XBC, 0XAE, 0XB1, 0XB9, 0XB0, 0XAF, 0XB6,
    0XAD, 0XAD, 0XBA, 0X9B, 0XAC, 0XC1, 0X6E, 0X90, 0XB4, 0X63, 0X8A, 0XBF, 0X56, 0X84, 0XB8, 0X66,
    0X90, 0XC7, 0X70, 0X96, 0XCD, 0X77, 0X9F, 0XD0, 0X98, 0XBC, 0XE5, 0XB4, 0XCE, 0XEF, 0X8E, 0XB9,
    0XEA, 0X74, 0XA5, 0XD8, 0X91, 0XBB, 0XEA, 0X66, 0X98, 0XD7, 0X8C, 0XB4, 0XE8, 0X85, 0XAB, 0XDC,
    0XAF, 0XCE, 0XF6, 0XB1, 0XCD, 0XF0, 0XBC, 0XD4, 0XF0, 0XCC, 0XE1, 0XFC, 0XBD, 0XD0, 0XF5, 0XC0,
    0XD5, 0XF4, 0XB0, 0XCD, 0XF5, 0X96, 0XC0, 0XEE, 0XA7, 0XCB, 0XF1, 0XB7, 0XD0, 0XEE, 0XBB, 0XD6,
    0XF8, 0XB7, 0XD2, 0XF4, 0XCC, 0XDA, 0XEE, 0XEB, 0XEE, 0XF6, 0XEE, 0XF2, 0XF5, 0XEC, 0XF0, 0XF5,
    0XEC, 0XF0, 0XF2, 0XEC, 0XF0, 0XF1, 0XEC, 0XEF, 0XF1, 0XEC, 0XEF, 0XF3, 0XEB, 0XED, 0XF2, 0XEB,
    0XEB, 0XF1, 0XEE, 0XED, 0XF1, 0XF0, 0XEF, 0XF3, 0XEF, 0XEE, 0XF0, 0XEF, 0XEE, 0XEF, 0XEE, 0XED,
    0XEE, 0XED, 0XEC, 0XF0, 0XEC, 0XEC, 0XF0, 0XEA, 0XEB, 0XEF, 0XE7, 0XEA, 0XEE, 0XE8, 0XE8, 0XEC,
    0XE8, 0XE7, 0XEB, 0XE7, 0XE7, 0XEB, 0XE7, 0XE6, 0XEA, 0XE6, 0XE5, 0XE9, 0XE3, 0XE2, 0XE6, 0XE2,
    0XE1, 0XE5, 0XE0, 0XDF, 0XE3, 0XDD, 0XDB, 0XE1, 0XDB, 0XDA, 0XDF, 0XD6, 0XD5, 0XD7, 0XD2, 0XD2,
    0XD2, 0XCF, 0XCE, 0XD0, 0XC9, 0XC8, 0XCF, 0XC1, 0XC0, 0XCB, 0XBA, 0XB8, 0XC4, 0XB2, 0XB2, 0XBC,
    0XA8, 0XA8, 0XB4, 0X9E, 0XA1, 0XB4, 0X9D, 0X9E, 0XB3, 0XA5, 0X9F, 0XAC, 0XA1, 0X9D, 0XAD, 0X99,
    0XA3, 0XC5, 0X90, 0XA6, 0XD3, 0X88, 0X9D, 0XD2, 0X82, 0X98, 0XD2, 0X74, 0X95, 0XD5, 0X84, 0X9D,
    0XD4, 0X80, 0XA0, 0XD6, 0X7F, 0XA1, 0XD4, 0X96, 0XAF, 0XE3, 0X8C, 0XAB, 0XE0, 0X92, 0XB8, 0XEB,
    0X94, 0XB2, 0XDC, 0X7E, 0XA4, 0XE8, 0X53, 0X86, 0XD2, 0X65, 0X93, 0XD5, 0X6C, 0X9A, 0XE2, 0X64,
    0X96, 0XDB, 0X7F, 0XA8, 0XE8, 0X9C, 0XBA, 0XF5, 0XA0, 0XB9, 0XEF, 0X94, 0XB1, 0XE6, 0X9B, 0XBA,
    0XF4, 0X86, 0XA4, 0XE1, 0X96, 0XB2, 0XEC, 0XA7, 0XC2, 0XF3, 0X9A, 0XB7, 0XEB, 0X96, 0XB4, 0XE7,
    0XA0, 0XBB, 0XED, 0XA1, 0XB7, 0XEA, 0X9B, 0XB2, 0XE8, 0X94, 0XAF, 0XE9, 0X9C, 0XB9, 0XF4, 0X89,
    0X9D, 0XE9, 0X8F, 0X9D, 0XEC, 0X87, 0X92, 0XEB, 0X6E, 0X73, 0XF1, 0X67, 0X71, 0XE9, 0X85, 0X9D,
    0XF1, 0X7C, 0X93, 0XD8, 0X99, 0XA7, 0XDB, 0XE2, 0XEA, 0XFB, 0XF2, 0XF3, 0XF8, 0XF1, 0XEF, 0XF8,
    0XEE, 0XEF, 0XFA, 0XEE, 0XF1, 0XF9, 0XF0, 0XEF, 0XF8, 0XEF, 0XED, 0XF7, 0XF0, 0XF0, 0XF8, 0XEE,
    0XED, 0XF6, 0XED, 0XEC, 0XF5, 0XF0, 0XED, 0XF6, 0XEF, 0XED, 0XF2, 0XEF, 0XED, 0XF2, 0XEF, 0XED,
    0XF2, 0XEE, 0XEC, 0XF2, 0XEC, 0XEA, 0XF0, 0XEC, 0XEA, 0XF0, 0XEB, 0XE9, 0XEF, 0XE9, 0XE8, 0XED,
    0XEA, 0XE9, 0XEC, 0XEB, 0XEA, 0XEE, 0XEA, 0XE7, 0XEB, 0XEA, 0XE7, 0XEC, 0XE7, 0XE6, 0XE8, 0XE5,
    0XE4, 0XE6, 0XE3, 0XE2, 0XE4, 0XE3, 0XE0, 0XE2, 0XE1, 0XDE, 0XE0, 0XE2, 0XDD, 0XDF, 0XDD, 0XD7,
    0XDD, 0XD7, 0XD7, 0XDB, 0XD5, 0XD6, 0XDA, 0XD8, 0XD2, 0XD8, 0XDA, 0XCF, 0XD5, 0XD5, 0XCB, 0XD1,
    0XCE, 0XC9, 0XCC, 0XC9, 0XC4, 0XC5, 0XC6, 0XBE, 0XC1, 0XC5, 0XB9, 0XBE, 0XC7, 0XB4, 0XBC, 0XBB,
    0X9C, 0XA4, 0XA5, 0X73, 0X7A, 0XA0, 0X5D, 0X61, 0XA3, 0X56, 0X5C, 0XA6, 0X53, 0X60, 0XA6, 0X51,
    0X5F, 0XA4, 0X4C, 0X5B, 0XA7, 0X47, 0X5C, 0XAA, 0X45, 0X5B, 0X9E, 0X34, 0X48, 0X8F, 0X24, 0X34,
    0X96, 0X32, 0X3C, 0XBC, 0X5A, 0X62, 0XCC, 0X6C, 0X73, 0XC6, 0X69, 0X6C, 0XC6, 0X6A, 0X66, 0XC0,
    0X5B, 0X52, 0XA9, 0X35, 0X28, 0XA3, 0X27, 0X18, 0XA3, 0X2A, 0X19, 0XA1, 0X28, 0X16, 0XA7, 0X2A,
    0X18, 0XA5, 0X29, 0X17, 0XA2, 0X28, 0X16, 0XA5, 0X2E, 0X1B, 0XA1, 0X2B, 0X1A, 0X9F, 0X29, 0X19,
};



