#ifndef CYCLE_COUNTER_H
#define CYCLE_COUNTER_H

#include <stdint.h>

/* ARM Cortex-M3 Core Debug & DWT Registers */
#define CoreDebug_DEMCR  (*(volatile uint32_t*)0xE000EDFCUL)
#define DWT_CTRL         (*(volatile uint32_t*)0xE0001000UL)
#define DWT_CYCCNT       (*(volatile uint32_t*)0xE0001004UL)

/* Enable TRCENA bit in DEMCR */
#define CoreDebug_DEMCR_TRCENA_Msk (1UL << 24)

/* Enable CYCCNTENA bit in DWT_CTRL */
#define DWT_CTRL_CYCCNTENA_Msk     (1UL << 0)

/**
 * @brief  Initializes the ARM Cortex-M3 DWT Cycle Counter.
 * @note   Must be called once before taking cycle measurements.
 */
static inline void DWT_Init(void) {
    CoreDebug_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; /* Enable Trace System */
    DWT_CYCCNT = 0U;                               /* Reset Cycle Counter */
    DWT_CTRL |= DWT_CTRL_CYCCNTENA_Msk;            /* Enable Cycle Counter */
}

/**
 * @brief  Reads current CPU clock cycle count.
 * @retval 32-bit unsigned cycle count.
 */
static inline uint32_t DWT_GetCycles(void) {
    return DWT_CYCCNT;
}

/**
 * @brief  Resets CPU clock cycle count back to zero.
 */
static inline void DWT_ResetCycles(void) {
    DWT_CYCCNT = 0U;
}

/**
 * @brief  Converts clock cycles to microseconds based on CPU frequency.
 * @param  cycles Measured DWT cycles.
 * @param  cpu_freq_hz System core clock in Hz (e.g., 72000000UL for STM32F103).
 * @retval Time in microseconds (float).
 */
static inline float DWT_CyclesToMicroseconds(uint32_t cycles, uint32_t cpu_freq_hz) {
    return ((float)cycles * 1000000.0f) / (float)cpu_freq_hz;
}

#endif /* CYCLE_COUNTER_H */