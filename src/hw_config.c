/****************************************************************************************
*
* Hardware configuration and low level functions
*
* The idea of HW initialization and configuration have taken on from
* http://vg.ucoz.ru/load/stm32_ickhodnye_teksty_programm_na_si/stm32_biblioteka_podkljuchenija_displeja_na_kontrollere_st7735_dlja_stm32f4/16-1-0-41
****************************************************************************************/
#include <stdio.h>
#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include "platform_config.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_spi.h"

#include "hw_config.h"

static __IO uint32_t TimingDelay;

#ifndef __ENABLE_NOT_STABLE
// not work :( It is possible that GPIO pin doesn't switch to input mode, but I don't know hot to do it.
void receive_data(const uint8_t cmd, uint8_t *data, uint8_t cnt) {
    uint8_t i;
    LCD_DC0;
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    SPI_SendData(SPI2, cmd);
    //while(SPI2->SR & SPI_SR_BSY);
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    LCD_DC1;
    LCD_DC0;
    LCD_DC1;
    SPI_BiDirectionalLineConfig(SPI2,SPI_Direction_Rx);
    for(i=0; i<cnt; i++) {
        //		while(SPI2->SR & SPI_SR_BSY);
        if( SPI2->SR & SPI_I2S_FLAG_OVR )
            STM_EVAL_LEDOn(LED3);
        else
            STM_EVAL_LEDOff(LED3);
        if( SPI2->SR & I2S_FLAG_UDR )
            STM_EVAL_LEDOn(LED7);
        else
            STM_EVAL_LEDOff(LED7);
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
        data[i] = SPI_ReceiveData8(SPI2);
    }
    LCD_DC0;
    SPI_BiDirectionalLineConfig(SPI2,SPI_Direction_Tx);
    LCD_CS1;
    LCD_CS0;
}

#endif

// Send byte via SPI to controller
void lcd7735_senddata(const uint8_t data) {
#ifdef LCD_TO_SPI2
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    SPI_SendData(SPI2, data);
#else
    unsigned char i;
    for(i=0; i<8; i++) {
        if (data & 0x80) LCD_MOSI1;
        else LCD_MOSI0;
        data = data<<1;
        LCD_SCK0;
        LCD_SCK1;
    }
#endif
}

// Send byte via SPI to controller
void lcd7735_senddata16(const uint16_t data) {
#ifdef LCD_TO_SPI2
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI2, data);
#else
    lcd7735_senddata(data >> 8);
    lcd7735_senddata(data &0xFF);
#endif
}

// Send control command to controller
void lcd7735_sendCmd(const uint8_t cmd) {
    LCD_DC0;
    lcd7735_senddata(cmd);
#ifdef LCD_TO_SPI2
    while(SPI2->SR & SPI_SR_BSY);
#endif
}

// Send parameters o command to controller
void lcd7735_sendData(const uint8_t data) {
    LCD_DC1;
    lcd7735_senddata(data);
#ifdef LCD_TO_SPI2
    while(SPI2->SR & SPI_SR_BSY);
#endif
}

// Init hardware
void lcd7735_setup(void) {

#ifdef LCD_TO_SPI2  // hardware SIP
    SPI_InitTypeDef  SPI_InitStructure;
#endif
    GPIO_InitTypeDef GPIO_InitStructure;

    //    SystemInit();

    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
    STM_EVAL_LEDInit(LED7);
    STM_EVAL_LEDInit(LED8);
    STM_EVAL_LEDInit(LED9);
    STM_EVAL_LEDInit(LED10);

    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000)) {
        /* Capture error */
        while (1) {}
    }

    RCC_AHB1PeriphClockCmd(LCD_AHB1_GPIO, ENABLE);

#ifdef LCD_TO_SPI2  // hardware SIP

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    // SCK (Pin_13), MOSI (Pin_15) SPI2
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);   // SPI2_CLK
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);   // SPI2_MOSI

    GPIO_InitStructure.GPIO_Pin 			= GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode 			= GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed 			= GPIO_Speed_Config;
    GPIO_InitStructure.GPIO_OType 			= GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  			= GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    SPI_DeInit(SPI2);
    SPI_InitStructure.SPI_Mode        		= SPI_Mode_Master;
    SPI_InitStructure.SPI_Direction   		= SPI_Direction_1Line_Rx;
    SPI_InitStructure.SPI_DataSize 			= SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL 				= SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA 				= SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS 				= SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI2_BaudRatePrescaler;
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;

    SPI_Init(SPI2, &SPI_InitStructure);
    SPI_Cmd(SPI2, ENABLE);

#ifndef	LCD_SOFT_RESET
    GPIO_InitStructure.GPIO_Pin  			= LCD_CSE_PIN | LCD_A0_PIN | LCD_RST_PIN;
#else
    GPIO_InitStructure.GPIO_Pin  			= LCD_CSE_PIN | LCD_A0_PIN ;
#endif /* LCD_SOFT_RESET */

#else // Software SPI configuration

#ifndef	LCD_SOFT_RESET
    GPIO_InitStructure.GPIO_Pin  			=(1<<LCD_CSE_PIN) | (1<<LCD_A0_PIN) | (1<<LCD_SCK_PIN) | (1<<LCD_RST_PIN) | (1<<LCD_SDA_PIN);
#else
    GPIO_InitStructure.GPIO_Pin  			=(1<<LCD_CSE_PIN) | (1<<LCD_A0_PIN) | (1<<LCD_SCK_PIN) | (1<<LCD_SDA_PIN);
#endif /* LCD_SOFT_RESET */

    LCD_SCK0;
#endif /* LCD_TO_SPI2 */

    GPIO_InitStructure.GPIO_Mode 			=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType			=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd 			=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed			=GPIO_Speed_Config;
    GPIO_Init(LCD_GPIO, &GPIO_InitStructure);

    SPI_BiDirectionalLineConfig(SPI2,SPI_Direction_Tx);
}

void delay_ms(uint32_t delay_value) {
    TimingDelay = delay_value;
    while( TimingDelay != 0 );
}

void TimingDelay_Decrement(void) {
    if (TimingDelay != 0x00) TimingDelay--;
    else STM_EVAL_LEDToggle(LED4);
}

// override handler
void SysTick_Handler(void) {
    TimingDelay_Decrement();
}
