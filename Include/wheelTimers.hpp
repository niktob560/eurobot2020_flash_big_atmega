#include <stdio.h>
#include "avr-api/Include/api.hpp"

namespace wheelTimers
{
	extern uint64_t ticks0, 
					ticks1, 
					ticks2;
	extern const uint64_t baseFreq;

	void init();
	void stop();
	void setDelays(uint16_t w0, uint16_t w1, uint16_t w2);
} // namespace wheelTimers
