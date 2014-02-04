#ifndef __VCP_HW_CONFIG__
#define __VCP_HW_CONFIG__

#include "stm32f30x.h"
//
// Hardware SPI if defined
#define LCD_TO_SPI2

// Can't be less 6 MGz according to datasheet on SR7755 controller
#define SPI2_BaudRatePrescaler   SPI_BaudRatePrescaler_2

// CS will be set every time before and and of operation
//#define LCD_SEL_AUTO

#define 	LCD_GPIO			GPIOB

#define     LCD_AHB1_GPIO		RCC_AHBPeriph_GPIOB
//                                                         Pin name fo IDBD02-1.8SP
#define 	LCD_RST_PIN 		GPIO_Pin_14	// PB14 (RST)
#define     LCD_A0_PIN			GPIO_Pin_12	// PB12 (RS)
#define		LCD_CSE_PIN			GPIO_Pin_10	// PB10 (CS)

// For software SPI only
#define		LCD_SDA_PIN			GPIO_Pin_15	// PB15 (SCL)
#define		LCD_SCK_PIN			GPIO_Pin_13	// PB13 (SDA)

// operate GPIO bits via GPIO function call for debug purposes
//#define NO_BITBIND

// The pin LCD_RST_PIN is not used if defined
//#define LCD_SOFT_RESET

/**************************** don't change anythings below *********************************/

#ifdef NO_BITBIND
#define LCD_RST1  GPIO_SetBits(GPIOB, LCD_RST_PIN)
#define LCD_RST0  GPIO_ResetBits(GPIOB, LCD_RST_PIN)

#define LCD_DC1   GPIO_SetBits(GPIOB, LCD_A0_PIN)
#define LCD_DC0   GPIO_ResetBits(GPIOB, LCD_A0_PIN)

#define LCD_CS1   GPIO_SetBits(GPIOB, LCD_CSE_PIN)
#define LCD_CS0   GPIO_ResetBits(GPIOB, LCD_CSE_PIN)

#else

#define LCD_RST1  LCD_GPIO->BSRR = LCD_RST_PIN
#define LCD_RST0  LCD_GPIO->BRR = LCD_RST_PIN

#define LCD_DC1   LCD_GPIO->BSRR = LCD_A0_PIN
#define LCD_DC0   LCD_GPIO->BRR = LCD_A0_PIN

#define LCD_CS1   LCD_GPIO->BSRR = LCD_CSE_PIN
#define LCD_CS0   LCD_GPIO->BRR = LCD_CSE_PIN
#endif


#ifndef LCD_TO_SPI2
#define LCD_SCK1  LCD_GPIO->BSRR = LCD_SCK_PIN
#define LCD_SCK0  LCD_GPIO->BRR = LCD_SCK_PIN

#define LCD_MOSI1 LCD_GPIO->BSRR = LCD_SDA_PIN
#define LCD_MOSI0 LCD_GPIO->BRR = LCD_SDA_PIN
#endif

extern void lcd7735_setup(void);
extern void lcd7735_senddata(const uint8_t cmd);
extern void lcd7735_senddata16(const uint16_t data);
extern void lcd7735_sendCmd(const uint8_t cmd);
extern void lcd7735_sendData(const uint8_t data);

extern void receive_data(const uint8_t cmd, uint8_t *data, uint8_t cnt);

#endif /* __VCP_HW_CONFIG__ */

