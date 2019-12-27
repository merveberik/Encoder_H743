/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

extern SPI_HandleTypeDef hspi1;

void MX_SPI1_Init(void);

#define EF_DIS  		0
#define EF_EN			1
#define PAR_DIS			0x0000
#define PAR_EN			0x0001
#define READ_COMMAND 	0x8000
#define WRITE_COMMAND 	0x0000

#define SPI_POR_OF_REG			0x3F22		//R-W
#define SPI_SOFTWARE_RESET_REG	0x3C00		//W
#define SPI_MASTER_RESET_REG	0x33A5		//W
#define SPI_CLEAR_EF_REG		0x3380		//R
#define SPI_NOP_REG				0x0000		//W
#define SPI_AGC_REG				0x3FF8		//R-W
#define SPI_ANGULAR_DATA_REG	0x3FFF		//R
#define SPI_ERR_STATUS_REG		0x335A		//R
#define SPI_SYSTEM_CONF_REG		0x3F20		//R-W


#define CS_PIN_LOW 		HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET)
#define CS_PIN_HIGH		HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET)

uint16_t AS5050A_SPI_Read_2Byte (uint16_t addr);
void AS5050A_SPI_Write (uint16_t addr, uint16_t data);
void blind_loop();

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
