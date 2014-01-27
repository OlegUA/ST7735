#ifndef __HW_CONFIG__
#define __HW_CONFIG__

#include "stm32f30x.h"
//
// Hardware SPI
#define LCD_TO_SPI2

// Can't be less 6 MGz according to datasheet on SR7755 controller
#define SPI2_BaudRatePrescaler   SPI_BaudRatePrescaler_2

// -----------------------------------------------------------------------------------------------------------------
// –”„Ќќ≈ ”ѕ–ј¬Ћ≈Ќ»≈ ¬џЅќ–ќћ ƒ»—ѕЋ≈я
// -----------------------------------------------------------------------------------------------------------------
// если параметр ниже закомментирован то устанавливать линию выбора диспле€ нужно в коде основной программы
// вызовами:
// LCD_CS0; - дл€ выбора диспле€ перед началом проведени€ операций (нескольких) с дисплеем
// LCD_CS1; - дл€ отмены выбора диспле€ (после совершени€ операций)
// если параметр активен - то выбор диспле€ осуществл€етс€ автоматически по мере необходимости
//#define LCD_SEL_AUTO

// ---------------------------------------------------------------------------------------------------------------------------
// ЁЋ≈ “–»„≈— ќ≈ ѕќƒ Ћё„≈Ќ»≈ ƒ»—ѕЋ≈я
// ---------------------------------------------------------------------------------------------------------------------------
// дл€ простоты драйвера при программном SPI все линии управлени€ и данных диспле€ должны быть подключены к одному порту ввода\вывода !
// если же задан режим аппаратного SPI2 то, на один порт должны быть подключены линии RST, A0, CSE
// а остальные линии (SDA, SCK) должны быть подключены к GPIOB (пины 15 и 13 соответственно)
//                             +--------------------+
#define 	LCD_GPIO			GPIOB					// порт к которому подключены пины диспле€
//                             +--------------------+
#define     LCD_AHB1_GPIO		RCC_AHBPeriph_GPIOB	// шина к которой подключен порт
//                             +--------------------+
// пины диспле€ (управление)
//                             +--+
#define 	LCD_RST_PIN 		GPIO_Pin_14
//                             +--+
#define     LCD_A0_PIN			GPIO_Pin_12
//                             +--+
#define		LCD_CSE_PIN			GPIO_Pin_10
//                             +--+
//
// в случае если используетс€ SPI2 подключение то вывод SDA диспле€ должен быть подключен к GPIOB_Pin_15, и SCK к GPIOB_Pin_13
// остальные линии при SPI2 подключении могут быть подключены к любому порту (не только к GPIOB) см. выше
// пины диспле€ (данные)
//                             +--+
#define		LCD_SDA_PIN			GPIO_Pin_15
//                             +--+
#define		LCD_SCK_PIN			GPIO_Pin_13
//                             +--+

// operate GPIO bits via GPIO function call for debug purposes
#define NO_BITBIND

//#define LCD_SOFT_RESET

/**************************** don't change anythings below *********************************/

#ifdef NO_BITBIND
// ?????????? ?????? LCD_RST
#define LCD_RST1  GPIO_SetBits(GPIOB, LCD_RST_PIN)
#define LCD_RST0  GPIO_ResetBits(GPIOB, LCD_RST_PIN)
// ?????????? ?????? LCD_DC
#define LCD_DC1   GPIO_SetBits(GPIOB, LCD_A0_PIN)
#define LCD_DC0   GPIO_ResetBits(GPIOB, LCD_A0_PIN)
// ?????????? ?????? LCD_CS
#define LCD_CS1   GPIO_SetBits(GPIOB, LCD_CSE_PIN)
#define LCD_CS0   GPIO_ResetBits(GPIOB, LCD_CSE_PIN)

#else

#define IO_BB_ADDR(io_reg_addr,bit_number) ((uint32_t*)(PERIPH_BB_BASE + (((uint32_t)io_reg_addr - PERIPH_BASE) << 5) + (bit_number << 2)))

#define LCD_RST_BB_ADDR  IO_BB_ADDR(&LCD_GPIO->ODR, LCD_RST_PIN)
#define LCD_A0_BB_ADDR   IO_BB_ADDR(&LCD_GPIO->ODR, LCD_A0_PIN)
#define LCD_CSE_BB_ADDR  IO_BB_ADDR(&LCD_GPIO->ODR, LCD_CSE_PIN)
#define LCD_SDA_BB_ADDR  IO_BB_ADDR(&LCD_GPIO->ODR, LCD_SDA_PIN)
#define LCD_SCK_BB_ADDR  IO_BB_ADDR(&LCD_GPIO->ODR, LCD_SCK_PIN)

// ”правление линией LCD_RST
#define LCD_RST1  *LCD_RST_BB_ADDR=0x00000001
#define LCD_RST0  *LCD_RST_BB_ADDR=0x00000000
// ”правление линией LCD_DC
#define LCD_DC1   *LCD_A0_BB_ADDR=0x00000001
#define LCD_DC0   *LCD_A0_BB_ADDR=0x00000000
// ”правление линией LCD_CS
#define LCD_CS1   *LCD_CSE_BB_ADDR=0x00000001
#define LCD_CS0   *LCD_CSE_BB_ADDR=0x00000000
#endif


#ifndef LCD_TO_SPI2
// ”правление линией LCD_SCK
#define LCD_SCK1  *LCD_SCK_BB_ADDR=0x00000001
#define LCD_SCK0  *LCD_SCK_BB_ADDR=0x00000000
// ”правление линией LCD_MOSI
#define LCD_MOSI1 *LCD_SDA_BB_ADDR=0x00000001
#define LCD_MOSI0 *LCD_SDA_BB_ADDR=0x00000000
#endif

extern void lcd7735_setup(void);
extern void lcd7735_senddata(const uint8_t cmd);
extern void lcd7735_senddata16(const uint16_t data);
extern void lcd7735_sendCmd(const uint8_t cmd);
extern void lcd7735_sendData(const uint8_t data);

extern void TimingDelay_Decrement(void);
extern void delay_ms(uint32_t delay_value);

#endif /* __HW_CONFIG__ */

