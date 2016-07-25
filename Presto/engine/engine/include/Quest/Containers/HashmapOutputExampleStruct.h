#include <Quest/Common.h>
#include <Quest/Containers.h>
#include <Quest/Modules/OpenAL/Player.h>

#define InvalidHashmapIndex (u32)(-1)

#ifdef CONTAINER_DEBUGGING
#define CONTAINER_DEBUG(x) x
#else
#define CONTAINER_DEBUG(x)
#endif

typedef u64 HashmapKey;
typedef struct
{
	u32 hashIndex;
	u32 dataIndex;
	u32 dataPreviousIndex;
	u32 padding;
} HashmapFindResult;

typedef struct
{
	HashmapKey key;
	u32 next;
	u32 padding;
	SoundInfo value;
} Hashmap_SoundInfo_Entry;
typedef struct
{
	Hashmap_SoundInfo_Entry* data;
	u32 length;
	u32 capacity;
} Array_Hashmap_SoundInfo_Entry;
typedef char static_assertion_Size_Of_Array_Hashmap_SoundInfo_Entry
[(sizeof(Array_Hashmap_SoundInfo_Entry) == 16) ? 1 : -1];
Hashmap_SoundInfo_Entry* Array_Hashmap_SoundInfo_EntryGetPtr(
	Array_Hashmap_SoundInfo_Entry* a, u32 index);
Hashmap_SoundInfo_Entry Array_Hashmap_SoundInfo_EntryGetValue(
	Array_Hashmap_SoundInfo_Entry* a, u32 index);
void Array_Hashmap_SoundInfo_EntrySet(Array_Hashmap_SoundInfo_Entry* a,
	u32 index, Hashmap_SoundInfo_Entry value);
void Array_Hashmap_SoundInfo_EntrySetPtr(Array_Hashmap_SoundInfo_Entry* a,
	u32 index,
	Hashmap_SoundInfo_Entry* value);
u32 Array_Hashmap_SoundInfo_EntrySize(const Array_Hashmap_SoundInfo_Entry* a);
void Array_Hashmap_SoundInfo_EntryEquals(
	Array_Hashmap_SoundInfo_Entry* a, const Array_Hashmap_SoundInfo_Entry* b);
void Array_Hashmap_SoundInfo_EntryPushBack(Array_Hashmap_SoundInfo_Entry* a,
	Hashmap_SoundInfo_Entry item);
void Array_Hashmap_SoundInfo_EntryPushBackPtr(Array_Hashmap_SoundInfo_Entry* a,
	Hashmap_SoundInfo_Entry* item);
void Array_Hashmap_SoundInfo_EntryDele(Array_Hashmap_SoundInfo_Entry* a);
b8 Array_Hashmap_SoundInfo_EntryEmpty(const Array_Hashmap_SoundInfo_Entry* a);
void* Array_Hashmap_SoundInfo_EntryBegin(Array_Hashmap_SoundInfo_Entry* a);
void* Array_Hashmap_SoundInfo_EntryEnd(Array_Hashmap_SoundInfo_Entry* a);
void* Array_Hashmap_SoundInfo_EntryBack(Array_Hashmap_SoundInfo_Entry* a);
void Array_Hashmap_SoundInfo_EntryClear(Array_Hashmap_SoundInfo_Entry* a);
void Array_Hashmap_SoundInfo_EntryTrim(Array_Hashmap_SoundInfo_Entry* a);
u32 Array_Hashmap_SoundInfo_EntryAppend(Array_Hashmap_SoundInfo_Entry* a,
	const Hashmap_SoundInfo_Entry* items,
	u32 count);
void Array_Hashmap_SoundInfo_EntryResize(Array_Hashmap_SoundInfo_Entry* a,
	u32 length);
void Array_Hashmap_SoundInfo_EntrySetCapacity(Array_Hashmap_SoundInfo_Entry* a,
	u32 capacity);
void Array_Hashmap_SoundInfo_EntryReserve(Array_Hashmap_SoundInfo_Entry* a,
	u32 capacity);
void Array_Hashmap_SoundInfo_EntryGrow(Array_Hashmap_SoundInfo_Entry* a,
	u32 minCapacity);
