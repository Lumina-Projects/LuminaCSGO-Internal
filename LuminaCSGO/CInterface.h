#pragma once
#include "includes.h"

struct CInterface {
	IEngineClient* Engine;
	CBaseEntityList* EntityList;

	template <class T>
	T CreateInterface(PVOID m_pModule, LPCSTR m_szInterface) {
		return ((T(*)(LPCSTR, DWORD))GetProcAddress((HMODULE)m_pModule, "CreateInterface"))(m_szInterface, 0x0);
	}
} Interface;