#include "pch.h"
#include <steam_api.h>
#include <string>
#include <vcclr.h>
#include <stringapiset.h>

#include "..\NCallbackManager\CallResult.h"

using mstring = System::String;
using mbuff = cli::array<unsigned char>;
namespace Steamworks::NETCore
{
	extern std::string mstr2u8(mstring^ str)
	{
		//std::string ret(str->Length, '\0');
		pin_ptr<const wchar_t> begin = PtrToStringChars(str);
		std::string ret;
		auto size = WideCharToMultiByte(
			CP_UTF8, WC_NO_BEST_FIT_CHARS, begin, str->Length,
			nullptr, 0, nullptr, nullptr);
		ret.resize(size);
		WideCharToMultiByte(
			CP_UTF8, WC_NO_BEST_FIT_CHARS, begin, str->Length,
			ret.data(), size, nullptr, nullptr);
		return ret;
	}
	
	delegate void nhandler(void*, bool);

	[System::Runtime::InteropServices::DllImportAttribute("NCallbackManager",EntryPoint = "MakeCallResult")]
	extern "C" Detail::NCallResult * MakeCallResult(int idx, uint8 flags, SteamAPICall_t handle, int size, nhandler ^ handler);


	generic<typename T>
	public ref class CallResult
	{
	public:
		delegate void CallResultHandler(T% result, bool ioFail);
		

		/// <summary>this will be invoked when the background work finished</summary>
		event CallResultHandler^ OnReceived;

		/// <summary>
		/// Internal use.
		/// </summary>
		CallResult(int k_iCallback, uint8 flags) :k_iCallback(k_iCallback), flags(flags) {}

		/// <summary>
		/// register this call result.
		/// </summary>
		/// <param name="handler"></param>
		/// <created>Fa¸ë,2020/2/25</created>
		/// <changed>Fa¸ë,2020/2/25</changed>
		void Set(SteamAPICall_t handle)
		{
			
			callback_base = MakeCallResult(k_iCallback, flags, handle, sizeof(T), gcnew nhandler(this, real_handler));
			SteamAPI_RegisterCallResult(callback_base, callback_base->handle);
		}

		/// <summary>
		/// cancel and unregister this call result.
		/// </summary>
		/// <created>Fa¸ë,2020/2/25</created>
		/// <changed>Fa¸ë,2020/2/25</changed>
		void Cancel()
		{
			SteamAPI_UnregisterCallResult(callback_base, callback_base->handle);
		}

		property bool IsActive { bool get() { return callback_base->handle != k_uAPICallInvalid; } }

	private:
		void real_handler(void* param, bool iofail)
		{
			T realparam;
			memcpy_s(pin_ptr<T>(&realparam), sizeof(T), param, sizeof(T));
			OnReceived(realparam, iofail);
		}

		int k_iCallback;
		uint8 flags;
		Detail::NCallResult* callback_base;
	};

	public value class SteamID
	{
	public:
		static bool operator==(SteamID l, SteamID r)
		{
			return l.SteamID64 == r.SteamID64;
		}

		mstring^ ToString() override
		{
			return SteamID64.ToString();
		}
		uint64 SteamID64;
	};

	public ref class SteamAPI
	{
	public:
		#pragma region Properties
		/// <summary>
		/// returns the pipe we are communicating to Steam with
		/// </summary>
		property int32 HSteamPipe { int32 get() { return SteamAPI_GetHSteamPipe(); } }
		/// <summary>
		/// returns true if Steam is currently running
		/// </summary>
		/// <created>Fa¸ë,2020/2/25</created>
		/// <changed>Fa¸ë,2020/2/25</changed>
		property bool IsSteamRunning { bool get() { return SteamAPI_IsSteamRunning(); } }
		#pragma endregion

		/// <summary>
		/// SteamAPI_Init must be called before using any other API functions. If it fails, an
		/// error message will be output to the debugger (or stderr) with further information.
		/// </summary>
		static bool Init() { return SteamAPI_Init(); }

		/// <summary>
		/// SteamAPI_Shutdown should be called during process shutdown if possible.
		/// </summary>
		static void Shutdown() { SteamAPI_Shutdown(); }

		/// <summary>
		/// SteamAPI_RunCallbacks is safe to call from multiple threads simultaneously,
		/// but if you choose to do this, callback code could be executed on any thread.
		/// One alternative is to call SteamAPI_RunCallbacks from the main thread only,
		/// and call SteamAPI_ReleaseCurrentThreadMemory regularly on other threads.
		/// </summary>
		static void RunCallbacks() { SteamAPI_RunCallbacks(); }
	};
}