#ifndef STM32F1XX_GPIO_H
#define STM32F1XX_GPIO_H

#include "stm32f1xx.h"

#define GPIO_PIN_RESET           0
#define GPIO_PIN_SET             1

/* GPIO Configuration Modes (4-bit MODE + CNF field for STM32F1) */
#define GPIO_MODE_ANALOG         0x00  /* Analog Mode */
#define GPIO_MODE_IN_FLOATING    0x04  /* Input Floating */
#define GPIO_MODE_IN_PU_PD       0x08  /* Input Pull-Up/Pull-Down (raw) */
#define GPIO_MODE_IN_PULLDOWN    0x08  /* Input Pull-Down (ODR=0) */
#define GPIO_MODE_IN_PULLUP      0x18  /* Input Pull-Up (ODR=1) */
#define GPIO_MODE_OUT_PP_2MHZ    0x02  /* Output Push-Pull 2MHz */
#define GPIO_MODE_OUT_OD_2MHZ    0x06  /* Output Open-Drain 2MHz */
#define GPIO_MODE_OUT_PP_10MHZ   0x01  /* Output Push-Pull 10MHz */
#define GPIO_MODE_OUT_OD_10MHZ   0x05  /* Output Open-Drain 10MHz */
#define GPIO_MODE_OUT_PP_50MHZ   0x03  /* Output Push-Pull 50MHz */
#define GPIO_MODE_OUT_OD_50MHZ   0x07  /* Output Open-Drain 50MHz */
#define GPIO_MODE_ALT_PP_2MHZ    0x0A  /* Alternate Function Push-Pull 2MHz */
#define GPIO_MODE_ALT_OD_2MHZ    0x0E  /* Alternate Function Open-Drain 2MHz */
#define GPIO_MODE_ALT_PP_50MHZ   0x0B  /* Alternate Function Push-Pull 50MHz */
#define GPIO_MODE_ALT_OD_50MHZ   0x0F  /* Alternate Function Open-Drain 50MHz */

void GPIO_Init(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ModeCnf);
uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif