#ifndef STM32F1XX_I2C_H
#define STM32F1XX_I2C_H

#include "stm32f1xx.h"

typedef struct {
    __VO uint32_t CR1;
    __VO uint32_t CR2;
    __VO uint32_t OAR1;
    __VO uint32_t OAR2;
    __VO uint32_t DR;
    __VO uint32_t SR1;
    __VO uint32_t SR2;
    __VO uint32_t CCR;
    __VO uint32_t TRISE;
} I2C_RegDef_t;

#define I2C1 ((I2C_RegDef_t*) I2C1_BASE)

void I2C1_Init(void);
void I2C1_MasterSendData(uint8_t SlaveAddr, uint8_t *pData, uint32_t Len);

#endif