__forceinline Hashmap_SoundInfo_Entry*
Array_Hashmap_SoundInfo_EntryGetPtr(Array_Hashmap_SoundInfo_Entry* a, u32 index)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(index < a->length))
		ForceAssert(L"index < a->length", 0, "D:"
			"\\Presto\\Presto\\engine\\engine\\inc"
			"lude\\Quest/Modules/OpenAL/Player.h",
			32, &ASSERTBLOCK__LINE__);
	;
	return a->data + index;
}
__forceinline Hashmap_SoundInfo_Entry
Array_Hashmap_SoundInfo_EntryGetValue(Array_Hashmap_SoundInfo_Entry* a,
	u32 index)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(index < a->length))
		ForceAssert(L"index < a->length", 0, "D:"
			"\\Presto\\Presto\\engine\\engine\\inc"
			"lude\\Quest/Modules/OpenAL/Player.h",
			32, &ASSERTBLOCK__LINE__);
	;
	return *(a->data + index);
}
__forceinline void
Array_Hashmap_SoundInfo_EntrySet(Array_Hashmap_SoundInfo_Entry* a, u32 index,
	Hashmap_SoundInfo_Entry value)
{
	*(Array_Hashmap_SoundInfo_EntryGetPtr(a, index)) = value;
}
__forceinline void
Array_Hashmap_SoundInfo_EntrySetPtr(Array_Hashmap_SoundInfo_Entry* a, u32 index,
	Hashmap_SoundInfo_Entry* value)
{
	copyMemory(value, Array_Hashmap_SoundInfo_EntryGetPtr(a, index),
		sizeof(Hashmap_SoundInfo_Entry));
}
__forceinline u32
Array_Hashmap_SoundInfo_EntrySize(const Array_Hashmap_SoundInfo_Entry* a)
{
	return a->length * sizeof(Hashmap_SoundInfo_Entry);
}
__forceinline void
Array_Hashmap_SoundInfo_EntryEquals(Array_Hashmap_SoundInfo_Entry* a,
	const Array_Hashmap_SoundInfo_Entry* b)
{
	Array_Hashmap_SoundInfo_EntryResize(a, b->length);
	copyMemory(b->data, a->data, Array_Hashmap_SoundInfo_EntrySize(b));
}
__forceinline void
Array_Hashmap_SoundInfo_EntryPushBack(Array_Hashmap_SoundInfo_Entry* a,
	Hashmap_SoundInfo_Entry item)
{
	if (a->length == a->capacity)
		Array_Hashmap_SoundInfo_EntryGrow(a, 0);
	Array_Hashmap_SoundInfo_EntrySet(a, a->length++, item);
}
__forceinline void
Array_Hashmap_SoundInfo_EntryPushBackPtr(Array_Hashmap_SoundInfo_Entry* a,
	Hashmap_SoundInfo_Entry* item)
{
	if (a->length == a->capacity)
		Array_Hashmap_SoundInfo_EntryGrow(a, 0);
	Array_Hashmap_SoundInfo_EntrySetPtr(a, a->length++, item);
}
__forceinline void
Array_Hashmap_SoundInfo_EntryDele(Array_Hashmap_SoundInfo_Entry* a)
{
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(a->length > 0))
		ForceAssert(L"a->length > 0", 0, "D:"
			"\\Presto\\Presto\\engine\\engine\\include"
			"\\Quest/Modules/OpenAL/Player.h",
			32, &ASSERTBLOCK__LINE__);
	;
	a->length--;
}
__forceinline b8
Array_Hashmap_SoundInfo_EntryEmpty(const Array_Hashmap_SoundInfo_Entry* a)
{
	return a->length == 0;
}
__forceinline void*
Array_Hashmap_SoundInfo_EntryBegin(Array_Hashmap_SoundInfo_Entry* a)
{
	return a->data;
}
__forceinline void*
Array_Hashmap_SoundInfo_EntryEnd(Array_Hashmap_SoundInfo_Entry* a)
{
	return a->data + a->length;
}
__forceinline void*
Array_Hashmap_SoundInfo_EntryBack(Array_Hashmap_SoundInfo_Entry* a)
{
	return a->data + a->length - 1;
}
__forceinline void
Array_Hashmap_SoundInfo_EntryClear(Array_Hashmap_SoundInfo_Entry* a)
{
	Array_Hashmap_SoundInfo_EntryResize(a, 0);
}
__forceinline void
Array_Hashmap_SoundInfo_EntryTrim(Array_Hashmap_SoundInfo_Entry* a)
{
	Array_Hashmap_SoundInfo_EntrySetCapacity(a, a->length);
}
__forceinline u32
Array_Hashmap_SoundInfo_EntryAppend(Array_Hashmap_SoundInfo_Entry* a,
	const Hashmap_SoundInfo_Entry* items,
	u32 count)
{
	if (a->capacity <= a->length + count)
		Array_Hashmap_SoundInfo_EntryGrow(a, a->length + count);
	copyMemory(items, a->data + a->length,
		count * sizeof(Hashmap_SoundInfo_Entry));
	return a->length += count;
}
__forceinline void
Array_Hashmap_SoundInfo_EntryResize(Array_Hashmap_SoundInfo_Entry* a,
	u32 length)
{
	if (length > a->capacity)
		Array_Hashmap_SoundInfo_EntryGrow(a, length);
	a->length = length;
}
__forceinline void
Array_Hashmap_SoundInfo_EntrySetCapacity(Array_Hashmap_SoundInfo_Entry* a,
	u32 capacity)
{
	if (capacity == a->capacity)
		return;
	if (capacity < a->length)
		Array_Hashmap_SoundInfo_EntryResize(a, capacity);
	Hashmap_SoundInfo_Entry* data = 0;
	data = (Hashmap_SoundInfo_Entry*)heapAllocate(
		capacity * sizeof(Hashmap_SoundInfo_Entry), (vol)(4));
	if (a->data != 0) {
		copyMemory(a->data, data, Array_Hashmap_SoundInfo_EntrySize(a));
		heapDeallocate(a->data);
	}
	a->data = data;
	a->capacity = capacity;
}
__forceinline void
Array_Hashmap_SoundInfo_EntryReserve(Array_Hashmap_SoundInfo_Entry* a,
	u32 capacity)
{
	if (capacity > a->capacity)
		Array_Hashmap_SoundInfo_EntrySetCapacity(a, capacity);
}
__forceinline void
Array_Hashmap_SoundInfo_EntryGrow(Array_Hashmap_SoundInfo_Entry* a,
	u32 minCapacity)
{
	u32 capacity = 2 * a->capacity + 2;
	if (capacity < minCapacity)
		capacity = minCapacity;
	Array_Hashmap_SoundInfo_EntrySetCapacity(a, capacity);
}
typedef struct
{
	Array_u64 hashes;
	Array_Hashmap_SoundInfo_Entry data;
} Hashmap_SoundInfo;
typedef char static_assertion_Size_Of_Hashmap_SoundInfo
[(sizeof(Hashmap_SoundInfo) == 32) ? 1 : -1];
b8 Hashmap_SoundInfoHas(Hashmap_SoundInfo* hashmap, HashmapKey key);
SoundInfo* Hashmap_SoundInfoGetPtr(Hashmap_SoundInfo* hashmap, HashmapKey key);
SoundInfo* Hashmap_SoundInfoGetPtrDefault(Hashmap_SoundInfo* hashmap,
	HashmapKey key,
	SoundInfo* defaultValue);
