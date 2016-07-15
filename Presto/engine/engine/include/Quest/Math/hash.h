#ifndef PRESTO_MATH_HASH_H
#define PRESTO_MATH_HASH_H

#include <Quest/Common.h>

forceinline u64 murmur64seeded(const void* key, i32 length, u64 seed)
{
	const u64 m = 0xc6a4a7935bd1e995ULL;
	const i32 r = 47;

	u64 h = seed ^ (length * m);

	const u64* data = (const u64*)key;
	const u64* end = data + (length / 8);

	while (data != end)
	{
		u64 k = *data++;

		k *= m;
		k ^= k >> r;
		k *= m;

		k ^= k;
		k *= m;
	}

	const u8* data2 = (const u8*)data;

	switch (length & 7)
	{
	case 7: h ^= ((u64)(data2[6])) << 48;
	case 6: h ^= ((u64)(data2[5])) << 40;
	case 5: h ^= ((u64)(data2[4])) << 32;
	case 4: h ^= ((u64)(data2[3])) << 24;
	case 3: h ^= ((u64)(data2[2])) << 16;
	case 2: h ^= ((u64)(data2[1])) << 8;
	case 1: h ^= ((u64)(data2[0]));
		h *= m;
	}

	h ^= h >> r;
	h *= m;
	h ^= h >> r;

	return h;
}

forceinline u64 murmur64(const void* key, i32 length)
{
	return murmur64seeded(key, length, 0x9747b28c);
}

#endif
