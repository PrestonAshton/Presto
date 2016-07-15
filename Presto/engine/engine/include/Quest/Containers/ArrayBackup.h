// OLD STYLE ARRAY! OLD!!!!!!!
// use me for reference only


#if 0

#ifndef PSTDLIB_CONTAINERS_ARRAY_H
#define PSTDLIB_CONTAINERS_ARRAY_H

#include <Quest/Common.h>

typedef struct
{
	void* data;

#ifdef QUEST_ARCHITECTURE_x32
	u32 _padding;
#endif

	u32 length;
	u32 capacity;

	u16 objectSize;

	u16 __padding;
	u64 ___padding;
} Array;

// <-- Array | 256 bits | 32 bytes -->
// Test this.
STATIC_ASSERT(sizeof(Array) == 32, Size_Of_Array);


#define ArrayCreateNonCast(x) \
	{0, 0, sizeof(x), 0}

#define ArrayCreate(x) \
	(Array){0, 0, sizeof(x), 0}

// returns an array*
#define ArrayCreateFixed(x, size) \
	Array* __array = spawn(sizeof(Array) + (size * sizeof(x))); \
	*__array = ArrayCreate(x); \
	__array->data = __array + 1; \
	__array

//usize ArraySize(const Array* a);
void ArrayEquals(Array* a, const Array* b);
void ArrayPushBack(Array* a, const void* item);
void ArrayDele(Array* a);
b8 ArrayEmpty(const Array* a);
void* ArrayBegin(Array* a);
void* ArrayEnd(Array* a);
void* ArrayBack(Array* a);
void ArrayClear(Array* a);
void ArrayTrim(Array* a);
usize ArrayAppend(Array* a, const void* items, usize count);
void ArrayResize(Array* a, usize length);
void ArraySetCapacity(Array* a, usize capacity);
void ArrayReserve(Array* a, usize capacity);
void ArrayGrow(Array* a, usize minCapacity);

#define ArrayGet(array, index) \
	((void*)((u8*)((array)->data) + (index * (array)->objectSize))) \

#define ArrayGetType(array, index, type) \
	(( type *)((u8*)((array)->data) + (index * (array)->objectSize))) \

#define ArrayGetValue(array, index, type) \
	*((( type *)((u8*)((array)->data) + (index * (array)->objectSize)))) \

forceinline usize ArraySize(const Array* a)
{
	return(a->length * a->objectSize);
}

forceinline void ArrayEquals(Array* a, const Array* b)
{
	ArrayResize(a, b->length);
	copyMemory(b->data, a->data, ArraySize(b));
}

forceinline void ArrayPushBack(Array* a, const void* item)
{
	if (a->length == a->capacity)
		ArrayGrow(a, 0);

	copyMemory(item, ArrayGet(a, a->length++), a->objectSize);
}

forceinline void ArrayDele(Array* a)
{
	Assert(a->length > 0);
	a->length--;
}

forceinline b8 ArrayEmpty(const Array* a)
{
	return(a->length == 0);
}

forceinline void* ArrayBegin(Array* a)
{
	return(a->data);
}

forceinline void* ArrayEnd(Array* a)
{
	return((i8*)(a->data) + ArraySize(a));
}

forceinline void* ArrayBack(Array* a)
{
	return((i8*)(a->data) + ArraySize(a) - a->objectSize);
}

forceinline void ArrayClear(Array* a)
{
	ArrayResize(a, 0);
}

forceinline void ArrayTrim(Array* a)
{
	ArraySetCapacity(a, a->length);
}

forceinline usize ArrayAppend(Array* a, const void* items, usize count)
{
	if (a->capacity <= a->length + count)
		ArrayGrow(a, a->length + count);

	memcpy((i8*)(a->data) + ArraySize(a), items, count * a->objectSize);
	return(a->length += count);
}

forceinline void ArrayResize(Array* a, usize length)
{
	if (length > a->capacity)
		ArrayGrow(a, length);

	a->length = length;
}

forceinline void ArraySetCapacity(Array* a, usize capacity)
{
	if (capacity == a->capacity)
		return;

	if (capacity < a->length)
		ArrayResize(a, capacity);

	void* data = NULL;
	data = spawn(capacity * a->objectSize);
	memcpy(data, a->data, ArraySize(a));
	murder(a->data);
	a->data = data;
	a->capacity = capacity;
}

forceinline void ArrayReserve(Array* a, usize capacity)
{
	if (capacity > a->capacity)
		ArraySetCapacity(a, capacity);
}

forceinline void ArrayGrow(Array* a, usize minCapacity)
{
	usize capacity = 2 * a->capacity + 2;
	if (capacity < minCapacity)
		capacity = minCapacity;

	ArraySetCapacity(a, capacity);
}

#endif

#endif