SoundInfo Hashmap_SoundInfoGetValue(Hashmap_SoundInfo* hashmap, HashmapKey key);
SoundInfo Hashmap_SoundInfoGetValueDefault(Hashmap_SoundInfo* hashmap,
	HashmapKey key,
	SoundInfo defaultValue);
void Hashmap_SoundInfoSetByValue(Hashmap_SoundInfo* hashmap, HashmapKey key,
	SoundInfo value);
void Hashmap_SoundInfoSetByPtr(Hashmap_SoundInfo* hashmap, HashmapKey key,
	SoundInfo* value);
void Hashmap_SoundInfoRemove(Hashmap_SoundInfo* hashmap, HashmapKey key);
void Hashmap_SoundInfoReserve(Hashmap_SoundInfo* hashmap, HashmapKey key,
	u32 capacity);
void Hashmap_SoundInfoClear(Hashmap_SoundInfo* hashmap);
void Hashmap_SoundInfozInternalErase(Hashmap_SoundInfo* hashmap,
	HashmapFindResult* findResult);
u32 Hashmap_SoundInfozInternalAddEntry(Hashmap_SoundInfo* hashmap,
	HashmapKey key);
void Hashmap_SoundInfozInternalFindAndErase(Hashmap_SoundInfo* hashmap,
	HashmapKey key);
HashmapFindResult Hashmap_SoundInfozInternalFindByKey(
	Hashmap_SoundInfo* hashmap, HashmapKey key);
