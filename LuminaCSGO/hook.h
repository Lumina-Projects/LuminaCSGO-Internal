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
					Globals::TitleFont = io.Fonts->AddFontFromMemoryCompressedTTF(MuseoSansCompressedData, MuseoSansCompressedSize, 25.f);
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

				if ((GetAsyncKeyState(VK_F6) & 0x1)) Settings::ToggleMenu = !Settings::ToggleMenu;

				if (Menu::IsUIOpen()) Menu::RenderUI();

				ImGui::EndFrame();
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			}
			return oPresent(pDevice, src, dest, hWnd, dirtyRegion);
		}
	}

	WNDPROC oWndProc;

	/*Window Process*/
	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
		oWndProc = (WNDPROC)SetWindowLongPtr(FindWindowA("Valve001", NULL), GWLP_WNDPROC, (LONG_PTR)WndProc);
		return true;
	}
}