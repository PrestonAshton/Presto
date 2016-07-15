#ifndef QUEST_CONTAINERS_HASHMAP_H
#define QUEST_CONTAINERS_HASHMAP_H

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

#define InvalidHashmapIndex (usize)(-1)

#define HashmapCreate() \
	(Hashmap) \
	{ \
		{0, 0, sizeof(usize), ALIGNOF(usize), 0}, \
		{0, 0, sizeof(HashmapEntry), ALIGNOF(HashmapEntry), 0} \
	}

#define HashmapCreateNonCast() \
	{ \
		{0, 0, sizeof(usize), ALIGNOF(usize), 0}, \
		{0, 0, sizeof(HashmapEntry), ALIGNOF(HashmapEntry), 0} \
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

forceinline b8 HashmapHas(const Hashmap* hashmap, Key key)
{
	return HashmapInternalFindOrFail(hashmap, key) != InvalidHashmapIndex;
}

forceinline void* HashmapGet(const Hashmap* hashmap, Key key)
{
	usize index = HashmapInternalFindOrFail(hashmap, key);
	Assert(index != InvalidHashmapIndex);
	return ArrayGetType(&(hashmap->data), index, HashmapEntry)->value;
}
forceinline void* HashmapGetDefault(const Hashmap* hashmap, Key key, void* defaultValue)
{
	usize index = HashmapInternalFindOrFail(hashmap, key);
	if (index == InvalidHashmapIndex)
		return defaultValue;
	return ArrayGetType(&(hashmap->data), index, HashmapEntry)->value;
}

forceinline void HashmapSet(Hashmap* hashmap, Key key, const void* value)
{
	if (hashmap->hashes.length == 0)
		HashmapInternalGrow(hashmap);

	usize index = HashmapInternalFindOrMake(hashmap, key);

	// We need to make a copy of this memory that we are given
	//void* ourCopy = spawn()
	
	ArrayGetType(&(hashmap->data), index, HashmapEntry)->value = value;
	if (HashmapInternalFull(hashmap))
		HashmapInternalGrow(hashmap);
}
forceinline void HashmapRemove(Hashmap* hashmap, Key key)
{
	HashmapInternalFindAndErase(hashmap, key);
}

forceinline void HashmapReserve(Hashmap* hashmap, Key key, usize capacity)
{
	HashmapInternalRehash(hashmap, capacity);
}
forceinline void HashmapClear(Hashmap* hashmap)
{
	ArrayClear(&(hashmap->data));
	ArrayClear(&(hashmap->hashes));
}


forceinline void HashmapInternalErase(Hashmap* hashmap, const FindResult* foundResult)
{
	if (foundResult->dataPreviousIndex == InvalidHashmapIndex)
		ArrayGetValue(&(hashmap->hashes), foundResult->hashIndex, usize) = ArrayGetType(&(hashmap->data), foundResult->dataIndex, HashmapEntry)->next;
	else
		ArrayGetType(&(hashmap->data), foundResult->dataPreviousIndex, HashmapEntry)->next = ArrayGetType(&(hashmap->data), foundResult->dataIndex, HashmapEntry)->next;

	if (foundResult->dataIndex == hashmap->data.length - 1)
	{
		ArrayDele(&hashmap->data);
		return;
	}

	ArrayGetValue(&(hashmap->data), foundResult->dataIndex, HashmapEntry) = ArrayGetValue(&(hashmap->data), hashmap->data.length - 1, HashmapEntry);

	FindResult last = HashmapInternalFindByKey(hashmap, ((HashmapEntry*)(ArrayGet(&hashmap->data, foundResult->dataIndex)))->key);

	if (last.dataIndex == InvalidHashmapIndex)
		ArrayGetValue(&(hashmap->hashes), last.hashIndex, usize) = foundResult->dataIndex;
	else
		ArrayGetType(&(hashmap->data), last.dataIndex, HashmapEntry)->next = foundResult->dataIndex;
}
forceinline usize HashmapInternalAddEntry(Hashmap* hashmap, Key key)
{
	HashmapEntry newEntry;
	newEntry.key = key;
	newEntry.next = InvalidHashmapIndex;
	usize entryIndex = hashmap->data.length;
	ArrayPushBack(&hashmap->data, &newEntry);

	return entryIndex;
}
forceinline void HashmapInternalFindAndErase(Hashmap* hashmap, Key key)
{
	const FindResult fr = HashmapInternalFindByKey(hashmap, key);
	if (fr.dataIndex != InvalidHashmapIndex)
		HashmapInternalErase(hashmap, &fr);
}
forceinline FindResult HashmapInternalFindByKey(const Hashmap* hashmap, Key key)
{
	FindResult fr;
	fr.hashIndex = InvalidHashmapIndex;
	fr.dataIndex = InvalidHashmapIndex;
	fr.dataPreviousIndex = InvalidHashmapIndex;

	if (hashmap->hashes.length == 0)
		return fr;

	fr.hashIndex = key % hashmap->hashes.length;
	fr.dataIndex = ArrayGetValue(&(hashmap->hashes), fr.hashIndex, usize);
	while (fr.dataIndex != InvalidHashmapIndex)
	{
		if (ArrayGetType(&(hashmap->data), fr.dataIndex, HashmapEntry)->key == key)
			return fr;

		fr.dataPreviousIndex = fr.dataIndex;
		fr.dataIndex = ArrayGetType(&(hashmap->data), fr.dataIndex, HashmapEntry)->next;
	}

	return fr;
}
forceinline FindResult HashmapInternalFindByEntry(const Hashmap* hashmap, HashmapEntry* entry)
{
	FindResult fr;
	fr.hashIndex = InvalidHashmapIndex;
	fr.dataIndex = InvalidHashmapIndex;
	fr.dataPreviousIndex = InvalidHashmapIndex;

	if (hashmap->hashes.length == 0 || !entry)
		return fr;

	fr.hashIndex = entry->key % hashmap->hashes.length;
	fr.dataIndex = ArrayGetValue(&(hashmap->hashes), fr.hashIndex, usize);
	while (fr.dataIndex != InvalidHashmapIndex)
	{
		if (ArrayGet(&(hashmap->data), fr.dataIndex) == entry)
			return fr;
		fr.dataPreviousIndex = fr.dataIndex;
		fr.dataIndex = ArrayGetType(&(hashmap->data), fr.dataIndex, HashmapEntry)->next;
	}

	return fr;
}
forceinline usize HashmapInternalFindOrFail(const Hashmap* hashmap, Key key)
{
	return (HashmapInternalFindByKey(hashmap, key)).dataIndex;
}
forceinline usize HashmapInternalMake(Hashmap* hashmap, Key key)
{
	FindResult fr = HashmapInternalFindByKey(hashmap, key);
	const usize index = HashmapInternalAddEntry(hashmap, key);

	if (fr.dataPreviousIndex == InvalidHashmapIndex)
		ArrayGetValue(&(hashmap->hashes), fr.hashIndex, usize) = index;
	else
		ArrayGetType(&(hashmap->data), fr.dataPreviousIndex, HashmapEntry)->next = index;

	ArrayGetType(&(hashmap->data), index, HashmapEntry)->next = fr.dataIndex;

	return index;
}
forceinline usize HashmapInternalFindOrMake(Hashmap* hashmap, Key key)
{
	FindResult fr = HashmapInternalFindByKey(hashmap, key);
	if (fr.dataIndex != InvalidHashmapIndex)
		return fr.dataIndex;

	usize index = HashmapInternalAddEntry(hashmap, key);
	if (fr.dataPreviousIndex == InvalidHashmapIndex)
		ArrayGetValue(&(hashmap->hashes), fr.hashIndex, usize) = index;
	else
		ArrayGetType(&(hashmap->data), fr.dataPreviousIndex, HashmapEntry)->next = index;

	return index;
}
forceinline b8 HashmapInternalFull(Hashmap* hashmap)
{
	return hashmap->data.length >= 0.75f * hashmap->hashes.length;
}

Hashmap emptyHashmap = HashmapCreateNonCast();

forceinline void HashmapInternalRehash(Hashmap* hashmap, usize newCapacity)
{
	Hashmap newHashmap = HashmapCreate();
	ArrayResize(&(newHashmap.hashes), newCapacity);
	usize oldLength = hashmap->data.length;
	ArrayReserve(&(newHashmap.data), oldLength);

	for (usize i = 0; i < newCapacity; i++)
		ArrayGetValue(&(newHashmap.hashes), i, usize) = InvalidHashmapIndex;

	for (usize i = 0; i < oldLength; i++)
	{
		HashmapEntry* entry = ArrayGetType(&(hashmap->data), i, HashmapEntry);
		HashmapSet(&newHashmap, entry->key, entry->value);
	}

	copyMemory(&newHashmap, &hashmap, sizeof(Hashmap));
	copyMemory(&emptyHashmap, &newHashmap, sizeof(Hashmap));
}
forceinline void HashmapInternalGrow(Hashmap* hashmap)
{
	usize newCapacity = 2 * hashmap->data.length + 2;
	HashmapInternalRehash(hashmap, newCapacity);
}
forceinline const HashmapEntry* HashmapInternalFindFirst(const Hashmap* hashmap, Key key)
{
	usize index = HashmapInternalFindOrFail(hashmap, key);
	if (index == InvalidHashmapIndex)
		return NULL;

	return ArrayGetType(&(hashmap->data), index, HashmapEntry);
}
forceinline const HashmapEntry* HashmapInternalFindNext(const Hashmap* hashmap, HashmapEntry* entry)
{
	if (!entry)
		return NULL;

	usize index = entry->next;

	while (index != InvalidHashmapIndex)
	{
		HashmapEntry* found = ArrayGetType(&(hashmap->data), index, HashmapEntry);
		if (found->key == entry->key)
			return found;
		index = found->next;
	}
	return NULL;
}

#endif