HashmapFindResult Hashmap_SoundInfozInternalFindByEntry(
	Hashmap_SoundInfo* hashmap, Hashmap_SoundInfo_Entry* entry);
u32 Hashmap_SoundInfozInternalFindOrFail(Hashmap_SoundInfo* hashmap,
	HashmapKey key);
u32 Hashmap_SoundInfozInternalMake(Hashmap_SoundInfo* hashmap, HashmapKey key);
u32 Hashmap_SoundInfozInternalFindOrMake(Hashmap_SoundInfo* hashmap,
	HashmapKey key);
b8 Hashmap_SoundInfozInternalFull(Hashmap_SoundInfo* hashmap);
void Hashmap_SoundInfozInternalRehash(Hashmap_SoundInfo* hashmap,
	u32 newCapacity);
void Hashmap_SoundInfozInternalGrow(Hashmap_SoundInfo* hashmap);
void Hashmap_SoundInfozInternalInsert(Hashmap_SoundInfo* hashmap,
	HashmapKey key, SoundInfo* value);
Hashmap_SoundInfo_Entry* Hashmap_SoundInfozInternalFindFirst(
	Hashmap_SoundInfo* hashmap, HashmapKey key);
Hashmap_SoundInfo_Entry* Hashmap_SoundInfozInternalFindNext(
	Hashmap_SoundInfo* hashmap, Hashmap_SoundInfo_Entry* entry);
