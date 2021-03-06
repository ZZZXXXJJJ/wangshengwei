#ifndef __DEBUG_USART_H
#define	__DEBUG_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


//引脚定义
/*******************************************************/
//#define DEBUG_USART                             USART1
//#define DEBUG_USART_CLK                         RCC_APB2Periph_USART1
//#define DEBUG_USART_BAUDRATE                    115200  //串口波特率

//#define DEBUG_USART_RX_GPIO_PORT                GPIOA
//#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
//#define DEBUG_USART_RX_PIN                      GPIO_Pin_10
//#define DEBUG_USART_RX_AF                       GPIO_AF_USART1
//#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource10

//#define DEBUG_USART_TX_GPIO_PORT                GPIOA
//#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
//#define DEBUG_USART_TX_PIN                      GPIO_Pin_9
//#define DEBUG_USART_TX_AF                       GPIO_AF_USART1
//#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource9

//#define DEBUG_USART_IRQHandler                  USART1_IRQHandler
//#define DEBUG_USART_IRQ                 				USART1_IRQn

//void Debug_USART_Config(void);
/************************************************************/



//引脚定义
/*******************************************************/
#define RNSS_USART                             USART3
#define RNSS_USART_CLK                         RCC_APB1Periph_USART3
#define RNSS_USART_BAUDRATE                    9600  //串口波特率

#define RNSS_USART_RX_GPIO_PORT                GPIOB
#define RNSS_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define RNSS_USART_RX_PIN                      GPIO_Pin_11
#define RNSS_USART_RX_AF                       GPIO_AF_USART3
#define RNSS_USART_RX_SOURCE                   GPIO_PinSource11

#define RNSS_USART_TX_GPIO_PORT                GPIOB
#define RNSS_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define RNSS_USART_TX_PIN                      GPIO_Pin_10
#define RNSS_USART_TX_AF                       GPIO_AF_USART3
#define RNSS_USART_TX_SOURCE                   GPIO_PinSource10

#define RNSS_USART_IRQHandler                  USART3_IRQHandler
#define RNSS_USART_IRQ                 				 USART3_IRQn

void RNSS_USART_Config(void);
/************************************************************/

//引脚定义
/*******************************************************/
#define RDSS_USART                             USART6
#define RDSS_USART_CLK                         RCC_APB2Periph_USART6
#define RDSS_USART_BAUDRATE                    115200  //串口波特率

#define RDSS_USART_RX_GPIO_PORT                GPIOC
#define RDSS_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define RDSS_USART_RX_PIN                      GPIO_Pin_7
#define RDSS_USART_RX_AF                       GPIO_AF_USART6
#define RDSS_USART_RX_SOURCE                   GPIO_PinSource7

#define RDSS_USART_TX_GPIO_PORT                GPIOC
#define RDSS_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define RDSS_USART_TX_PIN                      GPIO_Pin_6
#define RDSS_USART_TX_AF                       GPIO_AF_USART6
#define RDSS_USART_TX_SOURCE                   GPIO_PinSource6

#define RDSS_USART_IRQHandler                  USART6_IRQHandler
#define RDSS_USART_IRQ                 				 USART6_IRQn

void RDSS_USART_Config(void);
/************************************************************/
//引脚定义
/*******************************************************/
#define CENTER_USART                             UART4
#define CENTER_USART_CLK                         RCC_APB1Periph_UART4
#define CENTER_USART_BAUDRATE                    115200  //串口波特率

#define CENTER_USART_RX_GPIO_PORT                GPIOC
#define CENTER_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define CENTER_USART_RX_PIN                      GPIO_Pin_11
#define CENTER_USART_RX_AF                       GPIO_AF_UART4
#define CENTER_USART_RX_SOURCE                   GPIO_PinSource11

#define CENTER_USART_TX_GPIO_PORT                GPIOC
#define CENTER_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define CENTER_USART_TX_PIN                      GPIO_Pin_10
#define CENTER_USART_TX_AF                       GPIO_AF_UART4
#define CENTER_USART_TX_SOURCE                   GPIO_PinSource10

#define CENTER_USART_IRQHandler                  UART4_IRQHandler
#define CENTER_USART_IRQ                 				 UART4_IRQn

void CENTER_USART_Config(void);
/************************************************************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_  ( USART_TypeDef * pUSARTx, char *str);
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen );
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif /* __USART1_H */
