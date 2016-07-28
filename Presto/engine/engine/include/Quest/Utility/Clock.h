#ifndef QUEST_UTILITY_CLOCK_H
#define QUEST_UTILITY_CLOCK_H

#include <Quest/Common.h>
#include <Quest/Utility/Time.h>

typedef struct
{
	Time startTime;
} Clock;

forceinline Clock ClockCreate(void)
{
	return (Clock){ TimeNow() };
}

forceinline Time ClockGetElapsedTime(Clock clock)
{
	return TimeFromMicroseconds(TimeNow().microseconds - clock.startTime.microseconds);
}

forceinline Clock ClockRestartNewClock(Clock clock)
{
	Time now = TimeNow();
	Time elapsed = TimeFromMicroseconds(now.microseconds - clock.startTime.microseconds);
	clock.startTime = now;

	return clock;
}

forceinline Time ClockRestart(Clock* clock)
{
	Time now = TimeNow();
	Time elapsed = TimeFromMicroseconds(now.microseconds - clock->startTime.microseconds);
	clock->startTime = now;

	return elapsed;
}

#endif