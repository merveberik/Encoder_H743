#include "spi.h"

SPI_HandleTypeDef hspi1;

void blind_loop(){
	unsigned int i;
	for(i = 0; i < 100; i++){
	}

}
void MX_SPI1_Init(void){

	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;				//SPI_MODE_MASTER
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_16BIT;		//SPI_DATASIZE_8BIT
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;			//SPI_PHASE_1EDGE
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 0x0;
	hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi1.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi1.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi1) != HAL_OK){
		Error_Handler();
	}
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(spiHandle->Instance==SPI1){
		__HAL_RCC_SPI1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**SPI1 GPIO Configuration
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PD7     ------> SPI1_MOSI
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle){

	if(spiHandle->Instance==SPI1){
		__HAL_RCC_SPI1_CLK_DISABLE();

		/**SPI1 GPIO Configuration
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PD7     ------> SPI1_MOSI
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_7);

	}
} 

uint16_t AS5050A_SPI_Read_2Byte (uint16_t addr){
	uint16_t tx_data = READ_COMMAND | addr<<1 | PAR_EN;
	uint16_t rx_data;
//	rx_data[0] = 0;
//	rx_data[1] = 0;
	while(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX_RX);
	CS_PIN_LOW;
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) &tx_data,(uint8_t*) &rx_data,  1, 50);
	CS_PIN_HIGH;
	uint16_t ttx_data = READ_COMMAND | addr<<1 | PAR_DIS;

	while(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX_RX);
	CS_PIN_LOW;
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) &ttx_data,(uint8_t*) &rx_data,  1, 50);
//	HAL_SPI_Transmit(&hspi1, (uint8_t*) &tx_data, 1, 50);
//	CS_PIN_HIGH;
//	blind_loop();
//	while(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX_RX);
//	CS_PIN_LOW;
//	HAL_SPI_Receive(&hspi1, (uint8_t*) &rx_data, 1, 50);
	CS_PIN_HIGH;
	return rx_data;
}

void AS5050A_SPI_Write (uint16_t addr, uint16_t data){
	uint16_t tx_data [2];
	tx_data[0] = WRITE_COMMAND | addr | PAR_EN;
	tx_data[1] = data;
	CS_PIN_LOW;
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &tx_data, 2, 50);
	CS_PIN_HIGH;

}










