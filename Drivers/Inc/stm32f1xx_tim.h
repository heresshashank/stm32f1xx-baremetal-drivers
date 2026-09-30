#ifndef STM32F1XX_TIM_H
#define STM32F1XX_TIM_H

#include "stm32f1xx.h"

typedef struct {
    __VO uint32_t CR1;
    __VO uint32_t CR2;
    __VO uint32_t SMCR;
    __VO uint32_t DIER;
    __VO uint32_t SR;
    __VO uint32_t EGR;
    __VO uint32_t CCMR1;
    __VO uint32_t CCMR2;
    __VO uint32_t CCER;
    __VO uint32_t CNT;
    __VO uint32_t PSC;
    __VO uint32_t ARR;
    uint32_t      RESERVED0;
    __VO uint32_t CCR1;
    __VO uint32_t CCR2;
    __VO uint32_t CCR3;
    __VO uint32_t CCR4;
} TIM_RegDef_t;

#define TIM2 ((TIM_RegDef_t*) TIM2_BASE)

void TIM2_PWM_Init(uint16_t Period, uint16_t Prescaler);
void TIM2_SetDutyCycle(uint16_t DutyCycle);

#endif