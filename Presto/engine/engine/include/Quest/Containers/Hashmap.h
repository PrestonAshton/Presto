#ifndef PSTDLIB_CONTAINERS_HASHMAP_H
#define PSTDLIB_CONTAINERS_HASHMAP_H

#include <Quest/Common.h>
#include <Quest/Containers/Array.h>

typedef u64 Key;

typedef struct
{
	Key key;
	usize next;
	void* value;
} HashmapEntry;

typedef struct
{
	Array hashes;
	Array data;
} Hashmap;

typedef struct
{
	usize hashIndex;
	usize dataIndex;
	usize dataPreviousIndex;
} FindResult;

#define HashmapCreate() \
	(Hashmap) \
	{ \
		{0, 0, sizeof(usize), ALIGNOF(usize), 0}, \
		{0, 0, sizeof(void*), ALIGNOF(void*), 0} \
	}

b8 HashmapHas(const Hashmap* hashmap, Key key);

void* HashmapGet(const Hashmap* hashmap, Key key);
void* HashmapGetDefault(const Hashmap* hashmap, Key key, void* defaultValue);

void HashmapSet(Hashmap* hashmap, Key key, const void* value);
void HashmapRemove(Hashmap* hashmap, Key key);

void HashmapReserve(Hashmap* hashmap, Key key, usize capacity);
void HashmapClear(Hashmap* hashmap);

void HashmapInternalErase(Hashmap* hashmap, const FindResult* foundResult);
usize HashmapInternalAddEntry(Hashmap* hashmap, Key key);
void HashmapInternalFindAndErase(Hashmap* hashmap, Key key);
FindResult HashmapInternalFindByKey(const Hashmap* hashmap, Key key);
FindResult HashmapInternalFindByEntry(const Hashmap* hashmap, HashmapEntry* entry);
usize HashmapInternalFindOrFail(const Hashmap* hashmap, Key key);
usize HashmapInternalMake(Hashmap* hashmap, Key key);
usize HashmapInternalFindOrMake(Hashmap* hashmap, Key key);
b8 HashmapInternalFull(Hashmap* hashmap);
void HashmapInternalRehash(Hashmap* hashmap, usize newCapacity);
void HashmapInternalGrow(Hashmap* hashmap);
const HashmapEntry* HashmapInternalFindFirst(const Hashmap* hashmap, Key key);
const HashmapEntry* HashmapInternalFindNext(const Hashmap* hashmap, HashmapEntry* entry);

//forceinline void HashmapLoad(Hashmap* hashmap, const vchar* path);

forceinline b8 HashmapHas(const Hashmap* hashmap, Key key);

forceinline void* HashmapGet(const Hashmap* hashmap, Key key);
forceinline void* HashmapGetDefault(const Hashmap* hashmap, Key key, void* defaultValue);

forceinline void HashmapSet(Hashmap* hashmap, Key key, const void* value);
forceinline void HashmapRemove(Hashmap* hashmap, Key key);

forceinline void HashmapReserve(Hashmap* hashmap, Key key, usize capacity);
forceinline void HashmapClear(Hashmap* hashmap);

forceinline void HashmapInternalErase(Hashmap* hashmap, const FindResult* foundResult)
{
	if (foundResult->dataPreviousIndex == (usize)(-1))
		*((usize*)(ArrayGet(&hashmap->hashes, foundResult->hashIndex))) = ((HashmapEntry*)(ArrayGet(&hashmap->data, foundResult->dataIndex)))->next;
	else
		((HashmapEntry*)(ArrayGet(&hashmap->data, foundResult->dataPreviousIndex)))->next = ((HashmapEntry*)ArrayGet(&hashmap->data, foundResult->dataIndex))->next;

	if (foundResult->dataIndex == hashmap->data.length - 1)
	{
		ArrayDele(&hashmap->data);
		return;
	}
	*((HashmapEntry*)(ArrayGet(&hashmap->data, foundResult->dataIndex))) = *((HashmapEntry*)ArrayGet(&hashmap->data, hashmap->data.length - 1));

	FindResult last = HashmapInternalFindByKey(hashmap, ((HashmapEntry*)(ArrayGet(&hashmap->data, foundResult->dataIndex)))->key);

	if (last.dataIndex == (usize)(-1))
		*((usize*)(ArrayGet(&hashmap->hashes, last.hashIndex))) = foundResult->dataIndex;
	else
		((HashmapEntry*)(ArrayGet(&hashmap->data, last.dataIndex)))->next = foundResult->dataIndex;
}
forceinline usize HashmapInternalAddEntry(Hashmap* hashmap, Key key)
{
	HashmapEntry newEntry;
	newEntry.key = key;
	newEntry.next = (usize)(-1);
	usize entryIndex = hashmap->data.length;
	ArrayPushBack(&hashmap->data, &newEntry);

	return entryIndex;
}
forceinline void HashmapInternalFindAndErase(Hashmap* hashmap, Key key)
{
	const FindResult fr = HashmapInternalFindByKey(hashmap, key);
	if (fr.dataIndex != (usize)(-1))
		HashmapInternalErase(hashmap, &fr);
}
forceinline FindResult HashmapInternalFindByKey(const Hashmap* hashmap, Key key)
{
	FindResult fr;
	fr.hashIndex = (usize)(-1);
	fr.dataIndex = (usize)(-1);
	fr.dataPreviousIndex = (usize)(-1);
}
forceinline FindResult HashmapInternalFindByEntry(const Hashmap* hashmap, HashmapEntry* entry);
forceinline usize HashmapInternalFindOrFail(const Hashmap* hashmap, Key key);
forceinline usize HashmapInternalMake(Hashmap* hashmap, Key key);
forceinline usize HashmapInternalFindOrMake(Hashmap* hashmap, Key key);
forceinline b8 HashmapInternalFull(Hashmap* hashmap);
forceinline void HashmapInternalRehash(Hashmap* hashmap, usize newCapacity);
forceinline void HashmapInternalGrow(Hashmap* hashmap);
forceinline const HashmapEntry* HashmapInternalFindFirst(const Hashmap* hashmap, Key key);
forceinline const HashmapEntry* HashmapInternalFindNext(const Hashmap* hashmap, HashmapEntry* entry);

#endif
