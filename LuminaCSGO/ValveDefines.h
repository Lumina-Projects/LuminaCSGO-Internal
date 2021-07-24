#pragma once

#ifdef _WIN32

#define __THISCALL __thiscall
#define __FASTCALL __fastcall
#define __CDECL __cdecl
#define __STDCALL __stdcall
#define LINUX_ARGS(...)
#define RETURN_ADDRESS() std::uintptr_t(_ReturnAddress())
#define FRAME_ADDRESS() (std::uintptr_t(_AddressOfReturnAddress()) - sizeof(std::uintptr_t))
#define IS_WIN32() true
#define WIN32_LINUX(win32, linux) win32

#endif // _WIN32