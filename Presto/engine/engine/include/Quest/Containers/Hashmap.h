#ifndef QUEST_CONTAINERS_HASHMAP_H
#define QUEST_CONTAINERS_HASHMAP_H

#include <Quest/Common.h>
#include <Quest/Containers/Array.h>
#include <Quest/Utility/Console.h>

// TODO: Multi Hashmap Stuff!

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

// <-- HashmapFindResult | 128 bits | 16 bytes -->
STATIC_ASSERT(sizeof(HashmapFindResult) == 16, Size_Of_HashmapFindResult);

#define DEFINE_HASHMAP_STRUCT_64(type) \
typedef struct \
{ \
	HashmapKey key; /* u64 */ \
	u32 next; \
	u32 padding; \
	type value; \
} Hashmap_ ## type ## _Entry; \
	DEFINE_ARRAY(Hashmap_ ## type ## _Entry) \
 \
typedef struct \
{ \
	Array_u64 hashes; \
	Array_Hashmap_ ## type ## _Entry data; \
} Hashmap_ ## type ; \

#define DEFINE_HASHMAP_STRUCT_32(type) \
typedef struct \
{ \
	HashmapKey key; /* u64 */ \
	u32 next; \
	type value; \
} Hashmap_ ## type ## _Entry; \
	DEFINE_ARRAY(Hashmap_ ## type ## _Entry) \
 \
typedef struct \
{ \
	Array_u64 hashes; \
	Array_Hashmap_ ## type ## _Entry data; \
} Hashmap_ ## type ; \

#ifdef QUEST_ARCHITECTURE_X32
#define DEFINE_HASHMAP_STRUCT(type) DEFINE_HASHMAP_STRUCT_32(type)
#else
#define DEFINE_HASHMAP_STRUCT(type) DEFINE_HASHMAP_STRUCT_64(type)
#endif

#define DEFINE_HASHMAP_CHECK(type)                                               \
  \
STATIC_ASSERT(sizeof(Hashmap_##type) == 32, Size_Of_Hashmap_##type); \
// <-- Hashmap | 256 bits | 32 bytes -->

#define DEFINE_HASHMAP_FUNCTIONS(type)\
	b8 Hashmap_##type##Has(Hashmap_##type * hashmap, HashmapKey key); \
\
	type * Hashmap_##type##GetPtr(Hashmap_##type * hashmap, HashmapKey key); \
	type * Hashmap_##type##GetPtrDefault(Hashmap_##type * hashmap, HashmapKey key, type * defaultValue ); \
	type Hashmap_##type##GetValue(Hashmap_##type * hashmap, HashmapKey key); \
	type Hashmap_##type##GetValueDefault(Hashmap_##type * hashmap, HashmapKey key, type defaultValue ); \
	\
	void Hashmap_##type##SetByValue(Hashmap_##type * hashmap, HashmapKey key, type value ); \
	void Hashmap_##type##SetByPtr(Hashmap_##type * hashmap, HashmapKey key, type * value ); \
	\
	void Hashmap_##type##Remove(Hashmap_##type * hashmap, HashmapKey key); \
\
	void Hashmap_##type##Reserve(Hashmap_##type * hashmap, HashmapKey key, u32 capacity); \
	\
	void Hashmap_##type##Clear(Hashmap_##type * hashmap); \
	\
	void Hashmap_##type##zInternalErase(Hashmap_##type * hashmap, HashmapFindResult* findResult);\
	u32 Hashmap_##type##zInternalAddEntry(Hashmap_##type * hashmap, HashmapKey key); \
	void Hashmap_##type##zInternalFindAndErase(Hashmap_##type * hashmap, HashmapKey key); \
	HashmapFindResult Hashmap_##type##zInternalFindByKey(Hashmap_##type * hashmap, HashmapKey key); \
	HashmapFindResult Hashmap_##type##zInternalFindByEntry(Hashmap_##type * hashmap, Hashmap_##type##_Entry* entry); \
	\
	u32 Hashmap_##type##zInternalFindOrFail(Hashmap_##type * hashmap, HashmapKey key); \
	u32 Hashmap_##type##zInternalMake(Hashmap_##type * hashmap, HashmapKey key); \
	u32 Hashmap_##type##zInternalFindOrMake(Hashmap_##type * hashmap, HashmapKey key); \
	b8 Hashmap_##type##zInternalFull(Hashmap_##type * hashmap); \
	void Hashmap_##type##zInternalRehash(Hashmap_##type * hashmap, u32 newCapacity); \
	void Hashmap_##type##zInternalGrow(Hashmap_##type * hashmap); \
	void Hashmap_##type##zInternalInsert(Hashmap_##type * hashmap, HashmapKey key, type* value ); \
	Hashmap_##type##_Entry* Hashmap_##type##zInternalFindFirst(Hashmap_##type * hashmap, HashmapKey key); \
	Hashmap_##type##_Entry* Hashmap_##type##zInternalFindNext(Hashmap_##type * hashmap, Hashmap_##type##_Entry * entry);

#define DEFINE_HASHMAP_FUNCTION_IMPLEMENTATIONS(type)\
		forceinline b8 Hashmap_##type##Has(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("Has"))); \
			b8 findOrFailResult = Hashmap_##type##zInternalFindOrFail(hashmap, key) != InvalidHashmapIndex;\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("Has (1)"))); \
			return findOrFailResult;\
		}\
	\
		forceinline type * Hashmap_##type##GetPtr(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("GetPtr"))); \
			u32 index = Hashmap_##type##zInternalFindOrFail(hashmap, key);\
			Assert(index != InvalidHashmapIndex);\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("GetPtr (1)"))); \
			return &(Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index)->value);\
		}\
		forceinline type * Hashmap_##type##GetPtrDefault(Hashmap_##type * hashmap, HashmapKey key, type * defaultValue ) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("GetPtrDefault"))); \
			u32 index = Hashmap_##type##zInternalFindOrFail(hashmap, key);\
			if (index == InvalidHashmapIndex) \
			{\
					CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("GetPtrDefault (1)"))); \
					return defaultValue;\
			}\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("GetPtrDefault (2)"))); \
			return &(Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index)->value);\
		}\
		forceinline type Hashmap_##type##GetValue(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("GetValue"))); \
			u32 index = Hashmap_##type##zInternalFindOrFail(hashmap, key);\
			Assert(index != InvalidHashmapIndex);\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("GetValue (1)"))); \
			return Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index)->value;\
		}\
		forceinline type Hashmap_##type##GetValueDefault(Hashmap_##type * hashmap, HashmapKey key, type defaultValue ) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("GetValueDefault"))); \
			u32 index = Hashmap_##type##zInternalFindOrFail(hashmap, key);\
			if (index == InvalidHashmapIndex)\
			{\
				CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("GetValueDefault (1)"))); \
				return defaultValue;\
			}\
			return Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index)->value;\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("GetValueDefault (2)"))); \
		}\
		\
		forceinline void Hashmap_##type##SetByValue(Hashmap_##type * hashmap, HashmapKey key, type value ) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("SetByValue"))); \
			if (hashmap->hashes.length == 0)\
				Hashmap_##type##zInternalGrow(hashmap);\
