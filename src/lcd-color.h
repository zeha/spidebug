#ifndef LCD_COLOR_H
#define LCD_COLOR_H

typedef uint32_t lcd_color_t;
void lcd_init(void);
void lcd_demo_loop(void);

void lcd_show_color_string_4x6(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, unsigned int length, const char* p);
void lcd_show_color_string_5x8(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, unsigned int length, const char* p);
void lcd_show_color_string_5x7(unsigned int x, unsigned int y, lcd_color_t foreground, lcd_color_t background, unsigned int length, const char* p);

#define COLOR_BLACK                        0x000000
#define COLOR_WHITE                        0xffffff
#define COLOR_RED                          0xff0000
#define COLOR_GREEN                        0x00ff00
#define COLOR_BLUE                         0x0000ff

#endif
