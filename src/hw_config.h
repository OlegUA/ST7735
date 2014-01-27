#ifndef __HW_CONFIG__
#define __HW_CONFIG__

#include "stm32f30x.h"
//
// Hardware SPI
#define LCD_TO_SPI2

// Can't be less 6 MGz according to datasheet on SR7755 controller
#define SPI2_BaudRatePrescaler   SPI_BaudRatePrescaler_2

// -----------------------------------------------------------------------------------------------------------------
// ������ ���������� ������� �������
// -----------------------------------------------------------------------------------------------------------------
// ���� �������� ���� ��������������� �� ������������� ����� ������ ������� ����� � ���� �������� ���������
// ��������:
// LCD_CS0; - ��� ������ ������� ����� ������� ���������� �������� (����������) � ��������
// LCD_CS1; - ��� ������ ������ ������� (����� ���������� ��������)
// ���� �������� ������� - �� ����� ������� �������������� ������������� �� ���� �������������
//#define LCD_SEL_AUTO

// ---------------------------------------------------------------------------------------------------------------------------
// ������������� ����������� �������
// ---------------------------------------------------------------------------------------------------------------------------
// ��� �������� �������� ��� ����������� SPI ��� ����� ���������� � ������ ������� ������ ���� ���������� � ������ ����� �����\������ !
// ���� �� ����� ����� ����������� SPI2 ��, �� ���� ���� ������ ���� ���������� ����� RST, A0, CSE
// � ��������� ����� (SDA, SCK) ������ ���� ���������� � GPIOB (���� 15 � 13 ��������������)
//                             +--------------------+
#define 	LCD_GPIO			GPIOB					// ���� � �������� ���������� ���� �������
//                             +--------------------+
#define     LCD_AHB1_GPIO		RCC_AHBPeriph_GPIOB	// ���� � ������� ��������� ����
//                             +--------------------+
// ���� ������� (����������)
//                             +--+
#define 	LCD_RST_PIN 		GPIO_Pin_14
//                             +--+
#define     LCD_A0_PIN			GPIO_Pin_12
//                             +--+
#define		LCD_CSE_PIN			GPIO_Pin_10
//                             +--+
//
// � ������ ���� ������������ SPI2 ����������� �� ����� SDA ������� ������ ���� ��������� � GPIOB_Pin_15, � SCK � GPIOB_Pin_13
// ��������� ����� ��� SPI2 ����������� ����� ���� ���������� � ������ ����� (�� ������ � GPIOB) ��. ����
// ���� ������� (������)
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

// ���������� ������ LCD_RST
#define LCD_RST1  *LCD_RST_BB_ADDR=0x00000001
#define LCD_RST0  *LCD_RST_BB_ADDR=0x00000000
// ���������� ������ LCD_DC
#define LCD_DC1   *LCD_A0_BB_ADDR=0x00000001
#define LCD_DC0   *LCD_A0_BB_ADDR=0x00000000
// ���������� ������ LCD_CS
#define LCD_CS1   *LCD_CSE_BB_ADDR=0x00000001
#define LCD_CS0   *LCD_CSE_BB_ADDR=0x00000000
#endif


#ifndef LCD_TO_SPI2
// ���������� ������ LCD_SCK
#define LCD_SCK1  *LCD_SCK_BB_ADDR=0x00000001
#define LCD_SCK0  *LCD_SCK_BB_ADDR=0x00000000
// ���������� ������ LCD_MOSI
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

