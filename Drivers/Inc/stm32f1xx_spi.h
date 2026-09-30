#ifndef STM32F1XX_SPI_H
#define STM32F1XX_SPI_H

#include "stm32f1xx.h"

typedef struct {
    __VO uint32_t CR1;
    __VO uint32_t CR2;
    __VO uint32_t SR;
    __VO uint32_t DR;
    __VO uint32_t CRCPR;
    __VO uint32_t RXCRCR;
    __VO uint32_t TXCRCR;
    __VO uint32_t I2SCFGR;
    __VO uint32_t I2SPR;
} SPI_RegDef_t;

#define SPI1 ((SPI_RegDef_t*) SPI1_BASE)

void SPI1_Init(void);
void SPI1_Transmit(uint8_t *pData, uint32_t Size);
void SPI1_Receive(uint8_t *pData, uint32_t Size);

#endif