#include <stdio.h>
#include "api.hpp"

namespace wheelTimers
{
	extern uint64_t ticks0, 
					ticks1, 
					ticks2;
	extern const uint64_t baseFreq;

	void init();
	void stop();
	void setFreqs(uint64_t w0, uint64_t w1, uint64_t w2);
} // namespace wheelTimers
