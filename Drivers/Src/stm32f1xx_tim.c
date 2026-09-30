#include "stm32f1xx_tim.h"
#include "stm32f1xx_gpio.h"

void TIM2_PWM_Init(uint16_t Period, uint16_t Prescaler) {
    TIM2_PCLK_EN();
    GPIOA_PCLK_EN();

    // PA0 = TIM2_CH1 (Alternate Function Push-Pull)
    GPIO_Init(GPIOA, 0, GPIO_MODE_ALT_PP_2MHZ);

    TIM2->PSC = Prescaler;
    TIM2->ARR = Period;

    TIM2->CCMR1 |= (6 << 4) | (1 << 3); // PWM Mode 1
    TIM2->CCER |= (1 << 0);             // Enable Channel 1 Output
    TIM2->CR1 |= (1 << 0);              // Enable Counter
}

void TIM2_SetDutyCycle(uint16_t DutyCycle) {
    TIM2->CCR1 = DutyCycle;
}