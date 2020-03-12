MAINFILENAME=main
MCU=atmega2560
OPTIMIZE=-Os
XTAL=16000000

INCLUDES=-IInclude -I.
CFLAGS=-c $(OPTIMIZE) $(INCLUDES) -Wno-write-strings -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wduplicated-branches -Wduplicated-cond -Wextra-semi -Wfloat-equal -Wlogical-op -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Werror -Wall -Wextra -Wpedantic -std=gnu++14 -pedantic-errors -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -fno-devirtualize -fno-use-cxa-atexit -mmcu=$(MCU) -DF_CPU=$(XTAL)
LFLAGS=$(OPTIMIZE) $(INCLUDES) -Wno-write-strings -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wduplicated-branches -Wduplicated-cond -Wextra-semi -Wfloat-equal -Wlogical-op -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wall -Wextra -Wpedantic -pedantic-errors -flto -fuse-linker-plugin -ffunction-sections -fdata-sections -Wl,--gc-sections -mmcu=$(MCU) -lm


all: size

Build/main.o:
	avr-g++ $(CFLAGS) "Src/main.cpp" -o "Build/main.o"

Build/core.a:
	cd avr-api && make lib && cp Build/core.a ../Build/core.a && cd ..

clean_avr-api:
	cd avr-api && make clean && cd ..

clean: clean_avr-api
	rm -rf Build/*

link: Build/main.o Build/core.a
	avr-gcc $(LFLAGS) Build/main.o Build/core.a -o Build/main.elf

objcopy: link
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "Build/$(MAINFILENAME).elf" "Build/$(MAINFILENAME).eep"
	avr-objcopy -O ihex -R .eeprom  "Build/$(MAINFILENAME).elf" "Build/$(MAINFILENAME).hex"


size: objcopy
	@echo -e '\033[0;36m'
	@avr-size Build/$(MAINFILENAME).elf -C --mcu=$(MCU)
	@echo -e '\033[0m'
