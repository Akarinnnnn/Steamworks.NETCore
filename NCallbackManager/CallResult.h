#pragma once
#include <steam_api.h>

#ifdef NCALLBACKMANAGER_EXPORTS
#define __EXPORT__ __declspec(dllexport)
#else
#define __EXPORT__ __declspec(dllimport)
#endif // NCALLBACKMANAGER_EXPORTS


namespace Steamworks::NETCore::Detail
{
	class NCallResult;
	extern "C" __EXPORT__ NCallResult * __cdecl MakeCallResult(int idx, uint8 flags, SteamAPICall_t handle, int size, void (*handler) (void*,bool));


	class NCallResult : public CCallbackBase
	{
	public:
		typedef void (*Handler)(void*, bool);
		SteamAPICall_t handle;
		Handler h = nullptr;
		friend NCallResult* __cdecl MakeCallResult(int idx, uint8 flags, SteamAPICall_t handle, int size, void (*handler) (void*, bool));

	private:
		NCallResult(int indexOfCallback, uint8 callbackFlags, SteamAPICall_t handle, int callbackParamSize, Handler handler) :
			handle(handle),
			callback_size(callbackParamSize),
			h(handler)
		{
			this->m_iCallback = indexOfCallback;
			this->m_nCallbackFlags = callbackFlags;
		}

		int callback_size = 0;
		virtual int GetCallbackSizeBytes() override
		{
			return callback_size;
		}
		virtual void Run(void* param) override
		{
			if (h)
				h(param, true);
			handle = k_uAPICallInvalid;
		}
		virtual void Run(void* param, bool iofail, SteamAPICall_t handle) override
		{
			if (this->handle == handle && h)
				h(param, iofail);
			handle = k_uAPICallInvalid;
		}
	};
}