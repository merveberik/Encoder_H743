/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"

char _100_msec;

void Error_Handler(void);

#define INT_Pin 			GPIO_PIN_3
#define INT_GPIO_Port 		GPIOA
#define INT_EXTI_IRQn 		EXTI3_IRQn
#define LD1_Pin 			GPIO_PIN_0
#define LD1_GPIO_Port 		GPIOB
#define LD3_Pin 			GPIO_PIN_14
#define LD3_GPIO_Port 		GPIOB
#define SPI_CS_Pin 			GPIO_PIN_14
#define SPI_CS_GPIO_Port 	GPIOD
#define LD2_Pin 			GPIO_PIN_7
#define LD2_GPIO_Port 		GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
