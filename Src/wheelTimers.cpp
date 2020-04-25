#include "wheelTimers.hpp"

namespace wheelTimers
{
	uint64_t 	ticks0 = 0, 
				ticks1 = 0, 
				ticks2 = 0;

	uint16_t	spd0 = 0,
				spd1 = 0,
				spd2 = 0;

	extern const uint64_t baseFreq = (160000000L) / 256;

	inline void updateA()
	{
		TIMER3SetA(spd0);
	}
	inline void updateB()
	{
		TIMER3SetB(spd1);
	}
	inline void updateC()
	{
		TIMER3SetC(spd2);
	}

	inline void updateSpeeds()
	{
		updateA();
		updateB();
		updateC();
	}

	void _COMA_ISR()
	{
		ticks0++;
		TIMER3SetA(spd0);
	}
	void _COMB_ISR()
	{
		ticks1++;
		TIMER3SetB(spd1);
	}
	void _COMC_ISR()
	{
		ticks2++;
		TIMER3SetC(spd2);
	}

	void init()
	{
		TIMER3Init(TIMER3_COMA_TOGGLE | TIMER3_COMB_TOGGLE | TIMER3_COMC_TOGGLE, TIMER3_WF_CTC_TOPICR3, TIMER3_CLK_SRC_256);
		setDelays(0, 0, 0);
		interrupt::set(interrupt::TC3_COMPA, _COMA_ISR);
		interrupt::set(interrupt::TC3_COMPB, _COMB_ISR);
		interrupt::set(interrupt::TC3_COMPC, _COMC_ISR);
		TIMER3EnableCOMPAInterrupt();
		TIMER3EnableCOMPBInterrupt();
		TIMER3EnableCOMPCInterrupt();
	}

	void stop()
	{
		setDelays(0, 0, 0);
	}

	void setDelays(uint16_t w0, uint16_t w1, uint16_t w2)
	{
		if(!spd0)
		{
			spd0 = w0;
			updateA();
		}
		else
			spd0 = w0;

		if(!spd1)
		{
			spd1 = w1;
			updateB();
		}
		else
			spd1 = w1;

		if(!spd2)
		{
			spd2 = w2;
			updateC();
		}
		else
			spd2 = w2;
	}
} // namespace wheelTimers
