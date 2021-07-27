#pragma once
#include "includes.h"

class IPanel {
public:
	VIRTUAL_METHOD(VOID, SetInputKeyboardState, 31, (DWORD PanelID, BOOLEAN State), (this, PanelID, State))
	VIRTUAL_METHOD(VOID, SetInputMouseState, 32, (DWORD PanelID, BOOLEAN State), (this, PanelID, State))
	VIRTUAL_METHOD(LPCSTR, GetPanelName, 36, (DWORD PanelID), (this, PanelID))
};