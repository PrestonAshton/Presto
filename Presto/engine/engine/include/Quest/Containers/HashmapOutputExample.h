#include <Quest/Common.h>
#include <Quest/Memory.h>
#include <Quest/Containers/Array.h>
#include <Quest/Utility/Console.h>

typedef struct
{
	u64* data;
	u32 length;
	u32 capacity;
} Array_u64;
typedef char
static_assertion_Size_Of_Array_u64[(sizeof(Array_u64) == 16) ? 1 : -1];
u64* Array_u64GetPtr(Array_u64* a, u32 index);
u64 Array_u64GetValue(Array_u64* a, u32 index);
void Array_u64Set(Array_u64* a, u32 index, u64 value);
void Array_u64SetPtr(Array_u64* a, u32 index, u64* value);
u32 Array_u64Size(Array_u64* a);
void Array_u64Equals(Array_u64* a, Array_u64* b);
void Array_u64PushBack(Array_u64* a, u64 item);
void Array_u64PushBackPtr(Array_u64* a, u64* item);
void Array_u64Dele(Array_u64* a);
b8 Array_u64Empty(Array_u64* a);
void* Array_u64Begin(Array_u64* a);
void* Array_u64End(Array_u64* a);
void* Array_u64Back(Array_u64* a);
void Array_u64Clear(Array_u64* a);
void Array_u64Trim(Array_u64* a);
u32 Array_u64Append(Array_u64* a, u64* items, u32 count);
void Array_u64Resize(Array_u64* a, u32 length);
void Array_u64SetCapacity(Array_u64* a, u32 capacity);
void Array_u64Reserve(Array_u64* a, u32 capacity);
void Array_u64Grow(Array_u64* a, u32 minCapacity);
__forceinline u64*
Array_u64GetPtr(Array_u64* a, u32 index)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(index < a->length))
		ForceAssert(
			L"index < a->length", 0,
			"D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
			12, &ASSERTBLOCK__LINE__);
	;
	return a->data + index;
}
__forceinline u64
Array_u64GetValue(Array_u64* a, u32 index)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(index < a->length))
		ForceAssert(
			L"index < a->length", 0,
			"D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
			12, &ASSERTBLOCK__LINE__);
	;
	return *(a->data + index);
}
__forceinline void
Array_u64Set(Array_u64* a, u32 index, u64 value)
{
	*(Array_u64GetPtr(a, index)) = value;
}
__forceinline void
Array_u64SetPtr(Array_u64* a, u32 index, u64* value)
{
	copyMemory(value, Array_u64GetPtr(a, index), sizeof(u64));
}
__forceinline u32
Array_u64Size(Array_u64* a)
{
	return a->length * sizeof(u64);
}
__forceinline void
Array_u64Equals(Array_u64* a, Array_u64* b)
{
	Array_u64Resize(a, b->length);
	copyMemory(b->data, a->data, Array_u64Size(b));
}
__forceinline void
Array_u64PushBack(Array_u64* a, u64 item)
{
	if (a->length == a->capacity)
		Array_u64Grow(a, 0);
	Array_u64Set(a, a->length, item);
}
__forceinline void
Array_u64PushBackPtr(Array_u64* a, u64* item)
{
	if (a->length == a->capacity)
		Array_u64Grow(a, 0);
	Array_u64SetPtr(a, a->length, item);
}
__forceinline void
Array_u64Dele(Array_u64* a)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(a->length > 0))
		ForceAssert(
			L"a->length > 0", 0,
			"D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
			12, &ASSERTBLOCK__LINE__);
	;
	a->length--;
}
__forceinline b8
Array_u64Empty(Array_u64* a)
{
	return a->length == 0;
}
__forceinline void*
Array_u64Begin(Array_u64* a)
{
	return a->data;
}
__forceinline void*
Array_u64End(Array_u64* a)
{
	return a->data + a->length;
}
__forceinline void*
Array_u64Back(Array_u64* a)
{
	return a->data + a->length - 1;
}
__forceinline void
Array_u64Clear(Array_u64* a)
{
	Array_u64Resize(a, 0);
}
__forceinline void
Array_u64Trim(Array_u64* a)
{
	Array_u64SetCapacity(a, a->length);
}
__forceinline u32
Array_u64Append(Array_u64* a, u64* items, u32 count)
{
	if (a->capacity <= a->length + count)
		Array_u64Grow(a, a->length + count);
	copyMemory(items, a->data + a->length, count * sizeof(u64));
	return a->length += count;
}
__forceinline void
Array_u64Resize(Array_u64* a, u32 length)
{
	if (length > a->capacity)
		Array_u64Grow(a, length);
	a->length = length;
}
__forceinline void
Array_u64SetCapacity(Array_u64* a, u32 capacity)
{
	if (capacity == a->capacity)
		return;
	if (capacity < a->length)
		Array_u64Resize(a, capacity);
	u64* data = 0;
	data = (u64*)heapAllocate(capacity * sizeof(u64), (vol)(4));
	copyMemory(a->data, data, Array_u64Size(a));
	heapDeallocate(a->data);
	a->data = data;
	a->capacity = capacity;
}
__forceinline void
Array_u64Reserve(Array_u64* a, u32 capacity)
{
	if (capacity > a->capacity)
		Array_u64SetCapacity(a, capacity);
}
__forceinline void
Array_u64Grow(Array_u64* a, u32 minCapacity)
{
	u32 capacity = 2 * a->capacity + 2;
	if (capacity < minCapacity)
		capacity = minCapacity;
	Array_u64SetCapacity(a, capacity);
}
typedef struct
{
	HashmapKey key;
	u32 next;
	u32 padding;
	u64 value;
} Hashmap_u64_Entry;
typedef struct
{
	Hashmap_u64_Entry* data;
	u32 length;
	u32 capacity;
} Array_Hashmap_u64_Entry;
typedef char static_assertion_Size_Of_Array_Hashmap_u64_Entry
[(sizeof(Array_Hashmap_u64_Entry) == 16) ? 1 : -1];
Hashmap_u64_Entry* Array_Hashmap_u64_EntryGetPtr(Array_Hashmap_u64_Entry* a,
	u32 index);
