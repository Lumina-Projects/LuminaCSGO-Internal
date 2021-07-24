#include "includes.h"

VOID WINAPI HookThread(void* instance) {
	while (!GetModuleHandleA("serverbrowser.dll")) Sleep(200);
	if (!(SteamOverlay::GetModule())) {
		MessageBoxA(NULL, "\"GameOverlayRenderer.dll\" is not loaded!\nPlease load with Steam!", "Error", MB_OK | MB_ICONERROR);
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
	}

	try {
		Hooks::Initialize();
	}
	catch (std::exception e) {
		MessageBoxA(NULL, e.what(), "Lumina Error | 0x001", MB_OK | MB_ICONERROR);
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
	}
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HookThread, hModule, 0, 0);
		break;
	default:
		break;
	}
}