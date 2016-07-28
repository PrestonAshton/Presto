#ifndef QUEST_UTILITY_TICKCOUNTER_H
#define QUEST_UTILITY_TICKCOUNTER_H

#include <Quest/Common.h>
#include <Quest/Utility/Time.h>
#include <Quest/Utility/Clock.h>

typedef struct
{
	f64 tickRate;
	Clock clock;
	usize tick;
} TickCounter;

TickCounter TickCounterCreate(void)
{
	return (TickCounter) { 0, ClockCreate(), 0 };
}

b8 TickCounterUpdate(TickCounter* counter, Time period)
{
	b8 reset = false;
	Time elapsedTime = ClockGetElapsedTime(counter->clock);
	if (elapsedTime.microseconds >= period.microseconds)
	{
		counter->tickRate = ((f64)(counter->tick)) * (1.0f / TimeAsSeconds(period));
		counter->tick = 0;
		reset = true;
		ClockRestart(&(counter->clock));
		// Use newclock maybe?
	}

	counter->tick++;
	return reset;
}

#endif