Hashmap_u64_Entry Array_Hashmap_u64_EntryGetValue(Array_Hashmap_u64_Entry* a,
	u32 index);
void Array_Hashmap_u64_EntrySet(Array_Hashmap_u64_Entry* a, u32 index,
	Hashmap_u64_Entry value);
void Array_Hashmap_u64_EntrySetPtr(Array_Hashmap_u64_Entry* a, u32 index,
	Hashmap_u64_Entry* value);
u32 Array_Hashmap_u64_EntrySize(Array_Hashmap_u64_Entry* a);
void Array_Hashmap_u64_EntryEquals(Array_Hashmap_u64_Entry* a,
	Array_Hashmap_u64_Entry* b);
void Array_Hashmap_u64_EntryPushBack(Array_Hashmap_u64_Entry* a,
	Hashmap_u64_Entry item);
void Array_Hashmap_u64_EntryPushBackPtr(Array_Hashmap_u64_Entry* a,
	Hashmap_u64_Entry* item);
void Array_Hashmap_u64_EntryDele(Array_Hashmap_u64_Entry* a);
b8 Array_Hashmap_u64_EntryEmpty(Array_Hashmap_u64_Entry* a);
void* Array_Hashmap_u64_EntryBegin(Array_Hashmap_u64_Entry* a);
void* Array_Hashmap_u64_EntryEnd(Array_Hashmap_u64_Entry* a);
void* Array_Hashmap_u64_EntryBack(Array_Hashmap_u64_Entry* a);
void Array_Hashmap_u64_EntryClear(Array_Hashmap_u64_Entry* a);
void Array_Hashmap_u64_EntryTrim(Array_Hashmap_u64_Entry* a);
u32 Array_Hashmap_u64_EntryAppend(Array_Hashmap_u64_Entry* a,
	Hashmap_u64_Entry* items, u32 count);
