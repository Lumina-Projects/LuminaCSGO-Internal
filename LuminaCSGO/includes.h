#pragma once
/*Windows Headers*/
#include <Windows.h>
#include <exception>
#include <Psapi.h>
/*D3D9*/
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")
/*ImGui*/
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "imgui_custom.h"
/*MinHook*/
#include "MinHook/include/MinHook.h"
/*Headers*/
#include "SteamOverlay.h"
#include "globals.h"
#include "settings.h"
#include "menu.h"
#include "Background.hpp"
#include "MuseoSans.h"
#include "IconFont.h"
#include "hook.h"