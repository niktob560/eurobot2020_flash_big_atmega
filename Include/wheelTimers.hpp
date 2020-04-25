#include <stdio.h>
#include "api.hpp"

namespace wheelTimers
{
	extern uint64_t ticks0, 
					ticks1, 
					ticks2;

	void init();
	void stop();
	void setFreqs(uint8_t w0, uint8_t w1, uint8_t w2);
} // namespace wheelTimers
