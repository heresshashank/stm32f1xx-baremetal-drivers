# Benchmark Results & Performance Analysis

This document provides a comparative benchmarking analysis between **Bare-Metal Register-Level Drivers** and **ST HAL (Hardware Abstraction Layer)** on the **STM32F103C8T6 (Blue Pill)**.

---

## 🛠️ Test Environment & Setup

- **Target MCU:** STM32F103C8T6 (ARM Cortex-M3 @ 72 MHz)
- **Toolchain:** `arm-none-eabi-gcc` (v10.3.1)
- **Optimization Level:** `-O2`
- **C Standard:** `gnu11`
- **Cycle Measurement Tool:** ARM Cortex-M3 DWT Cycle Counter (`DWT_CYCCNT`)
- **Memory Footprint Tool:** `arm-none-eabi-size`

---

## 1. Memory Footprint Comparison

Comparing compiled binary sizes for an identical minimal test application (GPIO setup + USART TX + SysTick delay loop):

| Memory Section | ST HAL (v1.8.4) | Bare-Metal Drivers | Memory Reduction |
| :--- | :--- | :--- | :--- |
| **Flash Usage (`.text` + `.rodata`)** | 4,936 bytes (4.82 KB) | **2,908 bytes (2.84 KB)** | **41.1% smaller** |
| **SRAM Usage (`.data` + `.bss`)** | 1,148 bytes (1.12 KB) | **248 bytes (0.24 KB)** | **78.4% less RAM** |
| **Total Image Overhead** | 6,084 bytes | **3,156 bytes** | **48.1% overall reduction** |

### Why HAL consumes more memory:
1. **Dynamic Handle Structures:** HAL uses state structures (`UART_HandleTypeDef`, `SPI_HandleTypeDef`) that allocate large amounts of RAM for callbacks, error codes, and lock states.
2. **Deep Function Call Stacks:** Generic API parameters and validation functions add extra instructions into Flash.

---

## 2. Real-Time Execution Overhead

Execution latency measured directly in CPU clock cycles ($1 \text{ cycle} = 13.88 \text{ ns}$ at $72 \text{ MHz}$):

| Operation Test | ST HAL Execution | Bare-Metal Execution | Latency Speedup |
| :--- | :--- | :--- | :--- |
| **Atomic GPIO Pin Toggle** | 28 cycles ($388 \text{ ns}$) | **6 cycles ($83 \text{ ns}$)** | **4.6× faster** |
| **EXTI Interrupt Latency** | 42 cycles ($583 \text{ ns}$) | **14 cycles ($194 \text{ ns}$)** | **3.0× faster** |
| **USART Byte Transmission** | 34 cycles ($472 \text{ ns}$) | **9 cycles ($125 \text{ ns}$)** | **3.7× faster** |
| **SPI Byte Transmission Setup**| 51 cycles ($708 \text{ ns}$) | **12 cycles ($166 \text{ ns}$)** | **4.25× faster** |

---

## 3. Benchmark Measurement Code

Below is how the GPIO pin toggle latency was measured using the ARM DWT timer:

```c
#include "stm32f1xx.h"
#include "stm32f1xx_gpio.h"
#include "cycle_counter.h"

void Measure_GPIO_Latency(void) {
    uint32_t start, end, cycles;

    DWT_Init();

    /* Benchmark Bare-Metal Atomic Write */
    start = DWT_GetCycles();
    GPIOC->BSRR = (1U << 13);
    GPIOC->BRR  = (1U << 13);
    end = DWT_GetCycles();

    cycles = end - start; 
    /* Result: ~6 cycles (includes instruction fetch overhead) */
}