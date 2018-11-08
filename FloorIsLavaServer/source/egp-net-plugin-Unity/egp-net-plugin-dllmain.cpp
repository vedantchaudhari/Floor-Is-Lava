/*
	EGP Networking: Plugin Interface/Wrapper
	Dan Buckstein
	October 2018

	Optional entry point for DLL.
*/

#if (defined _WINDOWS || defined _WIN32)


#include <Windows.h>


int APIENTRY DllMain(
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// dispatched when another process (e.g. application) consumes this library
		break;
	case DLL_THREAD_ATTACH:
		// dispatched when another thread consumes this library
		break;
	case DLL_THREAD_DETACH:
		// dispatched when another thread releases this library
		break;
	case DLL_PROCESS_DETACH:
		// dispatched when another process releases this library
		break;
	}
	return TRUE;
}


#endif	// (defined _WINDOWS || defined _WIN32)