#pragma once
#include <stdint.h>

class EntityPool
{
public:
	char pad0[0x10];
	uint32_t num1;		// off=0x10
	char pad1[0xC];
	uint32_t num2;		// off=0x20

	inline bool Full()
	{
		return num1 - (num2 & 0x3FFFFFFF) <= 256;
	}
};

class VehiclePool
{
public:
	uint32_t *poolAddress;		// off=0x00
	uint32_t size;				// off=0x08
	char pad0[0x1E];
	uint32_t* bitArray;			// off=0x30
	char pad1[0x28];
	uint32_t itemCount;			// off=0x60

	inline bool isValid(uint32_t i)
	{
		return (bitArray[i >> 5] >> (i & 0x1F)) & 1;
	}

	inline uint64_t getAddress(uint32_t i)
	{
		return poolAddress[i];
	}
};

class GenericPool {
public:
	uint64_t poolStartAddress;		// off=0x00
	uint8_t* byteArray;				// off=0x08
	uint32_t size;					// off=0x10
	uint32_t itemSize;				// off=0x14


	inline bool isValid(uint32_t i)
	{
		return mask(i) != 0;
	}

	inline uint64_t getAddress(uint32_t i)
	{
		return mask(i) & (poolStartAddress + i * itemSize);
	}
private:
	inline long long mask(uint32_t i)
	{
		long long num1 = byteArray[i] & 0x80;
		return ~((num1 | -num1) >> 63);
	}
};
