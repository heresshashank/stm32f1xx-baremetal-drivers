#include "stm32f1xx.h"
#include "stm32f1xx_gpio.h"
#include "stm32f1xx_usart.h"
#include "../Benchmarks/cycle_counter.h"

/**
 * @brief Configure System Clock to 72 MHz using external 8 MHz HSE crystal.
 *        Falls back safely to internal 8 MHz HSI if HSE is not present.
 */
static void SystemClock_Config_72MHz(void) {
    RCC->CR |= (1 << 16); // Enable HSE
    uint32_t timeout = 20000;
    while (!(RCC->CR & (1 << 17)) && --timeout);

    if (timeout > 0) {
        // Configure Flash latency: 2 wait states for 72 MHz + Prefetch buffer
        FLASH_ACR = 0x12;

        // AHB prescaler = 1, APB2 = 1, APB1 prescaler = /2 (36 MHz max)
        // PLL source = HSE (8 MHz), PLL Multiplier = 9 (8 MHz * 9 = 72 MHz)
        RCC->CFGR &= ~((0x0F << 4) | (0x07 << 8) | (0x07 << 11) | (0x0F << 18) | (1 << 16));
        RCC->CFGR |= (0x04 << 8) | (1 << 16) | (0x07 << 18);

        // Enable PLL and wait for lock
        RCC->CR |= (1 << 24);
        while (!(RCC->CR & (1 << 25)));

        // Select PLL as System Clock
        RCC->CFGR &= ~(0x03 << 0);
        RCC->CFGR |= (0x02 << 0);
        while (((RCC->CFGR >> 2) & 0x03) != 0x02);
    }
}

int main(void) {
    // Configure MCU clock to 72 MHz (Blue Pill standard)
    SystemClock_Config_72MHz();

    // Start ARM Cortex-M3 DWT Cycle Counter
    DWT_Init();

    // Enable GPIOC Clock (APB2 Bus)
    GPIOC_PCLK_EN();

    // Configure PC13 (Blue Pill Onboard LED) as Output Push-Pull 2MHz
    GPIO_Init(GPIOC, 13, GPIO_MODE_OUT_PP_2MHZ);

    // Initialize Bare-Metal USART2 @ 115200 Baud
    USART2_Init(115200);
    USART2_SendString("STM32F103 Blue Pill Bare-Metal Drivers Loaded!\r\n");

    while (1) {
        // Toggle PC13 LED (Active LOW on Blue Pill)
        GPIO_TogglePin(GPIOC, 13);
        
        for (volatile int i = 0; i < 500000; i++); // Delay
    }
}