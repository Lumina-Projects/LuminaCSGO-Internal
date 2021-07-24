#pragma once
#include "includes.h"

class CCSClientClass {
public:
	PVOID CreateClassFn;
	PVOID CreateEventFn;
	char* m_szNetworkedName;
	PVOID m_pRecvTable;
	CCSClientClass* m_pNextClass;
	INT m_nClassID;
};