void Array_Hashmap_u64_EntryResize(Array_Hashmap_u64_Entry* a, u32 length);
void Array_Hashmap_u64_EntrySetCapacity(Array_Hashmap_u64_Entry* a,
	u32 capacity);
void Array_Hashmap_u64_EntryReserve(Array_Hashmap_u64_Entry* a, u32 capacity);
void Array_Hashmap_u64_EntryGrow(Array_Hashmap_u64_Entry* a, u32 minCapacity);
__forceinline Hashmap_u64_Entry*
Array_Hashmap_u64_EntryGetPtr(Array_Hashmap_u64_Entry* a, u32 index)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(index < a->length))
		ForceAssert(
			L"index < a->length", 0,
			"D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
			12, &ASSERTBLOCK__LINE__);
	;
	return a->data + index;
}
__forceinline Hashmap_u64_Entry
Array_Hashmap_u64_EntryGetValue(Array_Hashmap_u64_Entry* a, u32 index)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(index < a->length))
		ForceAssert(
			L"index < a->length", 0,
			"D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
			12, &ASSERTBLOCK__LINE__);
	;
	return *(a->data + index);
}
__forceinline void
Array_Hashmap_u64_EntrySet(Array_Hashmap_u64_Entry* a, u32 index,
	Hashmap_u64_Entry value)
{
	*(Array_Hashmap_u64_EntryGetPtr(a, index)) = value;
}
__forceinline void
Array_Hashmap_u64_EntrySetPtr(Array_Hashmap_u64_Entry* a, u32 index,
	Hashmap_u64_Entry* value)
{
	copyMemory(value, Array_Hashmap_u64_EntryGetPtr(a, index),
		sizeof(Hashmap_u64_Entry));
}
__forceinline u32
Array_Hashmap_u64_EntrySize(Array_Hashmap_u64_Entry* a)
{
	return a->length * sizeof(Hashmap_u64_Entry);
}
__forceinline void
Array_Hashmap_u64_EntryEquals(Array_Hashmap_u64_Entry* a,
	Array_Hashmap_u64_Entry* b)
{
	Array_Hashmap_u64_EntryResize(a, b->length);
	copyMemory(b->data, a->data, Array_Hashmap_u64_EntrySize(b));
}
__forceinline void
Array_Hashmap_u64_EntryPushBack(Array_Hashmap_u64_Entry* a,
	Hashmap_u64_Entry item)
{
	if (a->length == a->capacity)
		Array_Hashmap_u64_EntryGrow(a, 0);
	Array_Hashmap_u64_EntrySet(a, a->length++, item);
}
__forceinline void
Array_Hashmap_u64_EntryPushBackPtr(Array_Hashmap_u64_Entry* a,
	Hashmap_u64_Entry* item)
{
	if (a->length == a->capacity)
		Array_Hashmap_u64_EntryGrow(a, 0);
	Array_Hashmap_u64_EntrySetPtr(a, a->length++, item);
}
__forceinline void
Array_Hashmap_u64_EntryDele(Array_Hashmap_u64_Entry* a)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(a->length > 0))
		ForceAssert(
			L"a->length > 0", 0,
			"D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
			12, &ASSERTBLOCK__LINE__);
	;
	a->length--;
}
__forceinline b8
Array_Hashmap_u64_EntryEmpty(Array_Hashmap_u64_Entry* a)
{
	return a->length == 0;
}
__forceinline void*
Array_Hashmap_u64_EntryBegin(Array_Hashmap_u64_Entry* a)
{
	return a->data;
}
__forceinline void*
Array_Hashmap_u64_EntryEnd(Array_Hashmap_u64_Entry* a)
{
	return a->data + a->length;
}
__forceinline void*
Array_Hashmap_u64_EntryBack(Array_Hashmap_u64_Entry* a)
{
	return a->data + a->length - 1;
}
__forceinline void
Array_Hashmap_u64_EntryClear(Array_Hashmap_u64_Entry* a)
{
	Array_Hashmap_u64_EntryResize(a, 0);
}
__forceinline void
Array_Hashmap_u64_EntryTrim(Array_Hashmap_u64_Entry* a)
{
	Array_Hashmap_u64_EntrySetCapacity(a, a->length);
}
__forceinline u32
Array_Hashmap_u64_EntryAppend(Array_Hashmap_u64_Entry* a,
	Hashmap_u64_Entry* items, u32 count)
{
	if (a->capacity <= a->length + count)
		Array_Hashmap_u64_EntryGrow(a, a->length + count);
	copyMemory(items, a->data + a->length, count * sizeof(Hashmap_u64_Entry));
	return a->length += count;
}
__forceinline void
Array_Hashmap_u64_EntryResize(Array_Hashmap_u64_Entry* a, u32 length)
{
	if (length > a->capacity)
		Array_Hashmap_u64_EntryGrow(a, length);
	a->length = length;
}
__forceinline void
Array_Hashmap_u64_EntrySetCapacity(Array_Hashmap_u64_Entry* a, u32 capacity)
{
	if (capacity == a->capacity)
		return;
	if (capacity < a->length)
		Array_Hashmap_u64_EntryResize(a, capacity);
	Hashmap_u64_Entry* data = 0;
	data = (Hashmap_u64_Entry*)heapAllocate(capacity * sizeof(Hashmap_u64_Entry), (vol)(4));
	copyMemory(a->data, data, Array_Hashmap_u64_EntrySize(a));
	heapDeallocate(a->data);
	a->data = data;
	a->capacity = capacity;
}
__forceinline void
Array_Hashmap_u64_EntryReserve(Array_Hashmap_u64_Entry* a, u32 capacity)
{
	if (capacity > a->capacity)
		Array_Hashmap_u64_EntrySetCapacity(a, capacity);
}
__forceinline void
Array_Hashmap_u64_EntryGrow(Array_Hashmap_u64_Entry* a, u32 minCapacity)
{
	u32 capacity = 2 * a->capacity + 2;
	if (capacity < minCapacity)
		capacity = minCapacity;
	Array_Hashmap_u64_EntrySetCapacity(a, capacity);
}
typedef struct
{
	Array_u64 hashes;
	Array_Hashmap_u64_Entry data;
} Hashmap_u64;
typedef char
static_assertion_Size_Of_Hashmap_u64[(sizeof(Hashmap_u64) == 32) ? 1 : -1];
b8 Hashmap_u64Has(Hashmap_u64* hashmap, HashmapKey key);
u64* Hashmap_u64GetPtr(Hashmap_u64* hashmap, HashmapKey key);
u64* Hashmap_u64GetPtrDefault(Hashmap_u64* hashmap, HashmapKey key,
	u64* defaultValue);
