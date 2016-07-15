#ifndef QUEST_CONTAINERS_ARRAY_H
#define QUEST_CONTAINERS_ARRAY_H

#include <Quest/Common.h>

#define DEFINE_ARRAY_STRUCT_64(type)																																						\
typedef struct																																												\
{																																															\
	type * data;																																											\
																																															\
	u32 length;																																												\
	u32 capacity;																																											\
} Array_ ## type ;

#define DEFINE_ARRAY_STRUCT_32(type)																																						\
typedef struct																																												\
{																																															\
	type * data;																																											\
	u32 padding;																																											\
																																															\
	u32 length;																																												\
	u32 capacity;																																											\
} Array_ ## type ;

#define DEFINE_ARRAY_CHECK(type)																																							\
STATIC_ASSERT(sizeof( Array_ ## type ) == 16, Size_Of_Array_ ## type );																														\
// <-- Array | 128 bits | 16 bytes -->

#ifdef QUEST_ARCHITECTURE_X32
#define DEFINE_ARRAY_STRUCT(type) DEFINE_ARRAY_STRUCT_32(type)
#else
#define DEFINE_ARRAY_STRUCT(type) DEFINE_ARRAY_STRUCT_64(type)
#endif

#define DEFINE_ARRAY_FUNCTONS(type)																																							\
type * Array_ ## type ## GetPtr(Array_ ## type * a, u32 index);																																\
type Array_ ## type ## GetValue(Array_ ## type * a, u32 index);																																\
void Array_ ## type ## Set(Array_ ## type * a, u32 index, type value);																														\
u32 Array_ ## type ## Size(const Array_ ## type * a);																																		\
void Array_ ## type ## Equals(Array_ ## type * a, const Array_ ## type * b);																												\																											\
void Array_ ## type ## PushBack(Array_ ## type * a, type item);																																\
void Array_ ## type ## Dele(Array_ ## type * a);																																			\
b8 Array_ ## type ## Empty(const Array_ ## type * a);																																		\
void* Array_ ## type ## Begin(Array_ ## type * a);																																			\
void* Array_ ## type ## End(Array_ ## type * a);																																			\
void* Array_ ## type ## Back(Array_ ## type * a);																																			\
void Array_ ## type ## Clear(Array_ ## type * a);																																			\
void Array_ ## type ## Trim(Array_ ## type * a);																																			\
u32 Array_ ## type ## Append(Array_ ## type * a, const type * items, u32 count);																											\
void Array_ ## type ## Resize(Array_ ## type * a, u32 length);																																\
void Array_ ## type ## SetCapacity(Array_ ## type * a, u32 capacity);																														\
void Array_ ## type ## Reserve(Array_ ## type * a, u32 capacity);																															\
void Array_ ## type ## Grow(Array_ ## type * a, u32 minCapacity);


#define DEFINE_ARRAY_FUNCTION_IMPLEMENTATIONS(type)																																			\
																																															\
forceinline type * Array_ ## type ## GetPtr(Array_ ## type * a, u32 index)																													\
{																																															\
	Assert(index < a->length);																																								\
	return data + index;																																									\
}																																															\
																																															\
forceinline type Array_ ## type ## GetValue(Array_ ## type * a, u32 index)																													\
{																																															\
	Assert(index < a->length);																																								\
	return *(data + index);																																									\
}																																															\
																																															\
forceinline void Array_ ## type ## Set(Array_ ## type * a, u32 index, type value)																											\
{																																															\
	*( Array_ ## type ## GetPtr(a, index) ) = value;																																		\
}																																															\
																																															\
forceinline u32 Array_ ## type ## Size(const Array_ ## type * a)																															\
{																																															\
	return a->length * sizeof( type );																																						\
}																																															\
																																															\
forceinline void Array_ ## type ## Equals(Array_ ## type * a, const Array_ ## type * b)																										\
{																																															\
	Array_ ## type ## Resize( a, b->length );																																				\
	copyMemory(b->data, a->data, Array_ ## type ## Size(b));																																\
}																																															\
																																															\
forceinline void Array_ ## type ## PushBack(Array_ ## type * a, type item)																													\
{																																															\
	if (a->length == a->capacity)																																							\
		Array_ ## type ## Grow(a, 0);																																						\
	Array_ ## type ## Set(a, a->length, item);																																				\
}																																															\
																																															\
forceinline void Array_ ## type ## Dele(Array_ ## type * a)																																	\
{																																															\
	Assert(a->length > 0);																																									\
	a->length--;																																											\
}																																															\
																																															\
forceinline b8 Array_ ## type ## Empty(const Array_ ## type * a)																															\
{																																															\
	return a->length == 0;																																									\
}																																															\
																																															\
forceinline void* Array_ ## type ## Begin(Array_ ## type * a)																																\
{																																															\
	return a->data;																																											\
}																																															\
																																															\
forceinline void* Array_ ## type ## End(Array_ ## type * a)																																	\
{																																															\
	return a->data + a->length;																																								\
}																																															\
																																															\
forceinline void* Array_ ## type ## Back(Array_ ## type * a)																																\
{																																															\
	return a->data + a->length - 1;																																							\
}																																															\
																																															\
forceinline void Array_ ## type ## Clear(Array_ ## type * a)																																\
{																																															\
	Array_ ## type ## Resize(a, 0);																																							\
}																																															\
																																															\
forceinline void Array_ ## type ## Trim(Array_ ## type * a)																																	\
{																																															\
	Array_ ## type ## SetCapacity(a, a->length);																																			\
}																																															\
																																															\
forceinline u32 Array_ ## type ## Append(Array_ ## type * a, const type * items, u32 count)																									\
{																																															\
	if (a->capacity <= a->length + count)																																					\
		Array ## type ## Grow(a, a->length + count);																																		\
	copyMemory(items, a->data + length, count * sizeof( type ) );																															\
	return a->length += count;																																								\
}																																															\
																																															\
forceinline void Array_ ## type ## Resize(Array_ ## type * a, u32 length)																													\
{																																															\
	if (length > a->capacity)																																								\
		Array ## type ## Grow(a, length);																																					\
	a->length = length;																																										\
}																																															\
																																															\
forceinline void Array_ ## type ## SetCapacity(Array_ ## type * a, u32 capacity)																											\
{																																															\
	if (capacity == a->capacity)																																							\
		return;																																												\
																																															\
	if (capacity < a->length)																																								\
		ArrayResize(a, capacity);																																							\
																																															\
	type * data = NULL;																																										\
	data = spawn(capacity * sizeof(type));																																					\
	copyMemory(a->data, data, Array_ ## type ## Size(a) );																																	\
	murder(a->data);																																										\
	a->data = data;																																											\
	a->capacity = capacity;																																									\
}																																															\
																																															\
forceinline void Array_ ## type ## Reserve(Array_ ## type * a, u32 capacity)																												\
{																																															\
	if (capacity > a->capacity)																																								\
		Array_ ## type ## SetCapacity(a, capacity);																																			\
}																																															\
																																															\
forceinline void Array_ ## type ## Grow(Array_ ## type * a, u32 minCapacity)																												\
{																																															\
	u32 capacity = 2 * a->capacity + 2;																																						\
	if (capacity < minCapacity)																																								\
		capacity = minCapacity;																																								\
																																															\
	Array ## type ## SetCapacity(a, capacity);																																				\
}																																															\

#define DEFINE_ARRAY(type)																																									\
			DEFINE_ARRAY_STRUCT(type)																																						\
			DEFINE_ARRAY_CHECK(type)																																						\
			DEFINE_ARRAY_FUNCTONS(type)																																						\
			DEFINE_ARRAY_FUNCTION_IMPLEMENTATIONS(type)																																		\

#endif