__forceinline b8
Hashmap_SoundInfoHas(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	b8 findOrFailResult =
		Hashmap_SoundInfozInternalFindOrFail(hashmap, key) != (u32)(-1);
	;
	return findOrFailResult;
}
__forceinline SoundInfo*
Hashmap_SoundInfoGetPtr(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	u32 index = Hashmap_SoundInfozInternalFindOrFail(hashmap, key);
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(index != (u32)(-1)))
		ForceAssert(L"index != (u32)(-1)", 0,
			"D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Modules/"
			"OpenAL/Player.h",
			32, &ASSERTBLOCK__LINE__);
	;
	;
	return &(Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index)->value);
}
__forceinline SoundInfo*
Hashmap_SoundInfoGetPtrDefault(Hashmap_SoundInfo* hashmap, HashmapKey key,
	SoundInfo* defaultValue)
{
	;
	u32 index = Hashmap_SoundInfozInternalFindOrFail(hashmap, key);
	if (index == (u32)(-1)) {
		;
		return defaultValue;
	};
	return &(Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index)->value);
}
__forceinline SoundInfo
Hashmap_SoundInfoGetValue(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	u32 index = Hashmap_SoundInfozInternalFindOrFail(hashmap, key);
	static b8 ASSERTBLOCK__LINE__ = 0;
	if (!(index != (u32)(-1)))
		ForceAssert(L"index != (u32)(-1)", 0,
			"D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Modules/"
			"OpenAL/Player.h",
			32, &ASSERTBLOCK__LINE__);
	;
	;
	return Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index)->value;
}
__forceinline SoundInfo
Hashmap_SoundInfoGetValueDefault(Hashmap_SoundInfo* hashmap, HashmapKey key,
	SoundInfo defaultValue)
{
	;
	u32 index = Hashmap_SoundInfozInternalFindOrFail(hashmap, key);
	if (index == (u32)(-1)) {
		;
		return defaultValue;
	}
	return Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index)->value;
	;
}
__forceinline void
Hashmap_SoundInfoSetByValue(Hashmap_SoundInfo* hashmap, HashmapKey key,
	SoundInfo value)
{
	;
	if (hashmap->hashes.length == 0)
		Hashmap_SoundInfozInternalGrow(hashmap);
	u32 index = Hashmap_SoundInfozInternalFindOrMake(hashmap, key);
	Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index)->value = value;
	if (Hashmap_SoundInfozInternalFull(hashmap))
		Hashmap_SoundInfozInternalGrow(hashmap);
	;
}
__forceinline void
Hashmap_SoundInfoSetByPtr(Hashmap_SoundInfo* hashmap, HashmapKey key,
	SoundInfo* value)
{
	;
	if (hashmap->hashes.length == 0)
		Hashmap_SoundInfozInternalGrow(hashmap);
	u32 index = Hashmap_SoundInfozInternalFindOrMake(hashmap, key);
	Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index)->value = *value;
	if (Hashmap_SoundInfozInternalFull(hashmap))
		Hashmap_SoundInfozInternalGrow(hashmap);
	;
}
__forceinline void
Hashmap_SoundInfoRemove(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	Hashmap_SoundInfozInternalFindAndErase(hashmap, key);
	;
}
__forceinline void
Hashmap_SoundInfoReserve(Hashmap_SoundInfo* hashmap, HashmapKey key,
	u32 capacity)
{
	;
	Hashmap_SoundInfozInternalRehash(hashmap, capacity);
	;
}
__forceinline void
Hashmap_SoundInfoClear(Hashmap_SoundInfo* hashmap)
{
	;
	Array_u64Clear(&(hashmap->hashes));
	Array_Hashmap_SoundInfo_EntryClear(&(hashmap->data));
	;
}
__forceinline void
Hashmap_SoundInfozInternalErase(Hashmap_SoundInfo* hashmap,
	HashmapFindResult* findResult)
{
	;
	if (findResult->dataPreviousIndex == (u32)(-1))
		*Array_u64GetPtr(&(hashmap->hashes), findResult->hashIndex) =
		Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data),
			findResult->dataIndex)
		->next;
	else
		Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data),
			findResult->dataPreviousIndex)
		->next = Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data),
			findResult->dataIndex)
		->next;
	if (findResult->dataIndex == hashmap->data.length - 1) {
		Array_Hashmap_SoundInfo_EntryDele(&(hashmap->data));
		;
		return;
	}
	*Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data),
		findResult->dataIndex) =
		Array_Hashmap_SoundInfo_EntryGetValue(&(hashmap->data),
			hashmap->data.length - 1);
	HashmapFindResult last = Hashmap_SoundInfozInternalFindByKey(
		hashmap,
		Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), findResult->dataIndex)
		->key);
	if (last.dataIndex == (u32)(-1))
		*Array_u64GetPtr(&(hashmap->hashes), last.hashIndex) =
		findResult->dataIndex;
	else
		Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), last.dataIndex)
		->next = findResult->dataIndex;
	;
}
__forceinline u32
Hashmap_SoundInfozInternalAddEntry(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	Hashmap_SoundInfo_Entry newEntry;
	newEntry.key = key;
	newEntry.next = (u32)(-1);
	u32 entryIndex = hashmap->data.length;
	Array_Hashmap_SoundInfo_EntryPushBackPtr(&(hashmap->data), &newEntry);
	;
	return entryIndex;
}
__forceinline void
Hashmap_SoundInfozInternalFindAndErase(Hashmap_SoundInfo* hashmap,
	HashmapKey key)
{
	;
	HashmapFindResult fr = Hashmap_SoundInfozInternalFindByKey(hashmap, key);
	if (fr.dataIndex != (u32)(-1))
		Hashmap_SoundInfozInternalErase(hashmap, &fr);
}
__forceinline HashmapFindResult
Hashmap_SoundInfozInternalFindByKey(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	HashmapFindResult fr;
	fr.hashIndex = (u32)(-1);
	fr.dataIndex = (u32)(-1);
	fr.dataPreviousIndex = (u32)(-1);
	if (hashmap->hashes.length == 0) {
		;
		return fr;
	}
	fr.hashIndex = key % hashmap->hashes.length;
	fr.dataIndex = Array_u64GetValue(&(hashmap->hashes), fr.hashIndex);
	while (fr.dataIndex != (u32)(-1)) {
		if (Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), fr.dataIndex)
			->key == key) {
			;
			return fr;
		}
		fr.dataPreviousIndex = fr.dataIndex;
		fr.dataIndex =
			Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), fr.dataIndex)->next;
	};
	return fr;
}
__forceinline HashmapFindResult
Hashmap_SoundInfozInternalFindByEntry(Hashmap_SoundInfo* hashmap,
	Hashmap_SoundInfo_Entry* entry)
{
	;
	HashmapFindResult fr;
	fr.hashIndex = (u32)(-1);
	fr.dataIndex = (u32)(-1);
	fr.dataPreviousIndex = (u32)(-1);
	if (hashmap->hashes.length == 0 || entry == 0) {
		;
		return fr;
	}
	fr.hashIndex = entry->key % hashmap->hashes.length;
	fr.dataIndex = Array_u64GetValue(&(hashmap->hashes), fr.hashIndex);
	while (fr.dataIndex != (u32)(-1)) {
		if (Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), fr.dataIndex) ==
			entry) {
			;
			return fr;
		}
		fr.dataPreviousIndex = fr.dataIndex;
		fr.dataIndex =
			Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), fr.dataIndex)->next;
	};
	return fr;
}
__forceinline u32
Hashmap_SoundInfozInternalFindOrFail(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	u32 dataIndex = Hashmap_SoundInfozInternalFindByKey(hashmap, key).dataIndex;
	;
	return dataIndex;
}
__forceinline u32
Hashmap_SoundInfozInternalMake(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	HashmapFindResult fr = Hashmap_SoundInfozInternalFindByKey(hashmap, key);
	u32 index = Hashmap_SoundInfozInternalAddEntry(hashmap, key);
	if (fr.dataPreviousIndex == (u32)(-1))
		*Array_u64GetPtr(&(hashmap->hashes), fr.hashIndex) = index;
	else
		Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), fr.dataPreviousIndex)
		->next = index;
	Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index)->next =
		fr.dataIndex;
	;
	return index;
}
__forceinline u32
Hashmap_SoundInfozInternalFindOrMake(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	HashmapFindResult fr = Hashmap_SoundInfozInternalFindByKey(hashmap, key);
	if (fr.dataIndex != (u32)(-1)) {
		;
		return fr.dataIndex;
	}
	u32 index = Hashmap_SoundInfozInternalAddEntry(hashmap, key);
	if (fr.dataPreviousIndex == (u32)(-1))
		Array_u64Set(&(hashmap->hashes), fr.hashIndex, index);
	else
		Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), fr.dataPreviousIndex)
		->next = index;
	;
	return index;
}
__forceinline b8
Hashmap_SoundInfozInternalFull(Hashmap_SoundInfo* hashmap)
{
	;
	;
	return hashmap->data.length >= 0.75f * hashmap->hashes.length;
}
__forceinline void
Hashmap_SoundInfozInternalRehash(Hashmap_SoundInfo* hashmap, u32 newCapacity)
{
	;
	Hashmap_SoundInfo newHashmap = { 0 };
	Array_u64Resize(&(newHashmap.hashes), newCapacity);
	u32 oldLength = hashmap->data.length;
	Array_Hashmap_SoundInfo_EntryReserve(&(newHashmap.data), oldLength);
	for (u32 i = 0; i < newCapacity; i++)
		*Array_u64GetPtr(&(newHashmap.hashes), i) = (u32)(-1);
	for (u32 i = 0; i < oldLength; i++) {
		Hashmap_SoundInfo_Entry* entry =
			Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), i);
		Hashmap_SoundInfozInternalInsert(&newHashmap, entry->key, &(entry->value));
	}
	copyMemory(&newHashmap, hashmap, sizeof(Hashmap_SoundInfo));
	;
}
__forceinline void
Hashmap_SoundInfozInternalGrow(Hashmap_SoundInfo* hashmap)
{
	;
	u32 newCapacity = 2 * hashmap->data.length + 2;
	Hashmap_SoundInfozInternalRehash(hashmap, newCapacity);
	;
}
__forceinline Hashmap_SoundInfo_Entry*
Hashmap_SoundInfozInternalFindFirst(Hashmap_SoundInfo* hashmap, HashmapKey key)
{
	;
	u32 index = Hashmap_SoundInfozInternalFindOrFail(hashmap, key);
	if (index == (u32)(-1)) {
		;
		return 0;
	};
	return Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index);
}
__forceinline void
Hashmap_SoundInfozInternalInsert(Hashmap_SoundInfo* hashmap, HashmapKey key,
	SoundInfo* value)
{
	if (hashmap->hashes.length == 0)
		Hashmap_SoundInfozInternalGrow(hashmap);
	u32 next = Hashmap_SoundInfozInternalMake(hashmap, key);
	Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), next)->value = *value;
	if (Hashmap_SoundInfozInternalFull(hashmap))
		Hashmap_SoundInfozInternalGrow(hashmap);
}
__forceinline Hashmap_SoundInfo_Entry*
Hashmap_SoundInfozInternalFindNext(Hashmap_SoundInfo* hashmap,
	Hashmap_SoundInfo_Entry* entry)
{
	;
	if (!entry) {
		;
		return 0;
	}
	u32 index = entry->next;
	while (index != (u32)(-1)) {
		Hashmap_SoundInfo_Entry* found =
			Array_Hashmap_SoundInfo_EntryGetPtr(&(hashmap->data), index);
		if (found->key == entry->key) {
			;
			return found;
		}
		index = found->next;
	};
	return 0;
};