\
			u32 index = Hashmap_##type##zInternalFindOrMake(hashmap, key);\
\
			Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index)->value = value;\
\
			if (Hashmap_##type##zInternalFull(hashmap))\
				Hashmap_##type##zInternalGrow(hashmap);\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("SetByValue (1)"))); \
		}\
		forceinline void Hashmap_##type##SetByPtr(Hashmap_##type * hashmap, HashmapKey key, type * value )\
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("SetByPtr"))); \
			if (hashmap->hashes.length == 0)\
				Hashmap_##type##zInternalGrow(hashmap);\
\
			u32 index = Hashmap_##type##zInternalFindOrMake(hashmap, key);\
\
			Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index)->value = *value;\
\
			if (Hashmap_##type##zInternalFull(hashmap))\
				Hashmap_##type##zInternalGrow(hashmap);\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("SetByPtr (1)"))); \
		} \
		\
		forceinline void Hashmap_##type##Remove(Hashmap_##type * hashmap, HashmapKey key)\
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("Remove"))); \
			Hashmap_##type##zInternalFindAndErase(hashmap, key);\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("Remove (1)"))); \
		}\
		\
		forceinline void Hashmap_##type##Reserve(Hashmap_##type * hashmap, HashmapKey key, u32 capacity) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("Reserve"))); \
			Hashmap_##type##zInternalRehash(hashmap, capacity);\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("Reserve (1)"))); \
		}\
		\
		forceinline void Hashmap_##type##Clear(Hashmap_##type * hashmap) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("Clear"))); \
			Array_u64Clear(&(hashmap->hashes)); \
			Array_Hashmap_ ## type ## _EntryClear(&(hashmap->data)); \
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("Clear (1)"))); \
		}\
		\
		forceinline void Hashmap_##type##zInternalErase(Hashmap_##type * hashmap, HashmapFindResult* findResult)\
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalErase"))); \
			if (findResult->dataPreviousIndex == InvalidHashmapIndex)\
				*Array_u64GetPtr(&(hashmap->hashes), findResult->hashIndex) = Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), findResult->dataIndex)->next;\
			else\
				Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), findResult->dataPreviousIndex)->next = Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), findResult->dataIndex)->next;\
\
			if (findResult->dataIndex == hashmap->data.length - 1)\
			{\
				Array_Hashmap_ ## type ## _EntryDele(&(hashmap->data)); \
				CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalErase (1)"))); \
				return;\
			}\
