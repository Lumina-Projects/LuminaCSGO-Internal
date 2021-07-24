#pragma once
#include "includes.h"

struct SPlayerInfo {
	ULONG64 m_ullVersion;
	union {
		ULONG64 m_ullXUID;
		struct {
			DWORD m_nXUIDLow;
			DWORD m_nXUIDHigh;
		};
	};
	CHAR m_szName[128];
	INT m_nUserID;
	CHAR m_szGUID[33];
	DWORD m_nFriendsID;
	CHAR m_szFriendsName[128];
	BOOLEAN m_bIsBot;
	BOOLEAN m_bIsHLTV;
	INT m_nCustomFiles[4];
	BYTE m_ucFilesDownloaded;
};

class IEngineClient {
public:
	VIRTUAL_METHOD(BOOLEAN, IsInGame, 26, (), (this))
	VIRTUAL_METHOD(DWORD, GetLocalPlayer, 12, (), (this))
    VIRTUAL_METHOD(const Matrix4x4&, WorldToScreenMatrix, 37, (), (this))
	VIRTUAL_METHOD(BOOLEAN, GetPlayerInfo, 8, (INT idx, SPlayerInfo* info), (this, idx, info))
};
