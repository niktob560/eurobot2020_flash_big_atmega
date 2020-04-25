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

Build/wheelTimers.o:
	avr-g++ $(CFLAGS) "Src/wheelTimers.cpp" -o "Build/wheelTimers.o"

Build/core.a:
	cd avr-api && make lib && cp Build/core.a ../Build/core.a && cd ..

Build/libscheduler.a:
	cd scheduler && mkdir -p Build && cd Build && cmake -DCMAKE_TOOLCHAIN_FILE=../cmake-avr/generic-gcc-avr.cmake .. && make scheduler && cp libscheduler-${MCU}.a ../../Build/libscheduler.a && cd ../../

Build/libavrlog.a:
	cd avr-log && mkdir -p Build && cd Build && cmake -DCMAKE_TOOLCHAIN_FILE=../cmake-avr/generic-gcc-avr.cmake .. && make avr-log && cp libavr-log-${MCU}.a ../../Build/libavrlog.a && cd ../../

Build/libtranslator.o:
	cd mcuterminaltranslator && make Build/translator.o && cp Build/translator.o ../Build/libtranslator.o && cd ..

clean_avr-api:
	cd avr-api && make clean && cd ../

clean_scheduler:
	cd scheduler/Build && make clean && cd ../../

clean_avrlog:
	cd avr-log/Build && make clean && cd ../../

clean_translator:
	cd mcuterminaltranslator && make clean && cd ..

clean: clean_avr-api clean_scheduler clean_avrlog clean_translator
	rm -rf Build/*

link: Build/main.o Build/wheelTimers.o Build/core.a Build/libscheduler.a Build/libavrlog.a Build/libtranslator.o
	avr-gcc $(LFLAGS) Build/wheelTimers.o Build/main.o Build/core.a Build/libscheduler.a Build/libavrlog.a Build/libtranslator.o -o Build/main.elf

objcopy: link
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "Build/$(MAINFILENAME).elf" "Build/$(MAINFILENAME).eep"
	avr-objcopy -O ihex -R .eeprom  "Build/$(MAINFILENAME).elf" "Build/$(MAINFILENAME).hex"


size: objcopy
	@echo -e '\033[0;36m'
	@avr-size Build/$(MAINFILENAME).elf -C --mcu=$(MCU)
	@echo -e '\033[0m'
