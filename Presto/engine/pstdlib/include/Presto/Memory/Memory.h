#ifndef PRESTO_MEMORY_MEMORY_H
#define PRESTO_MEMORY_MEMORY_H

#include <Presto/Common.h>
#include <stdlib.h>

typedef usize vol;
static const vol defaultAlignment = 4;
static const vol notTracked = (vol)(-1);
static const vol paddingValue = (vol)(-1);

extern vol totalHeapAllocatedSpace;
extern vol totalheapAllocationCount;
extern b8 heapMutex;

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

PSTDLIB_EXPORT void* heapAllocate(vol size, vol alignment);

PSTDLIB_EXPORT MemoryHeader* getHeader(const void* data);

PSTDLIB_EXPORT void heapDeallocate(void* pointer);

PSTDLIB_EXPORT vol heapAllocatedSize(void* pointer);

#ifdef PRESTO_SYSTEM_WINDOWS
#define conjure _alloca
#else
// TODO(Preston): Other systems conjure functions.
#endif

#define spawn(x) heapAllocate(x, defaultAlignment)
#define murder heapDeallocate

#endif
