#ifndef QUEST_CONTAINERS_STRING_H
#define QUEST_CONTAINERS_STRING_H

#include <Quest/Containers/Types.h>

typedef struct
{
	Array_a8 data;
} String;

i32 StrCmp(const String* string, const String* otherString);

u32 StrLength(const String* string);
u32 StrCapacity(const String* string);

u32 StrAppendChar(String* string, a8 character);
u32 StrAppendCStr(String* string, const a8* charArray);
u32 StrAppendStr(String* string, const String* otherString);

a8* StrBegin(String* string);
a8* StrEnd(String* string);

const a8* StrCStr(const String* string);

void StrClear(String* string);
void StrTrim(String* string);
u32 StrFind(const String* string, const String* substring);
void StrResize(String* string, u32 length);
void StrReserve(String* string, u32 capacity);

String StrSubstring(const String* string, u32 begin, u32 end);
b8 StrEqualsStr(const String* string, const String* otherString);
b8 StrEqualsCStr(const String* string, const a8* otherString);

i32 StrCmp(const String* string, const String* otherString)
{
	const a8* string1 = StrCStr(string);
	const a8* string2 = StrCStr(otherString);

	while (*string1 && (*string1 == *string2))
	{
		string1++;
		string2++;
	}

	return *(const a8*)(string1)-*(const u8*)(string2);
}

u32 StrLength(const String* string)
{
	return string->data.length;
}
u32 StrCapacity(const String* string)
{
	return string->data.capacity;
}

u32 StrAppendChar(String* string, a8 character)
{
	Array_a8PushBack(&(string->data), character);
	return string->data.length;
}
u32 StrAppendCStr(String* string, const a8* charArray)
{
	return Array_a8Append(&(string->data), charArray, (u32)(strlen(charArray)));
}
u32 StrAppendStr(String* string, const String* otherString)
{
	return Array_a8Append(&(string->data), StrCStr(otherString), StrLength(otherString));
}

a8* StrBegin(String* string)
{
	return (a8*)Array_a8Begin(&(string->data));
}
a8* StrEnd(String* string)
{
	return (a8*)Array_a8End(&(string->data));
}

const a8* StrCStr(const String* string)
{
	StrAppendChar(((String*)(string)), '\0');
	Array_a8Dele((Array_a8*)(&(string->data)));
	return (const a8*)(StrBegin((String*)(string)));
}

void StrClear(String* string)
{
	Array_a8Clear(&(string->data));
}
void StrTrim(String* string)
{
	Array_a8Trim(&(string->data));
}
u32 StrFindCString(const String* string, const a8* substring)
{
	String substringReal = { 0 };
	StrAppendCStr(&substringReal, substring);
	return StrFind(string, &substringReal);
}
u32 StrFind(const String* string, const String* substring)
{
	u32 subLength = StrLength(substring);
	for (u32 i = 0; i < StrLength(substring); i++)
	{
		String portion = StrSubstring(string, i, i + StrLength(substring));
		if (StrEqualsStr(&portion, substring))
			return i;
	}
	return (u32)(-1);
}
void StrResize(String* string, u32 length)
{
	Array_a8Resize(&(string->data), length);
}
void StrReserve(String* string, u32 capacity)
{
	Array_a8Reserve(&(string->data), capacity);
}

String StrSubstring(const String* string, u32 begin, u32 end)
{
	if (end >= StrLength(string))
		end = StrLength(string);

	String output = { 0 };
	u32 length = end - begin;

	StrReserve(&output, length);

	for (usize i = begin; i < end; i++)
		StrAppendChar(&output, string->data.data[i]);

	return output;
}
b8 StrEqualsStr(const String* string, const String* otherString)
{
	return StrCmp(string, otherString) == 0;
}
b8 StrEqualsCStr(const String* string, const a8* otherString)
{
	String otherStringReal = { 0 };
	StrAppendCStr(&otherStringReal, otherString);
	b8 result = StrCmp(string, &otherStringReal) == 0;
	murder(otherStringReal.data.data);
	return result;
}

#endif