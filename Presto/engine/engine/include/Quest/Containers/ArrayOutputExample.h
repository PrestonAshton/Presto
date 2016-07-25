typedef struct
{
  usize* data;
  u32 length;
  u32 capacity;
} Array_usize;
typedef char
  static_assertion_Size_Of_Array_usize[(sizeof(Array_usize) == 16) ? 1 : -1];
usize* Array_usizeGetPtr(Array_usize* a, u32 index);
usize Array_usizeGetValue(Array_usize* a, u32 index);
void Array_usizeSet(Array_usize* a, u32 index, usize value);
void Array_usizeSetPtr(Array_usize* a, u32 index, usize* value);
u32 Array_usizeSize(const Array_usize* a);
void Array_usizeEquals(Array_usize* a, const Array_usize* b);
void Array_usizePushBack(Array_usize* a, usize item);
void Array_usizePushBackPtr(Array_usize* a, usize* item);
void Array_usizeDele(Array_usize* a);
b8 Array_usizeEmpty(const Array_usize* a);
void* Array_usizeBegin(Array_usize* a);
void* Array_usizeEnd(Array_usize* a);
void* Array_usizeBack(Array_usize* a);
void Array_usizeClear(Array_usize* a);
void Array_usizeTrim(Array_usize* a);
u32 Array_usizeAppend(Array_usize* a, const usize* items, u32 count);
void Array_usizeResize(Array_usize* a, u32 length);
void Array_usizeSetCapacity(Array_usize* a, u32 capacity);
void Array_usizeReserve(Array_usize* a, u32 capacity);
void Array_usizeGrow(Array_usize* a, u32 minCapacity);
__forceinline usize*
Array_usizeGetPtr(Array_usize* a, u32 index)
{
  static b8 ASSERTBLOCK__LINE__ = 0;
  if (!(index < a->length))
    ForceAssert(
      L"index < a->length", 0,
      "D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
      23, &ASSERTBLOCK__LINE__);
  ;
  return a->data + index;
}
__forceinline usize
Array_usizeGetValue(Array_usize* a, u32 index)
{
  static b8 ASSERTBLOCK__LINE__ = 0;
  if (!(index < a->length))
    ForceAssert(
      L"index < a->length", 0,
      "D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
      23, &ASSERTBLOCK__LINE__);
  ;
  return *(a->data + index);
}
__forceinline void
Array_usizeSet(Array_usize* a, u32 index, usize value)
{
  *(Array_usizeGetPtr(a, index)) = value;
}
__forceinline void
Array_usizeSetPtr(Array_usize* a, u32 index, usize* value)
{
  copyMemory(value, Array_usizeGetPtr(a, index), sizeof(usize));
}
__forceinline u32
Array_usizeSize(const Array_usize* a)
{
  return a->length * sizeof(usize);
}
__forceinline void
Array_usizeEquals(Array_usize* a, const Array_usize* b)
{
  Array_usizeResize(a, b->length);
  copyMemory(b->data, a->data, Array_usizeSize(b));
}
__forceinline void
Array_usizePushBack(Array_usize* a, usize item)
{
  if (a->length == a->capacity)
    Array_usizeGrow(a, 0);
  Array_usizeSet(a, a->length, item);
}
__forceinline void
Array_usizePushBackPtr(Array_usize* a, usize* item)
{
  if (a->length == a->capacity)
    Array_usizeGrow(a, 0);
  Array_usizeSetPtr(a, a->length, item);
}
__forceinline void
Array_usizeDele(Array_usize* a)
{
  static b8 ASSERTBLOCK__LINE__ = 0;
  if (!(a->length > 0))
    ForceAssert(
      L"a->length > 0", 0,
      "D:\\Presto\\Presto\\engine\\engine\\include\\Quest/Containers/Types.h",
      23, &ASSERTBLOCK__LINE__);
  ;
  a->length--;
}
__forceinline b8
Array_usizeEmpty(const Array_usize* a)
{
  return a->length == 0;
}
__forceinline void*
Array_usizeBegin(Array_usize* a)
{
  return a->data;
}
__forceinline void*
Array_usizeEnd(Array_usize* a)
{
  return a->data + a->length;
}
__forceinline void*
Array_usizeBack(Array_usize* a)
{
  return a->data + a->length - 1;
}
__forceinline void
Array_usizeClear(Array_usize* a)
{
  Array_usizeResize(a, 0);
}
__forceinline void
Array_usizeTrim(Array_usize* a)
{
  Array_usizeSetCapacity(a, a->length);
}
__forceinline u32
Array_usizeAppend(Array_usize* a, const usize* items, u32 count)
{
  if (a->capacity <= a->length + count)
    ArrayusizeGrow(a, a->length + count);
  copyMemory(items, a->data + a->length, count * sizeof(usize));
  return a->length += count;
}
__forceinline void
Array_usizeResize(Array_usize* a, u32 length)
{
  if (length > a->capacity)
    ArrayusizeGrow(a, length);
  a->length = length;
}
__forceinline void
Array_usizeSetCapacity(Array_usize* a, u32 capacity)
{
  if (capacity == a->capacity)
    return;
  if (capacity < a->length)
    ArrayResize(a, capacity);
  usize* data = 0;
  data = heapAllocate(capacity * sizeof(usize), (vol)(4));
  copyMemory(a->data, data, Array_usizeSize(a));
  heapDeallocate(a->data);
  a->data = data;
  a->capacity = capacity;
}
__forceinline void
Array_usizeReserve(Array_usize* a, u32 capacity)
{
  if (capacity > a->capacity)
    Array_usizeSetCapacity(a, capacity);
}
__forceinline void
Array_usizeGrow(Array_usize* a, u32 minCapacity)
{
  u32 capacity = 2 * a->capacity + 2;
  if (capacity < minCapacity)
    capacity = minCapacity;
  ArrayusizeSetCapacity(a, capacity);
}
