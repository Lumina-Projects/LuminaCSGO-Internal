#pragma once
#include "includes.h"

namespace fnv {
	DWORD hash(LPCSTR szString, DWORD nOffset = 0x811C9DC5) {
		return (*szString == '\0') ? nOffset : hash(&szString[1], (nOffset ^ DWORD(*szString)) * 0x01000193);
	}
}