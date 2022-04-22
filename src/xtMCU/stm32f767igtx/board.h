/**
  * @file     board.h
  * @date     2022-01-12
  * @author   yxnan <yxnan@pm.me>
  * @brief    Board definition for STM32F767IGTx
  *
  * This file contains the IO defines of the application.
  * Renamed from STM32CubeMX generated `main.h`
  */

#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"

#define SPI5_CS_Pin GPIO_PIN_6
#define SPI5_CS_GPIO_Port GPIOF
#define LED_R_Pin GPIO_PIN_10
#define LED_R_GPIO_Port GPIOH
#define LED_G_Pin GPIO_PIN_11
#define LED_G_GPIO_Port GPIOH
#define LED_B_Pin GPIO_PIN_12
#define LED_B_GPIO_Port GPIOH
#define X4_GPIO1_Pin GPIO_PIN_8
#define X4_GPIO1_GPIO_Port GPIOC
#define X4_GPIO2_Pin GPIO_PIN_9
#define X4_GPIO2_GPIO_Port GPIOC
#define USART1_TX_Pin GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA
#define USART1_RX_Pin GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA
#define X4_ENABLE_Pin GPIO_PIN_10
#define X4_ENABLE_GPIO_Port GPIOC

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
