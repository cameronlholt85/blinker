// Pin definitions
#define COMMANDS 0x00
#define ONECOMMAND 0x80
#define DATA 0x40
#define ONEDATA 0xC0
#define FLIP_HORIZONTAL 0xA1
#define ALL_WHITE 0xA5
#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE
#define SSD1306_PAGES 4

#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif
#define SSD1306 0X3C
#define DS1307 0x68
