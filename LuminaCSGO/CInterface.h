#pragma once
#include "includes.h"

class IClientModeShared;
class IClient {
public:

};

struct CInterface {
	IEngineClient* Engine;
	CBaseEntityList* EntityList;
	ICVar* CVar;
	IPanel* Panel;
	CUserCmd* UserCMD;
	IClient* Client;
	IClientModeShared* ClientMode;

	template <class T>
	T CreateInterface(PVOID m_pModule, LPCSTR m_szInterface) {
		return ((T(*)(LPCSTR, DWORD))GetProcAddress((HMODULE)m_pModule, "CreateInterface"))(m_szInterface, 0x0);
	}

	void Initialize() {
		Engine = CreateInterface<IEngineClient*>((PVOID)GetModuleHandleA("engine.dll"), "VEngineClient014");
		EntityList = CreateInterface<CBaseEntityList*>((PVOID)GetModuleHandleA("client.dll"), "VClientEntityList003");
		Panel = CreateInterface<IPanel*>((PVOID)GetModuleHandleA("vgui2.dll"), "VGUI_Panel009");
		CVar = CreateInterface<ICVar*>((PVOID)GetModuleHandleA("vstdlib.dll"), "VEngineCvar007");
		Client = CreateInterface<IClient*>((PVOID)GetModuleHandleA("client.dll"), "VClient018");
		ClientMode = **(IClientModeShared***)((*(DWORD**)(Client))[0xA] + 0x5);
	}
} Interface;