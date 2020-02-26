#include "pch.h"
#include "CallResult.h"

extern "C"
Steamworks::NETCore::Detail::NCallResult* __cdecl Steamworks::NETCore::Detail::MakeCallResult(int idx, uint8 flags, SteamAPICall_t handle, int size, void (*handler) (void*, bool))
{
	return new NCallResult(idx, flags, handle, size, handler);
}

void __cdecl Steamworks::NETCore::Detail::FreeCallResult(NCallResult* ptr)
{
	delete ptr;
}
