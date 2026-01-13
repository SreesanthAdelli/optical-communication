# Toolchain
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Compiler and linker flags
CFLAGS  = -mcpu=cortex-m4 -mthumb -O0 -g -Wall -ffreestanding -Iinclude
LDFLAGS = -TSTM32F446RE.ld -nostartfiles -Wl,-Map=output.map -nostdlib

# Sources
SRC     = src/startup.c src/main.c src/GPIO.c src/clock.c src/decode.c src/sysinit.c src/timer.c src/pwm.c
TARGET  = firmware
BIN     = $(TARGET).bin
ELF     = $(TARGET).elf

# Default target: build binary
all: $(BIN)

# Build ELF and binary
$(BIN): $(SRC) STM32F446RE.ld
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(ELF)
	$(OBJCOPY) -O binary $(ELF) $(BIN)

# Flash target using ST-Link
flash: $(BIN)
	st-flash write $(BIN) 0x08000000

# Clean build artifacts
clean:
	rm -f *.o *.elf *.bin output.map
