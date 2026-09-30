#include "stm32f1xx.h"
#include "stm32f1xx_gpio.h"

void GPIO_Init(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ModeCnf) {
    uint8_t cnf_mode = ModeCnf & 0x0F;
    if (PinNumber < 8) { // Config Low Register (Pins 0-7)
        pGPIOx->CRL &= ~(0x0F << (PinNumber * 4));
        pGPIOx->CRL |=  (cnf_mode << (PinNumber * 4));
    } else { // Config High Register (Pins 8-15)
        uint8_t shift = (PinNumber - 8) * 4;
        pGPIOx->CRH &= ~(0x0F << shift);
        pGPIOx->CRH |=  (cnf_mode << shift);
    }

    /* Handle Pull-Up / Pull-Down configuration via ODR */
    if (cnf_mode == GPIO_MODE_IN_PU_PD) {
        if (ModeCnf & 0x10) {
            pGPIOx->ODR |= (1U << PinNumber);  // Pull-Up
        } else {
            pGPIOx->ODR &= ~(1U << PinNumber); // Pull-Down
        }
    }
}

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    return (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x01);
}

void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) {
    if (Value) {
        pGPIOx->BSRR = (1U << PinNumber); // Atomic Bit Set
    } else {
        pGPIOx->BRR  = (1U << PinNumber); // Atomic Bit Reset
    }
}

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    pGPIOx->ODR ^= (1U << PinNumber);
}