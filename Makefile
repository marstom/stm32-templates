CC=arm-none-eabi-gcc

OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g3 -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -Iinc -Ilib -Ilib/inc
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals

ST_SRCS = ./src/stm32f4xx_it.c ./src/system_stm32f4xx.c ./lib/startup_stm32f4xx.s

# build stm32 library
lib:
	$(MAKE) -C lib

flash:
	st-flash write program.bin 0x8000000

clean:
	rm -f *.elf
	rm -f *.hex
	rm -f *.bin

clean_all: clean
	$(MAKE) -C lib clean


.PHONY: lib


# Programs rules

01lcd:
	$(CC) $(CFLAGS) 01LCD/lcd.c $(ST_SRCS) -Llib -lstm32f4 -o program.elf
	$(OBJCOPY) -O ihex program.elf program.hex
	$(OBJCOPY) -O binary program.elf program.bin

02lcd:
	$(CC) $(CFLAGS) 02LCD2/lcd.c $(ST_SRCS) -Llib -lstm32f4 -o program.elf
	$(OBJCOPY) -O ihex program.elf program.hex
	$(OBJCOPY) -O binary program.elf program.bin

00leds:
	$(CC) $(CFLAGS) 00Leds/leds_example.c $(ST_SRCS) -Llib -lstm32f4 -o program.elf
	$(OBJCOPY) -O ihex program.elf program.hex
	$(OBJCOPY) -O binary program.elf program.bin