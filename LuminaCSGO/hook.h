#pragma once
#include "includes.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hooks {
	/*Present Hook*/
	namespace Present {
		typedef HRESULT(STDMETHODCALLTYPE* Present) (IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
		Present oPresent = NULL;

		HRESULT STDMETHODCALLTYPE hkPresent(IDirect3DDevice9* pDevice, const RECT* src, const RECT* dest, HWND hWnd, const RGNDATA* dirtyRegion) {
			if (!Globals::InitD3D9) {
				hWnd = FindWindowA("Valve001", NULL);
				if (hWnd) {
					ImGui::CreateContext();
					ImGuiIO& io = ImGui::GetIO();
					io.Fonts->AddFontFromMemoryCompressedTTF(MuseoSansCompressedData, MuseoSansCompressedSize, 20.0f);
					io.Fonts->AddFontDefault();
					Globals::TitleFont = io.Fonts->AddFontFromMemoryCompressedTTF(MuseoSansCompressedData, MuseoSansCompressedSize, 25.f);
					Globals::SmallFont = io.Fonts->AddFontFromMemoryCompressedTTF(MuseoSansCompressedData, MuseoSansCompressedSize, 17.0f);
					Globals::IconFont = io.Fonts->AddFontFromMemoryCompressedTTF(IconCompressedData, IconCompressedSize, 20.0f);
					ImGui_ImplWin32_Init(hWnd);
					ImGui_ImplDX9_Init(pDevice);
					if (Globals::WindowPosition.x == 0 && Globals::WindowPosition.y == 0) {
						RECT ScreenRect{};
						GetWindowRect(hWnd, &ScreenRect);
						ImVec2 ScreenReselution = ImVec2((float)ScreenRect.right, (float)ScreenRect.bottom);
						Globals::WindowPosition = (ImVec2(ScreenReselution.x - 700, ScreenReselution.y - 650));
					}
					D3DXCreateTextureFromFileInMemoryEx(pDevice, &Background, sizeof(Background), 2000, 2000, D3DUSAGE_DYNAMIC, 0, D3DFMT_X8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &Globals::MenuBackground);
					Globals::InitD3D9 = true;
				}
			}
			else {
				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();

				if (Menu::IsUIOpen()) Menu::RenderUI();

				ESP::Render(ImGui::GetBackgroundDrawList());

				ImGui::EndFrame();
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			}
			return oPresent(pDevice, src, dest, hWnd, dirtyRegion);
		}
	}

	namespace PaintTraverse {
		typedef VOID(__thiscall* PaintTraverse)(IPanel*, DWORD, BOOLEAN, BOOLEAN);
		PaintTraverse oPaintTraverse;

		VOID WINAPI hkPaintTraverse(DWORD dwPanel, BOOLEAN bForceRepaint, BOOLEAN bAllowRepaint) {
			if (fnv::hash(Interface.Panel->GetPanelName(dwPanel)) == 0x8BE56F81 /* fnv::hash("FocusOverlayPanelj") = 0x8BE56F81 */) {
				Interface.Panel->SetInputMouseState(dwPanel, Settings::ToggleMenu);
				Interface.Panel->SetInputKeyboardState(dwPanel, Settings::ToggleMenu);
			}
			return oPaintTraverse(Interface.Panel, dwPanel, bForceRepaint, bAllowRepaint);
		}
	}

	namespace CreateMove {
		typedef BOOLEAN(WINAPI* CreateMove)(FLOAT, CUserCmd*);
		CreateMove oCreateMove;

		BOOLEAN WINAPI hkCreateMove(FLOAT flInputSampleTime, CUserCmd* cmd) {
			BOOLEAN bCreateMove = oCreateMove(flInputSampleTime, cmd);
			if (cmd->m_nCommandNumber % 4 == 1) {
				Misc::RenderCreateMoveCVar(); /*We have to put this heres because CVars need to be on 1 tick*/
			}
			return bCreateMove;
		}
	}

	WNDPROC oWndProc;

	/*Window Process*/
	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (uMsg == WM_KEYUP && (wParam == VK_INSERT)) Settings::ToggleMenu = !Settings::ToggleMenu;
		if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return TRUE;
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}
	/*Initialize Hook*/
	bool Initialize() {
		/*Initialize MinHook*/
		if (MH_Initialize() != MH_OK) {
			MessageBoxA(NULL, "Failed to initialize MinHook!", "Lumina Error | 0x002", MB_OK | MB_ICONERROR);
			return false;
		}
		/*SteamOverlay Hook*/
		uintptr_t pSteamPresentAddr = SteamOverlay::FindSig("GameOverlayRenderer.dll", "FF 15 ? ? ? ? 8B F0 85 FF") + 2;
		Present::oPresent = **reinterpret_cast<decltype(&Present::oPresent)*>(pSteamPresentAddr);
		**reinterpret_cast<void***>(pSteamPresentAddr) = reinterpret_cast<void*>(&Present::hkPresent);
		oWndProc = (WNDPROC)SetWindowLongA(FindWindowA("Valve001", NULL), GWLP_WNDPROC, (LONG)WndProc);
		/*Interfaces*/
		Interface.Initialize();
		/*Interfaces Hook*/
		if (MH_CreateHook((*reinterpret_cast<PVOID**>(Interface.Panel))[41], &PaintTraverse::hkPaintTraverse, (PVOID*)&PaintTraverse::oPaintTraverse) != MH_OK) {
			MessageBoxA(NULL, "Failed to initialize hkPaintTraverse!", "Lumina Error | 0x003", MB_OK | MB_ICONERROR);
			return false;
		}
		if (MH_CreateHook((*reinterpret_cast<PVOID**>(Interface.ClientMode))[24], &CreateMove::hkCreateMove, (PVOID*)&CreateMove::oCreateMove) != MH_OK) {
			MessageBoxA(NULL, "Failed to initialize hkCreateMove!", "Lumina Error | 0x004", MB_OK | MB_ICONERROR);
			return false;
		}
		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
			MessageBoxA(NULL, "Failed to enable hooks!", "Lumina Error | 0x005", MB_OK | MB_ICONERROR);
			return false;
		}
		return true;
	}
}