#include <stdio.h>
#include "avr-api/Include/api.hpp"
#include "avr-log/Include/logger.hpp"
#include "scheduler/Include/schedule.hpp"
#include "mcuterminaltranslator/Inc/translator.hpp"

uint64_t sysTime = 0;

uint8_t getSysTime()
{
	return static_cast<uint8_t>(sysTime);
}

void once();

void foo()
{
	gpio::setState(&PORTB, {PB7, gpio::TOGGLE});
}

void wait()
{
	asm("NOP");
}

void once2();

void once()
{
	usart::println("\t\tONCE");
	Log::debug(Log::Importance::Optional, "hello");
	Log::info(Log::Importance::Optional, "world");
	schedule::addOnceTask({once2, 1});
}

void once2()
{
	usart::println("\t\tONCE2");

	Log::dump(Log::Importance::Optional);

}

int main()
{
	usart::begin(115200);
	gpio::setMode(&PORTB, PB7, gpio::OUTPUT);
	schedule::addTask({foo, 1});
	schedule::addOnceTask({once, 1});
	interrupt::set(interrupt::TC0_COMPA, schedule::schedule);
	TIMER0Init(TIMER0_COMA_NPWM_NORMAL, TIMER0_WF_CTC, TIMER0_CLK_SRC_1024);
	TIMER0EnableCOMPAInterrupt();
	TIMER0SetA(255);
	Log::defaultDumpFunc = [](const unsigned char* c)
							{
								usart::println(static_cast<int>(*c));
								usart::println(c + 1);
							};
	sei();
	long i = 0;
	usart::println();
	while(1)
	{
		usart::print("NICE");	
		usart::println(i);
		i++;
		delay(200);
	}
    return 0;
}
