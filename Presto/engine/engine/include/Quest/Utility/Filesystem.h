#ifndef QUEST_UTILITY_FILESYSTEM_H
#define QUEST_UTILITY_FILESYSTEM_H

void* ReadEntireFile(const a8* filename);
void* ReadEntireTextFile(const a8* filename);

void OpenEngineLock(void);
void CloseEngineLock(void);


#endif
