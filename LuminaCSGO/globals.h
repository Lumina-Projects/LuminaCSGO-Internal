#pragma once
#include "includes.h"

namespace Globals {
	bool InitD3D9 = false;
	IDirect3DTexture9* MenuBackground;
	ImVec2 WindowPosition = ImVec2(0, 0);
	ImFont* TitleFont;
	ImFont* SmallFont;
	ImFont* IconFont;
	CBaseEntity* pLocal;
}