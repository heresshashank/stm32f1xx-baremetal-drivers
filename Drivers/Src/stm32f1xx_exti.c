#include "stm32f1xx_exti.h"

void EXTI_Config(uint8_t PortCode, uint8_t PinNumber, uint8_t TriggerEdge) {
    AFIO_PCLK_EN();

    uint8_t regIdx = PinNumber / 4;
    uint8_t bitShift = (PinNumber % 4) * 4;
    AFIO->EXTICR[regIdx] &= ~(0x0F << bitShift);
    AFIO->EXTICR[regIdx] |=  (PortCode << bitShift);

    if (TriggerEdge == EXTI_TRIGGER_RISING) {
        EXTI->RTSR |= (1 << PinNumber);
        EXTI->FTSR &= ~(1 << PinNumber);
    } else if (TriggerEdge == EXTI_TRIGGER_FALLING) {
        EXTI->FTSR |= (1 << PinNumber);
        EXTI->RTSR &= ~(1 << PinNumber);
    } else {
        EXTI->RTSR |= (1 << PinNumber);
        EXTI->FTSR |= (1 << PinNumber);
    }

    EXTI->IMR |= (1 << PinNumber); // Unmask EXTI Line

    if (PinNumber <= 4) {
        *NVIC_ISER0 |= (1U << (6 + PinNumber)); // EXTI0 - EXTI4 (IRQs 6 to 10)
    } else if (PinNumber <= 9) {
        *NVIC_ISER0 |= (1U << 23);              // EXTI9_5 (IRQ 23)
    } else if (PinNumber <= 15) {
        *NVIC_ISER1 |= (1U << (40 - 32));       // EXTI15_10 (IRQ 40)
    }
}

void EXTI_ClearPendingBit(uint8_t PinNumber) {
    /* EXTI->PR is rc_w1 (read/clear-by-write-1). Writing 1 clears only this bit without altering others */
    EXTI->PR = (1U << PinNumber);
}