u64 Hashmap_u64GetValue(Hashmap_u64* hashmap, HashmapKey key);
u64 Hashmap_u64GetValueDefault(Hashmap_u64* hashmap, HashmapKey key,
	u64 defaultValue);
void Hashmap_u64SetByValue(Hashmap_u64* hashmap, HashmapKey key,
	u64 value);
void Hashmap_u64SetByPtr(Hashmap_u64* hashmap, HashmapKey key,
	u64* value);
void Hashmap_u64Remove(Hashmap_u64* hashmap, HashmapKey key);
void Hashmap_u64Reserve(Hashmap_u64* hashmap, HashmapKey key, u32 capacity);
void Hashmap_u64Clear(Hashmap_u64* hashmap);
void Hashmap_u64zInternalErase(Hashmap_u64* hashmap,
	HashmapFindResult* findResult);
u32 Hashmap_u64zInternalAddEntry(Hashmap_u64* hashmap, HashmapKey key);
void Hashmap_u64zInternalFindAndErase(Hashmap_u64* hashmap, HashmapKey key);
HashmapFindResult Hashmap_u64zInternalFindByKey(Hashmap_u64* hashmap,
	HashmapKey key);
HashmapFindResult Hashmap_u64zInternalFindByEntry(Hashmap_u64* hashmap,
	Hashmap_u64_Entry* entry);
