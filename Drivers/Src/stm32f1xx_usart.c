#include "stm32f1xx_usart.h"
#include "stm32f1xx_gpio.h"

static uint32_t USART_GetPCLK1(void) {
    /* If PLL is system clock (SWS = 0b10), APB1 is typically 36 MHz; else reset default HSI 8 MHz */
    uint32_t sws = (RCC->CFGR >> 2) & 0x03;
    if (sws == 0x02) {
        return 36000000UL;
    }
    return 8000000UL;
}

void USART2_Init(uint32_t BaudRate) {
    USART2_PCLK_EN();
    GPIOA_PCLK_EN();

    // PA2 = TX (Alt Push-Pull), PA3 = RX (Input Floating)
    GPIO_Init(GPIOA, 2, GPIO_MODE_ALT_PP_2MHZ);
    GPIO_Init(GPIOA, 3, GPIO_MODE_IN_FLOATING);

    // Compute Baud Rate register value dynamically
    uint32_t pclk1 = USART_GetPCLK1();
    USART2->BRR = (pclk1 + (BaudRate / 2U)) / BaudRate;

    // Enable Transmitter, Receiver, and Module
    USART2->CR1 |= (1 << 3) | (1 << 2) | (1 << 13);
}

void USART2_SendChar(char ch) {
    while (!(USART2->SR & (1 << 7))); // Wait TXE
    USART2->DR = (ch & 0xFF);
}

void USART2_SendString(const char *str) {
    while (*str) {
        USART2_SendChar(*str++);
    }
}

char USART2_ReceiveChar(void) {
    while (!(USART2->SR & (1 << 5))); // Wait RXNE
    return (char)(USART2->DR & 0xFF);
}