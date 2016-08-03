#ifndef QUEST_EASTEREGGS_DIARY_H
#define QUEST_EASTEREGGS_DIARY_H

#include <Quest/Common.h>

const a8* diaryEntry01 = "19/07/2016 - Entry 1:\nI am starting to get extremely tired of programming these stupid hashmaps now. Debugging these ridiculously long macros is starting to get on my nerves. I wish I could move onto something else, but I can't as everything else requires this... Hopefully it will be all over soon.\n";
const a8* diaryEntry02 = "19/07/2016 - Entry 2:\nSo I have finally got around to finishing the hashmaps now. The main problem was that I was getting the address of a pointer... when I just needed to pass the pointer to copyMemory. I'm an idiot, but yay, everything works! ^_^\n";

QUEST_EXPORT void HiddenFeature()
{
	OutputDebugStringA(diaryEntry01);
	OutputDebugStringA(diaryEntry02);
}

#endif