\
			*Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), findResult->dataIndex) = Array_Hashmap_ ## type ## _EntryGetValue(&(hashmap->data), hashmap->data.length - 1);\
\
			HashmapFindResult last = Hashmap_##type##zInternalFindByKey(hashmap, Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), findResult->dataIndex)->key);\
\
			if (last.dataIndex == InvalidHashmapIndex)\
				*Array_u64GetPtr(&(hashmap->hashes), last.hashIndex) = findResult->dataIndex;\
			else\
				Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), last.dataIndex)->next = findResult->dataIndex;\
\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V(#type) V("zInternalErase (2)"))); \
}\
		forceinline u32 Hashmap_##type##zInternalAddEntry(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalAddEntry"))); \
			Hashmap_ ## type ## _Entry newEntry; \
			newEntry.key = key; \
			newEntry.next = InvalidHashmapIndex; \
			u32 entryIndex = hashmap->data.length; \
			Array_Hashmap_ ## type ## _EntryPushBackPtr(&(hashmap->data), &newEntry);\
\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalAddEntry (1)"))); \
			return entryIndex;\
		}\
		forceinline void Hashmap_##type##zInternalFindAndErase(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindAndErase"))); \
			HashmapFindResult fr = Hashmap_##type##zInternalFindByKey(hashmap, key);\
			if (fr.dataIndex != InvalidHashmapIndex)\
				Hashmap_##type##zInternalErase(hashmap, &fr);\
		}\
		forceinline HashmapFindResult Hashmap_##type##zInternalFindByKey(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindByKey"))); \
			HashmapFindResult fr;\
			fr.hashIndex = InvalidHashmapIndex;\
			fr.dataIndex = InvalidHashmapIndex;\
			fr.dataPreviousIndex = InvalidHashmapIndex;\
			\
			if (hashmap->hashes.length == 0)\
			{\
				CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V(#type) V("zInternalFindByKey (1)"))); \
				return fr; \
			}\
			\
			fr.hashIndex = key % hashmap->hashes.length; \
			fr.dataIndex = Array_u64GetValue(&(hashmap->hashes), fr.hashIndex); \
			while (fr.dataIndex != InvalidHashmapIndex)\
			{\
				if (Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), fr.dataIndex)->key == key)\
				{\
					CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindByKey (2)"))); \
					return fr;\
				}\
	\
				fr.dataPreviousIndex = fr.dataIndex;\
				fr.dataIndex = Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), fr.dataIndex)->next;\
			}\
\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindByKey (3)"))); \
			return fr;\
		}\
		forceinline HashmapFindResult Hashmap_##type##zInternalFindByEntry(Hashmap_##type * hashmap, Hashmap_##type##_Entry * entry) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindByEntry"))); \
			HashmapFindResult fr;\
			fr.hashIndex = InvalidHashmapIndex;\
			fr.dataIndex = InvalidHashmapIndex;\
			fr.dataPreviousIndex = InvalidHashmapIndex;\
\
			if (hashmap->hashes.length ==  0 || entry == NULL)\
			{\
				CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindByEntry (1)"))); \
				return fr;\
			}\
\
			fr.hashIndex = entry->key % hashmap->hashes.length;\
			fr.dataIndex = Array_u64GetValue(&(hashmap->hashes), fr.hashIndex);\
			while (fr.dataIndex != InvalidHashmapIndex)\
			{\
				if (Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), fr.dataIndex) == entry)\
				{\
					CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindByEntry (2)"))); \
					return fr;\
				}\
\
					fr.dataPreviousIndex = fr.dataIndex;\
					fr.dataIndex = Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), fr.dataIndex)->next;\
			}\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindByEntry (3)"))); \
			return fr;\
		}\
		\
		forceinline u32 Hashmap_##type##zInternalFindOrFail(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindOrFail"))); \
			u32 dataIndex = Hashmap_##type##zInternalFindByKey(hashmap, key).dataIndex; \
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindOrFail (1)"))); \
			return dataIndex; \
		}\
		forceinline u32 Hashmap_##type##zInternalMake(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalMake"))); \
			HashmapFindResult fr = Hashmap_##type##zInternalFindByKey(hashmap, key);\
			u32 index = Hashmap_##type##zInternalAddEntry(hashmap, key);\
\
			if (fr.dataPreviousIndex == InvalidHashmapIndex)\
				*Array_u64GetPtr(&(hashmap->hashes), fr.hashIndex) = index;\
			else\
				Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), fr.dataPreviousIndex)->next = index;\