u32 Hashmap_u64zInternalFindOrFail(Hashmap_u64* hashmap, HashmapKey key);
u32 Hashmap_u64zInternalMake(Hashmap_u64* hashmap, HashmapKey key);
u32 Hashmap_u64zInternalFindOrMake(Hashmap_u64* hashmap, HashmapKey key);
b8 Hashmap_u64zInternalFull(Hashmap_u64* hashmap);
void Hashmap_u64zInternalRehash(Hashmap_u64* hashmap, u32 newCapacity);
void Hashmap_u64zInternalGrow(Hashmap_u64* hashmap);
Hashmap_u64_Entry* Hashmap_u64zInternalFindFirst(Hashmap_u64* hashmap,
	HashmapKey key);
Hashmap_u64_Entry* Hashmap_u64zInternalFindNext(Hashmap_u64* hashmap,
	Hashmap_u64_Entry* entry);
b8
Hashmap_u64Has(Hashmap_u64* hashmap, HashmapKey key)
{
	return Hashmap_u64zInternalFindOrFail(hashmap, key) != (u32)(-1);
}
u64*
Hashmap_u64GetPtr(Hashmap_u64* hashmap, HashmapKey key)
{
	u32 index = Hashmap_u64zInternalFindOrFail(hashmap, key);
	Assert(index != InvalidHashmapIndex);
	return &(Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index)->value);
}
u64*
Hashmap_u64GetPtrDefault(Hashmap_u64* hashmap, HashmapKey key,
	u64* defaultValue)
{
	u32 index = Hashmap_u64zInternalFindOrFail(hashmap, key);
	if (index == (u32)(-1))
		return defaultValue;
	return &(Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index)->value);
}
u64
Hashmap_u64GetValue(Hashmap_u64* hashmap, HashmapKey key)
{
	u32 index = Hashmap_u64zInternalFindOrFail(hashmap, key);
	Assert(index != InvalidHashmapIndex);
	return Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index)->value;
}
u64
Hashmap_u64GetValueDefault(Hashmap_u64* hashmap, HashmapKey key,
	u64 defaultValue)
{
	u32 index = Hashmap_u64zInternalFindOrFail(hashmap, key);
	if (index == (u32)(-1))
		return defaultValue;
	return Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index)->value;
}
void
Hashmap_u64SetByValue(Hashmap_u64* hashmap, HashmapKey key, u64 value)
{
	if (hashmap->hashes.length == 0)
		Hashmap_u64zInternalGrow(hashmap);
	u32 index = Hashmap_u64zInternalFindOrMake(hashmap, key);
	Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index)->value = value;
	if (Hashmap_u64zInternalFull(hashmap))
		Hashmap_u64zInternalGrow(hashmap);
}
void
Hashmap_u64SetByPtr(Hashmap_u64* hashmap, HashmapKey key, u64* value)
{
	if (hashmap->hashes.length == 0)
		Hashmap_u64zInternalGrow(hashmap);
	u32 index = Hashmap_u64zInternalFindOrMake(hashmap, key);
	Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index)->value = *value;
	if (Hashmap_u64zInternalFull(hashmap))
		Hashmap_u64zInternalGrow(hashmap);
}
void
Hashmap_u64Remove(Hashmap_u64* hashmap, HashmapKey key)
{
	Hashmap_u64zInternalFindAndErase(hashmap, key);
}
void
Hashmap_u64Reserve(Hashmap_u64* hashmap, HashmapKey key, u32 capacity)
{
	Hashmap_u64zInternalRehash(hashmap, capacity);
}
void
Hashmap_u64Clear(Hashmap_u64* hashmap)
{
	Array_u64Clear(&(hashmap->hashes));
	Array_Hashmap_u64_EntryClear(&(hashmap->data));
}
void
Hashmap_u64zInternalErase(Hashmap_u64* hashmap, HashmapFindResult* findResult)
{
	if (findResult->dataPreviousIndex == (u32)(-1))
		*Array_u64GetPtr(&(hashmap->hashes), findResult->hashIndex) =
		Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), findResult->dataIndex)
		->next;
	else
		Array_Hashmap_u64_EntryGetPtr(&(hashmap->data),
			findResult->dataPreviousIndex)
		->next =
		Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), findResult->dataIndex)
		->next;
	if (findResult->dataIndex == hashmap->data.length - 1) {
		Array_Hashmap_u64_EntryDele(&(hashmap->data));
		return;
	}
	*Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), findResult->dataIndex) =
		Array_Hashmap_u64_EntryGetValue(&(hashmap->data), hashmap->data.length - 1);
	HashmapFindResult last = Hashmap_u64zInternalFindByKey(
		hashmap,
		Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), findResult->dataIndex)->key);
	if (last.dataIndex == (u32)(-1))
		*Array_u64GetPtr(&(hashmap->hashes), last.hashIndex) =
		findResult->dataIndex;
	else
		Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), last.dataIndex)->next =
		findResult->dataIndex;
}
u32
Hashmap_u64zInternalAddEntry(Hashmap_u64* hashmap, HashmapKey key)
{
	Hashmap_u64_Entry newEntry;
	newEntry.key = key;
	newEntry.next = (u32)(-1);
	u32 entryIndex = hashmap->data.length;
	Array_Hashmap_u64_EntryPushBackPtr(&(hashmap->data), &newEntry);
	return entryIndex;
}
void
Hashmap_u64zInternalFindAndErase(Hashmap_u64* hashmap, HashmapKey key)
{
	HashmapFindResult fr = Hashmap_u64zInternalFindByKey(hashmap, key);
	if (fr.dataIndex != (u32)(-1))
		Hashmap_u64zInternalErase(hashmap, &fr);
}
HashmapFindResult
Hashmap_u64zInternalFindByKey(Hashmap_u64* hashmap, HashmapKey key)
{
	HashmapFindResult fr;
	fr.hashIndex = InvalidHashmapIndex;
	fr.dataIndex = InvalidHashmapIndex;
	fr.dataPreviousIndex = InvalidHashmapIndex;

	if (hashmap->hashes.length == 0)
		return fr;
	fr.hashIndex = key % hashmap->hashes.length;
	fr.dataIndex = Array_u64GetValue(&(hashmap->hashes), fr.hashIndex);
	while (fr.dataIndex != (u32)(-1)) {
		if (Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), fr.dataIndex)->key ==
			key)
			return fr;
		fr.dataPreviousIndex = fr.dataIndex;
		fr.dataIndex =
			Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), fr.dataIndex)->next;
	}
	return fr;
}
HashmapFindResult
Hashmap_u64zInternalFindByEntry(Hashmap_u64* hashmap, Hashmap_u64_Entry* entry)
{
	HashmapFindResult fr;
	fr.hashIndex = InvalidHashmapIndex;
	fr.dataIndex = InvalidHashmapIndex;
	fr.dataPreviousIndex = InvalidHashmapIndex;

	if (hashmap->hashes.length == 0 || entry == 0)
		return fr;
	fr.hashIndex = entry->key % hashmap->hashes.length;
	fr.dataIndex = Array_u64GetValue(&(hashmap->hashes), fr.hashIndex);
	while (fr.dataIndex != (u32)(-1)) {
		if (Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), fr.dataIndex) == entry)
			return fr;
		fr.dataPreviousIndex = fr.dataIndex;
		fr.dataIndex =
			Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), fr.dataIndex)->next;
	}
	return fr;
}
u32
Hashmap_u64zInternalFindOrFail(Hashmap_u64* hashmap, HashmapKey key)
{
	return Hashmap_u64zInternalFindByKey(hashmap, key).dataIndex;
}

