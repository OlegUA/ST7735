#include "main.h"
#include "hw_config.h"
#include "Adafruit_ST7735.h"

#include "tux_50_ad.h"

/* Private function prototypes -----------------------------------------------*/


int main(void) {
	unsigned char y;
	unsigned char x;
	uint8_t r = 0;
	uint8_t m[16];
	
	lcd7735_setup();
	delay_ms(50);
	lcd7735_initR(INITR_REDTAB);
//	receive_data(0x0B,m,2);
//	delay_ms(2000);
	lcd7735_fillScreen(ST7735_BLACK);
	delay_ms(2000);
	lcd7735_setFont((uint8_t *)&BigFont[0]);
	while(1) {
		lcd7735_print("Hello!",10,10,0);
		delay_ms(2000);
		lcd7735_print("Hello!",10,10,30);
		delay_ms(2000);
        lcd7735_drawBitmap(0,0,50,52,(bitmapdatatype)tux_50_ad,1);
		delay_ms(2000);
		for (y=0;y<160;y++) {
			for (x=0;x<128;x++) {
				unsigned int color=0x0;
				if (y<30) color=ST7735_BLUE;
				else {
					if (y<60) color=ST7735_GREEN;
					else { 
						if (y<90) color=ST7735_RED; 
					}
				}
				lcd7735_drawPixel(x, y, color);
				//test_dp(x,y,ccolor);
			}
		}
		delay_ms(2000);
		lcd7735_invertDisplay(INVERT_ON);
		delay_ms(2000);
		lcd7735_invertDisplay(INVERT_OFF);
		delay_ms(2000);
		lcd7735_fillScreen(ST7735_RED);
		delay_ms(2000);
		lcd7735_fillScreen(ST7735_GREEN);
		delay_ms(2000);
		lcd7735_fillScreen(ST7735_BLUE);
		delay_ms(2000);
		lcd7735_fillScreen(ST7735_BLACK);
		delay_ms(2000);
		lcd7735_drawFastLine(10,5,110,100,ST7735_WHITE);
		delay_ms(2000);
		lcd7735_drawCircle(60,60,50,ST7735_CYAN);
		delay_ms(2000);
		lcd7735_drawRect(10,20,90,100,ST7735_MAGENTA);
		delay_ms(2000);
		lcd7735_fillCircle(60,60,50,ST7735_YELLOW);
		delay_ms(2000);
		lcd7735_fillRect(20,10,70,90,ST7735_BLUE);
		delay_ms(2000);

		r = (r+1) & 0x03;
		lcd7735_setRotation(r);
		delay_ms(2000);
	}
}

