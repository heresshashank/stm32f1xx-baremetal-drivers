#ifndef STM32F1XX_H
#define STM32F1XX_H

#include <stdint.h>

#define __VO volatile

/* Memory Base Addresses */
#define FLASH_BASEADDR      0x08000000UL
#define SRAM_BASEADDR       0x20000000UL
#define PERIPH_BASE         0x40000000UL

#define APB1PERIPH_BASE     PERIPH_BASE
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE      (PERIPH_BASE + 0x00020000UL)

/* APB2 Peripherals (STM32F1 GPIOs and AFIO are on APB2!) */
#define AFIO_BASE           (APB2PERIPH_BASE + 0x0000UL)
#define EXTI_BASE           (APB2PERIPH_BASE + 0x0400UL)
#define GPIOA_BASE          (APB2PERIPH_BASE + 0x0800UL)
#define GPIOB_BASE          (APB2PERIPH_BASE + 0x0C00UL)
#define GPIOC_BASE          (APB2PERIPH_BASE + 0x1000UL)
#define SPI1_BASE           (APB2PERIPH_BASE + 0x3000UL)
#define USART1_BASE         (APB2PERIPH_BASE + 0x3800UL)

/* APB1 Peripherals */
#define TIM2_BASE           (APB1PERIPH_BASE + 0x0000UL)
#define SPI2_BASE           (APB1PERIPH_BASE + 0x3800UL)
#define USART2_BASE         (APB1PERIPH_BASE + 0x4400UL)
#define I2C1_BASE           (APB1PERIPH_BASE + 0x5400UL)

/* AHB Peripherals */
#define RCC_BASE            (AHBPERIPH_BASE + 0x1000UL)
#define FLASH_R_BASE        (AHBPERIPH_BASE + 0x2000UL)
#define FLASH_ACR           (*((__VO uint32_t*)(FLASH_R_BASE + 0x00UL)))

/* NVIC Interrupt Set Enable Registers */
#define NVIC_ISER0          ((__VO uint32_t*)0xE000E100UL)
#define NVIC_ISER1          ((__VO uint32_t*)0xE000E104UL)

/* Peripheral Register Structures */
typedef struct {
    __VO uint32_t CRL;      /* Port Configuration Register Low  (Pins 0-7)  */
    __VO uint32_t CRH;      /* Port Configuration Register High (Pins 8-15) */
    __VO uint32_t IDR;      /* Input Data Register                          */
    __VO uint32_t ODR;      /* Output Data Register                         */
    __VO uint32_t BSRR;     /* Bit Set/Reset Register                       */
    __VO uint32_t BRR;      /* Bit Reset Register                           */
    __VO uint32_t LCKR;     /* Configuration Lock Register                  */
} GPIO_RegDef_t;

typedef struct {
    __VO uint32_t CR;
    __VO uint32_t CFGR;
    __VO uint32_t CIR;
    __VO uint32_t APB2RSTR;
    __VO uint32_t APB1RSTR;
    __VO uint32_t AHBENR;
    __VO uint32_t APB2ENR;
    __VO uint32_t APB1ENR;
    __VO uint32_t BDCR;
    __VO uint32_t CSR;
} RCC_RegDef_t;

typedef struct {
    __VO uint32_t EVCR;
    __VO uint32_t MAPR;
    __VO uint32_t EXTICR[4];
    __VO uint32_t MAPR2;
} AFIO_RegDef_t;

typedef struct {
    __VO uint32_t IMR;
    __VO uint32_t EMR;
    __VO uint32_t RTSR;
    __VO uint32_t FTSR;
    __VO uint32_t SWIER;
    __VO uint32_t PR;
} EXTI_RegDef_t;

/* Peripheral Pointers */
#define GPIOA   ((GPIO_RegDef_t*) GPIOA_BASE)
#define GPIOB   ((GPIO_RegDef_t*) GPIOB_BASE)
#define GPIOC   ((GPIO_RegDef_t*) GPIOC_BASE)
#define RCC     ((RCC_RegDef_t*) RCC_BASE)
#define AFIO    ((AFIO_RegDef_t*) AFIO_BASE)
#define EXTI    ((EXTI_RegDef_t*) EXTI_BASE)

/* Clock Enable Macros */
#define GPIOA_PCLK_EN()   (RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN()   (RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN()   (RCC->APB2ENR |= (1 << 4))
#define AFIO_PCLK_EN()    (RCC->APB2ENR |= (1 << 0))
#define USART1_PCLK_EN()  (RCC->APB2ENR |= (1 << 14))
#define USART2_PCLK_EN()  (RCC->APB1ENR |= (1 << 17))
#define SPI1_PCLK_EN()    (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()    (RCC->APB1ENR |= (1 << 14))
#define I2C1_PCLK_EN()    (RCC->APB1ENR |= (1 << 21))
#define TIM2_PCLK_EN()    (RCC->APB1ENR |= (1 << 0))

#endif