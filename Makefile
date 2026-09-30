CC ?= arm-none-eabi-gcc
OBJCOPY ?= arm-none-eabi-objcopy
SIZE ?= arm-none-eabi-size
MACH = cortex-m3

CFLAGS = -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -Wextra -O2 \
         -IDrivers/Inc -IBenchmarks -ffunction-sections -fdata-sections
ASFLAGS = -mcpu=$(MACH) -mthumb
LDFLAGS = -mcpu=$(MACH) -mthumb --specs=nano.specs -T stm32f103c8.ld \
          -Wl,-Map=build/final.map -Wl,--gc-sections

C_SRCS = App/main.c \
         Drivers/Src/stm32f1xx_gpio.c \
         Drivers/Src/stm32f1xx_exti.c \
         Drivers/Src/stm32f1xx_usart.c \
         Drivers/Src/stm32f1xx_spi.c \
         Drivers/Src/stm32f1xx_i2c.c \
         Drivers/Src/stm32f1xx_tim.c

ASM_SRCS = App/startup_stm32f103c8.s

OBJS = build/main.o \
       build/stm32f1xx_gpio.o \
       build/stm32f1xx_exti.o \
       build/stm32f1xx_usart.o \
       build/stm32f1xx_spi.o \
       build/stm32f1xx_i2c.o \
       build/stm32f1xx_tim.o \
       build/startup_stm32f103c8.o

all: build/final.elf build/final.bin build/final.hex
	@$(SIZE) build/final.elf 2>/dev/null || true

build:
	mkdir -p build

build/%.o: App/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: Drivers/Src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: App/%.s | build
	$(CC) $(ASFLAGS) -c $< -o $@

build/final.elf: $(OBJS) stm32f103c8.ld
	$(CC) $(LDFLAGS) $(OBJS) -o $@

build/final.bin: build/final.elf
	$(OBJCOPY) -O binary $< $@ 2>/dev/null || true

build/final.hex: build/final.elf
	$(OBJCOPY) -O ihex $< $@ 2>/dev/null || true

clean:
	rm -rf build