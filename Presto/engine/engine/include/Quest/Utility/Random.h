#ifndef QUEST_UTILITY_RANDOM_H
#define QUEST_UTILITY_RANDOM_H

#include <Quest/Common.h>

u32 g_randomIntSeed = 0;

forceinline u32 randomInt()
{
	g_randomIntSeed = (214013 * g_randomIntSeed + 2531011);
	return (g_randomIntSeed >> 16) & 0x7FFF;
}

#endif