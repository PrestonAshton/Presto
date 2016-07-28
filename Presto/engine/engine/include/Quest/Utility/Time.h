#ifndef QUEST_UTILITY_TIME_H
#define QUEST_UTILITY_TIME_H

#include <Quest/Common.h>

typedef struct
{
	i64 microseconds;
} Time;

// We kinda need 64 bits for this if we want to have time that is over 24 hours or whatever;
// Not that we would need that... but you never know! The main focus is x64 processors too so...
// Do we want negative time o:
// Gonna say yes for now!

void TimeInit(void);

INITIALIZER(TimeInit);

Time TimeNow(void);
void TimeSleep(Time time);

forceinline f32 TimeAsSeconds(Time time)
{
	return time.microseconds / 1000000.0f;
}

forceinline i32 TimeAsMilliseconds(Time time)
{
	return time.microseconds / 1000;
}

forceinline i64 TimeAsMicroseconds(Time time)
{
	return time.microseconds;
}

forceinline Time TimeFromSeconds(f32 amount)
{
	return (Time) { amount * 1000000 };
}

forceinline Time TimeFromMilliseconds(i32 amount)
{
	return (Time) { amount * 1000 };
}

forceinline Time TimeFromMicroseconds(i64 amount)
{
	return (Time) { amount };
}

#endif