#ifndef STM32F1XX_EXTI_H
#define STM32F1XX_EXTI_H

#include "stm32f1xx.h"

#define EXTI_TRIGGER_RISING  0
#define EXTI_TRIGGER_FALLING 1
#define EXTI_TRIGGER_BOTH    2

/* EXTI Port Codes for AFIO_EXTICR */
#define EXTI_PORT_A          0
#define EXTI_PORT_B          1
#define EXTI_PORT_C          2
#define EXTI_PORT_D          3

void EXTI_Config(uint8_t PortCode, uint8_t PinNumber, uint8_t TriggerEdge);
void EXTI_ClearPendingBit(uint8_t PinNumber);

#endif