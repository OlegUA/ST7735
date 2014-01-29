#include "main.h"
#include "hw_config.h"
#include "ST7735.h"

#include <stdio.h>

#include "tux_50_ad.h"

__IO uint32_t UserButtonPressed = 0;

/* Private function prototypes -----------------------------------------------*/
void test_ascii_screen(void);
void test_graphics(void);

int main(void) {

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI); 
    STM_EVAL_LEDOff(LED3);
	
	lcd7735_setup();
	delay_ms(50);
	lcd7735_initR(INITR_REDTAB);
	lcd7735_setFont((uint8_t *)&SmallFont[0]);
	lcd7735_fillScreen(ST7735_BLACK);
	lcd7735_print("Press button!",0,60,0);
	while(1) {
		if( UserButtonPressed == 0x01 ) {
			STM_EVAL_LEDToggle(LED3);
			test_graphics();
		} else if( UserButtonPressed == 0x02 ) {
			STM_EVAL_LEDToggle(LED3);
			test_ascii_screen();
		}
	}
}

void test_ascii_screen(void) {
	unsigned char x;
	int i;

	lcd7735_init_screen((void *)&SmallFont[0],ST7735_GREEN,ST7735_BLACK,PORTRAIT);
	printf("zz=%03.4f\n",34.678); 
	while(1) {
		x = 0x20;
		for(i=0;i<95;i++) {
			lcd7735_putc(x+i);
			delay_ms(50);
		}
		if( UserButtonPressed == 0x01 ) 
			return;
	}
}	

void test_graphics(void) {
	unsigned char y;
	unsigned char x;
	uint8_t r = 0;
//	uint8_t m[16];
	
//	receive_data(0x0B,m,2);
//	delay_ms(2000);
	lcd7735_fillScreen(ST7735_BLACK);
	lcd7735_setFont((uint8_t *)&BigFont[0]);
	while(1) {
		lcd7735_print("Hello!",10,10,0);
		delay_ms(1000);
		lcd7735_print("Hello!",10,10,30);
		delay_ms(1000);
        lcd7735_drawBitmap(0,0,50,52,(bitmapdatatype)tux_50_ad,1);
		delay_ms(1000);
        lcd7735_drawBitmap(0,0,50,52,(bitmapdatatype)tux_50_ad,2);
		delay_ms(1000);
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
		delay_ms(1000);
		lcd7735_invertDisplay(INVERT_ON);
		delay_ms(1000);
		lcd7735_invertDisplay(INVERT_OFF);
		delay_ms(1000);
		lcd7735_fillScreen(ST7735_RED);
		delay_ms(1000);
		lcd7735_fillScreen(ST7735_GREEN);
		delay_ms(1000);
		lcd7735_fillScreen(ST7735_BLUE);
		delay_ms(1000);
		lcd7735_fillScreen(ST7735_BLACK);
		delay_ms(1000);
		lcd7735_drawFastLine(10,5,110,100,ST7735_WHITE);
		delay_ms(1000);
		lcd7735_drawCircle(60,60,50,ST7735_CYAN);
		delay_ms(1000);
		lcd7735_drawRect(10,20,90,100,ST7735_MAGENTA);
		delay_ms(1000);
		lcd7735_fillCircle(70,70,50,ST7735_YELLOW);
		delay_ms(1000);
		lcd7735_fillRect(20,15,90,75,ST7735_BLUE);
		delay_ms(1000);

		r = (r+1) & 0x03;
		lcd7735_setRotation(r);
		delay_ms(1000);
		if( UserButtonPressed == 0x02 )
			return;
	}
}

