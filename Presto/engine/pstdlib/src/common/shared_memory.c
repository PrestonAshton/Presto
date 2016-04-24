vol totalHeapAllocatedSpace = 0;
vol totalheapAllocationCount = 0;
b8 heapMutex = false;

void* heapAllocate(vol size, vol alignment)
{
	LOCK_MUTEX(heapMutex);
	const vol total = size + alignment + sizeof(MemoryHeader);
	MemoryHeader* header = (MemoryHeader*)malloc(total);
	header->size = total;

	MemoryHeader* headerPlusOne = (MemoryHeader*)header + 1;
	void* ptr = alignForward(headerPlusOne, alignment);
	// Padding
	vol* headerPtr = (vol*)(headerPlusOne);
	while (headerPtr != ptr)
		*headerPtr++ = paddingValue;

	totalHeapAllocatedSpace += total;
	totalheapAllocationCount++;

	UNLOCK_MUTEX(heapMutex);
	return(ptr);
}

MemoryHeader* getHeader(const void* data)
{
	const vol* ptr = (vol*)data;
	ptr--;

	while (*ptr == paddingValue)
		ptr--;

	return((MemoryHeader*)ptr);
}

void heapDeallocate(void* pointer)
{
	if (pointer == NULL)
		return;

	LOCK_MUTEX(heapMutex);
	MemoryHeader* head = getHeader(pointer);
	totalHeapAllocatedSpace -= head->size;
	totalheapAllocationCount--;

	free(head);
	UNLOCK_MUTEX(heapMutex);
}
vol heapAllocatedSize(void* pointer)
{
	return(getHeader(pointer)->size);
}