\
			Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index)->next = fr.dataIndex;\
\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalMake (1)"))); \
			return index;\
		}\
		forceinline u32 Hashmap_##type##zInternalFindOrMake(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindOrMake"))); \
			HashmapFindResult fr = Hashmap_##type##zInternalFindByKey(hashmap, key);\
			if (fr.dataIndex != InvalidHashmapIndex)\
			{\
				CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindOrMake (1)"))); \
				return fr.dataIndex;\
			}\
\
			u32 index = Hashmap_##type##zInternalAddEntry(hashmap, key);\
			if (fr.dataPreviousIndex == InvalidHashmapIndex)\
				Array_u64Set(&(hashmap->hashes), fr.hashIndex, index);\
			else\
				Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), fr.dataPreviousIndex)->next = index;\
\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindOrMake (2)"))); \
			return index;\
		}\
		forceinline b8 Hashmap_##type##zInternalFull(Hashmap_##type * hashmap) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFull"))); \
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFull (1)"))); \
			return hashmap->data.length >= 0.75f * hashmap->hashes.length;\
		}\
		forceinline void Hashmap_##type##zInternalRehash(Hashmap_##type * hashmap, u32 newCapacity) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalRehash"))); \
			Hashmap_##type newHashmap = { 0 };\
			Array_u64Resize(&(newHashmap.hashes), newCapacity);\
			u32 oldLength = hashmap->data.length;\
			Array_Hashmap_ ## type ## _EntryReserve(&(newHashmap.data), oldLength);\
\
			for (u32 i = 0; i < newCapacity; i++)\
				*Array_u64GetPtr(&(newHashmap.hashes), i) = InvalidHashmapIndex;\
\
			for (u32 i = 0; i < oldLength; i++)\
			{\
				Hashmap_ ## type ## _Entry* entry = Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), i);\
				Hashmap_##type##zInternalInsert(&newHashmap, entry->key, &(entry->value));\
			}\
\
			copyMemory(&newHashmap, hashmap, sizeof(Hashmap_##type) );\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalRehash (1)"))); \
		}\
		forceinline void Hashmap_##type##zInternalGrow(Hashmap_##type * hashmap) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalGrow"))); \
			u32 newCapacity = 2 * hashmap->data.length + 2;\
			Hashmap_##type##zInternalRehash(hashmap, newCapacity);\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalGrow (1)"))); \
		}\
		forceinline Hashmap_##type##_Entry* Hashmap_##type##zInternalFindFirst(Hashmap_##type * hashmap, HashmapKey key) \
		{\
			CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindFirst"))); \
			u32 index = Hashmap_##type##zInternalFindOrFail(hashmap, key);\
			if (index == InvalidHashmapIndex)\
			{\
				CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindFirst (1)"))); \
				return NULL;\
			}\
\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindFirst (2)"))); \
			return Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index);\
		}\
		forceinline void Hashmap_##type##zInternalInsert(Hashmap_##type * hashmap, HashmapKey key, type* value ) \
		{\
			if (hashmap->hashes.length == 0)\
				Hashmap_##type##zInternalGrow(hashmap);\
\
			u32 next = Hashmap_##type##zInternalMake(hashmap, key);\
			Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), next)->value = *value;\
\
			if (Hashmap_##type##zInternalFull(hashmap))\
				Hashmap_##type##zInternalGrow(hashmap);\
		}\
forceinline Hashmap_##type##_Entry* Hashmap_##type##zInternalFindNext(Hashmap_##type * hashmap, Hashmap_##type##_Entry * entry) \
		{ \
		CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindNext"))); \
		if (!entry)\
		{\
			CONTAINER_DEBUG(DBUG(V("RETURN: Hashmap_") V( #type ) V("zInternalFindNext (1)"))); \
			return NULL; \
		}\
			\
		u32 index = entry->next; \
		while (index != InvalidHashmapIndex)\
		{\
			Hashmap_##type##_Entry* found = Array_Hashmap_ ## type ## _EntryGetPtr(&(hashmap->data), index); \
			if (found->key == entry->key)\
			{\
				CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindNext (2)"))); \
				return found;\
			}\
			index = found->next;\
		} \
		CONTAINER_DEBUG(DBUG(V("Hashmap_") V( #type ) V("zInternalFindNext (3)"))); \
		return NULL; \
		}\

#define DEFINE_HASHMAP(type) \
	DEFINE_HASHMAP_STRUCT(type) \
	DEFINE_HASHMAP_CHECK(type) \
	DEFINE_HASHMAP_FUNCTIONS(type) \
	DEFINE_HASHMAP_FUNCTION_IMPLEMENTATIONS(type)

#endif
