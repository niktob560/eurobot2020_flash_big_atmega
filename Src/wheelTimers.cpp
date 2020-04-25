#include "wheelTimers.hpp"

namespace wheelTimers
{
	uint64_t 	ticks0 = 0, 
				ticks1 = 0, 
				ticks2 = 0;

	void init();
	void stop();
	void setFreqs(uint8_t w0, uint8_t w1, uint8_t w2);
} // namespace wheelTimers
