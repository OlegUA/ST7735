/***************************************************
  Code below has been ported from Arduino Adafruit library.
  Copyrigths below.  

  This is a library for the Adafruit 1.8" SPI display.
  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618
 
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#ifndef _ADAFRUIT_ST7735H_
#define _ADAFRUIT_ST7735H_

#include "stm32f30x.h"
#include "DefaultFonts.h"

// some flags for initR() :(
#define INITR_GREENTAB 0x0
#define INITR_REDTAB   0x1
#define INITR_BLACKTAB   0x2

#define ST7735_TFTWIDTH  128
#define ST7735_TFTHEIGHT 160

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// 5-6-5 bits colors samples 
#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0  
#define ST7735_WHITE   0xFFFF

#define INVERT_ON		1
#define INVERT_OFF		0

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

#define PORTRAIT_NORMAL	0
#define LANDSAPE_NORMAL	1
#define PORTRAIT_FLIP	2
#define LANDSAPE_FLIP	3

#define CENTER	-1
#define RIGHT	-2

#define bitmapdatatype uint16_t *

// Initialization for ST7735B screens
extern void lcd7735_initB(void);
// Initialization for ST7735R screens (green or red tabs)
extern void lcd7735_initR(uint8_t options);
extern uint8_t lcd7735_getWidth(void);
extern uint8_t lcd7735_getHeight(void);

extern void lcd7735_invertDisplay(const uint8_t mode);
extern void lcd7735_setRotation(uint8_t m);
extern void lcd7735_fillScreen(uint16_t color);
// Pass 8-bit (each) R,G,B, get back 16-bit packed color
extern uint16_t lcd7735_Color565(uint8_t r, uint8_t g, uint8_t b);
extern void lcd7735_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
extern void lcd7735_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
extern void lcd7735_drawPixel(int16_t x, int16_t y, uint16_t color);
extern void lcd7735_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
extern void lcd7735_setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
extern void lcd7735_pushColor(uint16_t color); // CAUTION!! can't be used separately
extern void lcd7735_drawFastLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);
extern void lcd7735_drawRect(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2, uint16_t color);
extern void lcd7735_drawCircle(int16_t x, int16_t y, int radius, uint16_t color);
extern void lcd7735_fillCircle(int16_t x, int16_t y, int radius, uint16_t color);
extern void lcd7735_drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale);
extern void lcd7735_drawBitmapRotate(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy);
extern void lcd7735_setFont(uint8_t* font);
extern void lcd7735_setTransparent(uint8_t s);
extern void lcd7735_setForeground(uint16_t s);
extern void lcd7735_setBackground(uint16_t s);
extern void lcd7735_print(char *st, int x, int y, int deg);

#endif
