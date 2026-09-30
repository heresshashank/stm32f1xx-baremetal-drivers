#include "stm32f1xx_spi.h"
#include "stm32f1xx_gpio.h"

void SPI1_Init(void) {
    SPI1_PCLK_EN();
    GPIOA_PCLK_EN();

    // PA5 (SCK), PA7 (MOSI) -> AF Push-Pull, PA6 (MISO) -> Input Floating
    GPIO_Init(GPIOA, 5, GPIO_MODE_ALT_PP_2MHZ);
    GPIO_Init(GPIOA, 6, GPIO_MODE_IN_FLOATING);
    GPIO_Init(GPIOA, 7, GPIO_MODE_ALT_PP_2MHZ);

    SPI1->CR1 |= (1 << 2) | (1 << 3) | (1 << 8) | (1 << 9);
    SPI1->CR1 |= (1 << 6); // Enable SPI1
}

void SPI1_Transmit(uint8_t *pData, uint32_t Size) {
    for (uint32_t i = 0; i < Size; i++) {
        while (!(SPI1->SR & (1 << 1))); // Wait TXE
        SPI1->DR = pData[i];
        while (!(SPI1->SR & (1 << 0))); // Wait RXNE
        (void)SPI1->DR;                 // Read DR to clear RXNE and prevent overrun (OVR)
    }
    while (SPI1->SR & (1 << 7)); // Wait BSY
}

void SPI1_Receive(uint8_t *pData, uint32_t Size) {
    for (uint32_t i = 0; i < Size; i++) {
        while (!(SPI1->SR & (1 << 1))); // Wait TXE
        SPI1->DR = 0xFF;                // Send dummy byte to generate clock pulses
        while (!(SPI1->SR & (1 << 0))); // Wait RXNE
        pData[i] = (uint8_t)(SPI1->DR & 0xFF);
    }
}