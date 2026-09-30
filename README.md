# STM32F1 Bare-Metal Peripheral Drivers & Interrupt Stack

![Language](https://img.shields.io/badge/Language-Embedded%20C-00599C.svg)
![Architecture](https://img.shields.io/badge/Architecture-ARM%20Cortex--M3-orange.svg)
![Target MCU](https://img.shields.io/badge/MCU-STM32F103C8T6-blue.svg)
![Vendor HAL](https://img.shields.io/badge/Vendor%20HAL-Zero%20Dependency-brightgreen.svg)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

A high-performance, register-level **Bare-Metal Driver Framework** written from scratch in Embedded C for the **STM32F103C8 ("Blue Pill" / ARM Cortex-M3)** microcontroller architecture, operating without vendor abstraction libraries (ST HAL or Standard Peripheral Library).

---

## 📌 Project Architecture & Objectives

Standard vendor HAL libraries introduce significant memory bloat and execution latency due to dynamic handle checks, deep call stacks, and multi-layer abstractions. 

This repository demonstrates **zero-overhead hardware control** by directly manipulating memory-mapped registers via `volatile` structure pointers, delivering:
- **Deterministic peripheral control** with minimal clock cycle execution overhead.
- **Microcontroller architectural insight**, mastering the unique STM32F1 register layout (`CRL`/`CRH` mode-cnf configuration fields and `APB2` GPIO bus mapping).
- **Strict static allocation**, eliminating dynamic heap memory (`malloc`) fragmentation in safety-critical firmware.

---

## 🏗️ Supported Peripherals & Driver Modules

| Peripheral Module | Header / Source | Key Architectural Features |
| :--- | :--- | :--- |
| **GPIO** | `stm32f1xx_gpio.h/.c` | 4-bit `MODE` + `CNF` configuration in `CRL` (Pins 0–7) and `CRH` (Pins 8–15), atomic bit setting via `BSRR` / `BRR`. |
| **EXTI & AFIO** | `stm32f1xx_exti.h/.c` | Line mapping using Alternate Function I/O (`AFIO`), rising/falling edge selection, `NVIC` vector mask enablement. |
| **USART** | `stm32f1xx_usart.h/.c` | Hardware baud rate generation (`BRR`), polling/interrupt-driven byte transmission and reception (`TXE`/`RXNE`). |
| **SPI** | `stm32f1xx_spi.h/.c` | Full-duplex Master mode, software/hardware NSS pin management, `fPCLK` clock prescaling. |
| **I2C** | `stm32f1xx_i2c.h/.c` | Master mode 100 kHz Standard-mode timing, START/STOP condition generation, ACK/NACK management. |
| **TIMERS & PWM** | `stm32f1xx_tim.h/.c` | Hardware prescaler (`PSC`), Auto-Reload Register (`ARR`), and PWM Mode 1 generation on capture/compare channels. |
| **DWT Profiler** | `cycle_counter.h` | ARM Cortex-M Data Watchpoint and Trace (`DWT`) cycle counter initialization for cycle-accurate firmware profiling. |

---

## 📊 Performance Benchmarks: Bare-Metal vs. ST HAL

All metrics were benchmarked on a physical **STM32F103C8 Blue Pill board (ARM Cortex-M3 @ 72 MHz)** compiled using `arm-none-eabi-gcc -O2`. Execution cycle counts were measured using the internal **DWT Cycle Counter**.

### Memory Footprint & Execution Latency

| Performance Metric | ST HAL Library | Our Bare-Metal Driver | Performance Optimization |
| :--- | :--- | :--- | :--- |
| **Flash Usage (`.text`)** | 4.82 KB | **2.84 KB** | **~41.0% Footprint Reduction** |
| **SRAM Usage (`.data` + `.bss`)** | 1.12 KB | **0.24 KB** | **~78.5% RAM Reduction** |
| **GPIO Pin Toggle Overhead** | 28 Clock Cycles | **6 Clock Cycles** | **~78.5% Faster Execution** |
| **EXTI Interrupt Latency** | 42 Clock Cycles | **14 Clock Cycles** | **~66.6% Faster ISR Response** |

---

## 📂 Repository Structure

```text
stm32f1xx-baremetal-drivers/
├── App/
│   ├── main.c                     # Demonstration app targeting PC13 (Blue Pill LED)
│   └── startup_stm32f103c8.s      # GNU Assembly vector table & reset handler
├── Benchmarks/
│   ├── benchmark_results.md       # Detailed profiling data and execution comparisons
│   └── cycle_counter.h            # ARM Cortex-M DWT cycle benchmarking tool
├── Drivers/
│   ├── Inc/                       # Master memory map & peripheral API headers
│   │   ├── stm32f1xx.h            # Peripheral base addresses & register structs
│   │   ├── stm32f1xx_gpio.h
│   │   ├── stm32f1xx_exti.h
│   │   ├── stm32f1xx_usart.h
│   │   ├── stm32f1xx_spi.h
│   │   ├── stm32f1xx_i2c.h
│   │   └── stm32f1xx_tim.h
│   └── Src/                       # Register-level C implementations
│       ├── stm32f1xx_gpio.c
│       ├── stm32f1xx_exti.c
│       ├── stm32f1xx_usart.c
│       ├── stm32f1xx_spi.c
│       ├── stm32f1xx_i2c.c
│       └── stm32f1xx_tim.c
├── Makefile                       # Cross-compilation script (Arm GNU Toolchain)
├── LICENSE                        # MIT License
└── README.md                      # Project documentation


This repository contains clean, modular, register-level drivers for the most commonly used STM32F1 peripherals:

- GPIO  
- EXTI + NVIC interrupts  
- USART  
- SPI  
- I2C  
- Timer / PWM  

The goal is simple: give full control of the microcontroller with the smallest possible code size and the lowest possible execution overhead.

By writing drivers at the register level, this project achieves:

1. **Much smaller binary size**
2. **Faster execution** (fewer clock cycles per operation)
3. **Complete transparency** — every bit written to a register is visible in the code
4. **Better learning** of ARM Cortex-M3 and STM32F1 architecture

This approach is preferred in resource-constrained, real-time, and safety-critical firmware.

---

## How It Works

All peripherals are controlled through C structures that map directly onto the microcontroller’s memory-mapped registers.

Example (GPIO atomic write using BSRR/BRR):

```c
void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if (Value)
        pGPIOx->BSRR = (1U << PinNumber);   // Atomic set
    else
        pGPIOx->BRR  = (1U << PinNumber);   // Atomic reset
}