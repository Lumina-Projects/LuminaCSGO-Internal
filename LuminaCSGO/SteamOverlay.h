#pragma once
#include "includes.h"

#define InRange(x, a, b) (x >= a && x <= b) 
#define GetBits(x) (InRange((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA): (InRange(x, '0', '9') ? x - '0': 0))
#define GetByte(x) (GetBits(x[0]) << 4 | GetBits(x[1]))

namespace SteamOverlay {
	uintptr_t FindSigEx(const uintptr_t& pStartAddr, const uintptr_t& pEndAddr, const char* szTSig) {
		const char* szSig = szTSig;
		uintptr_t pFirstMatch = NULL;

		for (uintptr_t pPosition = pStartAddr; pPosition < pEndAddr; pPosition++) {
			if (!*szSig) return pFirstMatch;
			const uint8_t pCurrentPattern = *reinterpret_cast<const uint8_t*>(szSig);
			const uint8_t pCurrentMemory = *reinterpret_cast<const uint8_t*>(pPosition);

			if (pCurrentPattern == '\?' || pCurrentMemory == GetByte(szSig)) {
				if (!pFirstMatch) pFirstMatch = pPosition;
				if (!szSig[2]) return pFirstMatch;
				szSig += pCurrentPattern != '\?' ? 3 : 2;
			}
			else {
				szSig = szTSig;
				pFirstMatch = NULL;
			}
		}
		return NULL;
	}
	uintptr_t FindSig(const char* szModule, const char* szSig) {
		MODULEINFO hModInfo = { NULL };
		if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &hModInfo, sizeof(hModInfo))) return NULL;
		const uintptr_t pStartAddr = (uintptr_t)hModInfo.lpBaseOfDll;
		const uintptr_t pEndAddr = pStartAddr + hModInfo.SizeOfImage;
		return FindSigEx(pStartAddr, pEndAddr, szSig);
	}
	uintptr_t GetModule() {
		return (uintptr_t)GetModuleHandle(L"GameOverlayRenderer.dll");
	}
}