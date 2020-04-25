#include "wheelTimers.hpp"

namespace wheelTimers
{
	uint64_t 	ticks0 = 0, 
				ticks1 = 0, 
				ticks2 = 0;

	extern const uint64_t baseFreq = (160000000L) / 256;

	void init()
	{
		TIMER3Init(TIMER3_COMA_TOGGLE | TIMER3_COMB_TOGGLE | TIMER3_COMC_TOGGLE, TIMER3_WF_CTC_TOPICR3, TIMER3_CLK_SRC_256);
		TIMER3SetA(0);
		TIMER3SetB(0);
		TIMER3SetC(0);
	}

	void stop()
	{
		TIMER3SetA(0);
		TIMER3SetB(0);
		TIMER3SetC(0);
	}

	void setTicks(uint16_t w0, uint16_t w1, uint16_t w2)
	{
		TIMER3SetA(w0);
		TIMER3SetB(w1);
		TIMER3SetC(w2);
	}
} // namespace wheelTimers
