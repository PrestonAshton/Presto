#ifndef QUEST_MEMORY_MEMORY_H
#define QUEST_MEMORY_MEMORY_H

#include <Quest/Common.h>

typedef usize vol;
#define defaultAlignment (vol)(4)
#define notTracked (vol)(-1)
#define paddingValue (vol)(-1)

extern vol totalHeapAllocatedSpace;
extern vol totalheapAllocationCount;
extern b8 heapMutex;

forceinline void copyMemory(const void* from, void* to, usize length)
{
	while (length--)
	{
		*((u8*)to) = *((u8*)from);
		#ifdef QUEST_COMPILER_MSVC
		((u8*)(to))++;
		((u8*)(from))++;
		#else
		to++;
		from++;
		#endif

		//*((u8*)to)++ = *((u8*)from)++;
		// doesn't work on GCC/Clang, this is a more cross-platform friendly method.
	}
}

typedef struct
{
  vol size;
} MemoryHeader;

forceinline void* alignForward(void* pointer, vol alignment)
{
  uptr castedPointer = (uptr)pointer;
  const vol alignmentModulus = castedPointer % alignment;
  if (alignmentModulus)
    castedPointer += (uptr)(alignment - alignmentModulus);
  return((void*)castedPointer);
}

void* heapAllocate(vol size, vol alignment);

MemoryHeader* getHeader(const void* data);

void heapDeallocate(void* pointer);

vol heapAllocatedSize(void* pointer);

#ifdef QUEST_SYSTEM_WINDOWS
#define conjure _alloca
#else
// TODO(Questn): Other systems conjure functions.
#define conjure alloca
#endif

#define _spawn(x, y) heapAllocate(x, y)
#define spawn(x) _spawn(x, defaultAlignment)
#define murder heapDeallocate

#endif
