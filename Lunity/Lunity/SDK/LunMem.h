
#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <MinHook.h>
#include "../Client/Cheats/Speed.cpp"

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define ulong UINT64
class LunMem
{
public:
	static ulong getBaseModule();
	static ClientInstance* getClientInstance();
	static ulong getThisModule();

	static void Patch(BYTE* dst, BYTE* src, unsigned int size);
	static void Nop(BYTE* dst, unsigned int size);
	static uintptr_t FindSignature(const char* szSignature);
	static HMODULE hModule;
};