forceinline void Hashmap_u64zInternalInsert(Hashmap_u64 * hashmap, HashmapKey key, u64* value) \
{
	if (hashmap->hashes.length == 0)
		Hashmap_u64zInternalGrow(hashmap);

	u32 next = Hashmap_u64zInternalMake(hashmap, key);
	Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), next)->value = *value;

	if (Hashmap_u64zInternalFull(hashmap))
		Hashmap_u64zInternalGrow(hashmap);
}

u32
Hashmap_u64zInternalMake(Hashmap_u64* hashmap, HashmapKey key)
{
	HashmapFindResult fr = Hashmap_u64zInternalFindByKey(hashmap, key);
	u32 index = Hashmap_u64zInternalAddEntry(hashmap, key);
	if (fr.dataPreviousIndex == (u32)(-1))
		*Array_u64GetPtr(&(hashmap->hashes), fr.hashIndex) = index;
	else
		Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), fr.dataPreviousIndex)->next =
		index;
	Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index)->next = fr.dataIndex;
	return index;
}
u32
Hashmap_u64zInternalFindOrMake(Hashmap_u64* hashmap, HashmapKey key)
{
	HashmapFindResult fr = Hashmap_u64zInternalFindByKey(hashmap, key);
	if (fr.dataIndex != (u32)(-1))
		return fr.dataIndex;
	u32 index = Hashmap_u64zInternalAddEntry(hashmap, key);
	if (fr.dataPreviousIndex == (u32)(-1))
		Array_u64Set(&(hashmap->hashes), fr.hashIndex, index);
	else
		Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), fr.dataPreviousIndex)->next =
		index;
	return index;
}
b8
Hashmap_u64zInternalFull(Hashmap_u64* hashmap)
{
	return hashmap->data.length >= 0.75f * hashmap->hashes.length;
}
void
Hashmap_u64zInternalRehash(Hashmap_u64* hashmap, u32 newCapacity)
{
	Hashmap_u64 newHashmap = { 0 };
	Array_u64Resize(&(newHashmap.hashes), newCapacity);
	u32 oldLength = hashmap->data.length;
	Array_Hashmap_u64_EntryReserve(&(newHashmap.data), oldLength);
	for (u32 i = 0; i < newCapacity; i++) *Array_u64GetPtr(&(newHashmap.hashes), i) = (u32)(-1); for (u32 i = 0; i < oldLength; i++) {
		Hashmap_u64_Entry* entry =
			Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), i);
		Hashmap_u64zInternalInsert(&newHashmap, entry->key, &entry->value);
	} copyMemory(&newHashmap, hashmap, sizeof(Hashmap_u64));
}
void
Hashmap_u64zInternalGrow(Hashmap_u64* hashmap)
{
	u32 newCapacity = 2 * hashmap->data.length + 2;
	Hashmap_u64zInternalRehash(hashmap, newCapacity);
}
Hashmap_u64_Entry*
Hashmap_u64zInternalFindFirst(Hashmap_u64* hashmap, HashmapKey key)
{
	u32 index = Hashmap_u64zInternalFindOrFail(hashmap, key);
	if (index == (u32)(-1))
		return 0;
	return Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index);
}
Hashmap_u64_Entry*
Hashmap_u64zInternalFindNext(Hashmap_u64* hashmap, Hashmap_u64_Entry* entry)
{
	if (!entry)
		return 0;
	u32 index = entry->next;
	while (index != (u32)(-1)) {
		Hashmap_u64_Entry* found =
			Array_Hashmap_u64_EntryGetPtr(&(hashmap->data), index);
		if (found->key == entry->key)
			return found;
		index = found->next;
	}
	return 0;
}
