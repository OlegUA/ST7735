/**
  ******************************************************************************
  * @file    platform_config.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM32303C_EVAL)
#define USE_STM32303C_EVAL
#endif

/*Unique Devices IDs register set*/
#define         ID1          (0x1FFFF7E8)
#define         ID2          (0x1FFFF7EC)
#define         ID3          (0x1FFFF7F0)

/* Define the STM32F10x hardware depending on the used evaluation board */
#if defined (USE_STM32303C_EVAL)
  #if defined(STM32F30X)
    #define USB_INT_DEFAULT
    #define USB_DISCONNECT                      GPIOE  
    #define USB_DISCONNECT_PIN                  GPIO_Pin_14
    #define RCC_AHBPeriph_GPIO_DISCONNECT       RCC_AHBPeriph_GPIOE
  #else
    #define USB_DISCONNECT                      GPIOB  
    #define USB_DISCONNECT_PIN                  GPIO_Pin_8
    #define RCC_AHBPeriph_GPIO_DISCONNECT       RCC_AHBPeriph_GPIOB
  #endif /* STM32F30X */
#endif /* USE_STM3210B_EVAL */

#define RCC_AHBPeriph_ALLGPIO                 (RCC_AHBPeriph_GPIOA \
                                              | RCC_AHBPeriph_GPIOB \
                                              | RCC_AHBPeriph_GPIOC \
                                              | RCC_AHBPeriph_GPIOD \
                                              | RCC_AHBPeriph_GPIOE \
                                              | RCC_AHBPeriph_GPIOF )

/*** compatibility with F4 board constants ***/
#ifdef STM32F30X
#define SPI_SendData			SPI_SendData8
#define SPI_I2S_SendData		SPI_I2S_SendData16
#define RCC_AHB1PeriphClockCmd	RCC_AHBPeriphClockCmd
//#define LCD_AHB1_GPIO			LCD_AHB_GPIO
#define GPIO_Speed_Config		GPIO_Speed_50MHz
#define SPI_DeInit				SPI_I2S_DeInit
#define GPIO_AF_SPI2			GPIO_AF_5
#endif

#ifndef GPIO_Speed_Config
#define GPIO_Speed_Config		GPIO_Speed_100MHz
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
