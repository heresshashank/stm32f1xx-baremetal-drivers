#ifndef STM32F1XX_USART_H
#define STM32F1XX_USART_H

#include "stm32f1xx.h"

typedef struct {
    __VO uint32_t SR;
    __VO uint32_t DR;
    __VO uint32_t BRR;
    __VO uint32_t CR1;
    __VO uint32_t CR2;
    __VO uint32_t CR3;
    __VO uint32_t GTPR;
} USART_RegDef_t;

#define USART2 ((USART_RegDef_t*) USART2_BASE)

void USART2_Init(uint32_t BaudRate);
void USART2_SendChar(char ch);
void USART2_SendString(const char *str);
char USART2_ReceiveChar(void);

#endif