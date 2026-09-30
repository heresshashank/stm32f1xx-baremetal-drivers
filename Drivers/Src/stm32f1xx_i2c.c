#include "stm32f1xx_i2c.h"
#include "stm32f1xx_gpio.h"

static uint32_t I2C_GetPCLK1_MHz(void) {
    uint32_t sws = (RCC->CFGR >> 2) & 0x03;
    if (sws == 0x02) {
        return 36; // 36 MHz APB1 with PLL
    }
    return 8; // 8 MHz reset default
}

void I2C1_Init(void) {
    I2C1_PCLK_EN();
    GPIOB_PCLK_EN();

    // PB6 (SCL), PB7 (SDA) -> AF Open-Drain
    GPIO_Init(GPIOB, 6, GPIO_MODE_ALT_OD_2MHZ);
    GPIO_Init(GPIOB, 7, GPIO_MODE_ALT_OD_2MHZ);

    uint32_t pclk_mhz = I2C_GetPCLK1_MHz();
    I2C1->CR2 = pclk_mhz;                // Set peripheral clock frequency in MHz
    I2C1->CCR = (pclk_mhz * 1000000UL) / (2 * 100000UL); // 100 kHz standard mode
    I2C1->TRISE = pclk_mhz + 1;          // Maximum rise time
    I2C1->CR1 |= (1 << 0);               // Enable I2C1
}

void I2C1_MasterSendData(uint8_t SlaveAddr, uint8_t *pData, uint32_t Len) {
    if (Len == 0) return;

    I2C1->CR1 |= (1 << 8); // Generate START
    while (!(I2C1->SR1 & (1 << 0))); // Wait SB

    I2C1->DR = (SlaveAddr << 1); // Address + Write
    while (!(I2C1->SR1 & (1 << 1))); // Wait ADDR

    // Reading SR1 followed by SR2 clears ADDR flag
    volatile uint32_t dummy = I2C1->SR1;
    dummy = I2C1->SR2;
    (void)dummy;

    for (uint32_t i = 0; i < Len; i++) {
        while (!(I2C1->SR1 & (1 << 7))); // Wait TXE
        I2C1->DR = pData[i];
    }

    while (!(I2C1->SR1 & (1 << 2))); // Wait BTF
    I2C1->CR1 |= (1 << 9); // Generate STOP
}