#pragma once
/*Windows Headers*/
#include <limits>
#define NOMINMAX
#include <Windows.h>
#include <exception>
#include <Psapi.h>
#include <array>
#include <vector>
#include <string>
/*D3D9*/
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")
/*ImGui*/
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
/*MinHook*/
#include "MinHook/include/MinHook.h"
/*Valve SDK*/
#include "Vector.h"
#include "Matrix.h"
#include "VirtualMethod.h"
#include "ValveDefines.h"
#include "ClientClass.h"
#include "CBaseEntity.h"
#include "CBaseEntityList.h"
#include "IEngineClient.h"
#include "CInterface.h"
/*Headers*/
#include "SteamOverlay.h"
#include "globals.h"
#include "imgui_custom.h"
#include "settings.h"
#include "menu.h"
#include "Background.hpp"
#include "MuseoSans.h"
#include "IconFont.h"
#include "features.h"
#include "hook.h"