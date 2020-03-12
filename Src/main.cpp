#include <stdio.h>
#include "avr-api/Include/api.hpp"

int main()
{
	gpio::setMode(&PORTB, PB1, gpio::OUTPUT);
    return 0;
}