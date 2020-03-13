#include <stdio.h>
#include "avr-api/Include/api.hpp"
#include "scheduler/Include/schedule.hpp"

void foo()
{
	gpio::setState(&PORTB, {PB1, gpio::TOGGLE});
}

int main()
{
	gpio::setMode(&PORTB, PB1, gpio::OUTPUT);
	schedule::addFunc(foo);
	while(1)
	{
		schedule::schedule();
		delay(50);
	}
    return 0;
}