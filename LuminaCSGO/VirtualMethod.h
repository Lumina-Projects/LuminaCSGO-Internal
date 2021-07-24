#pragma once
#include <cstddef>
#include <Windows.h>

template <typename I, std::size_t Idx, typename ...Args>
__forceinline I v(PVOID iface, Args... args) { return (*reinterpret_cast<I(__thiscall***)(void*, Args...)>(iface))[Idx](iface, args...); }
#define VIRTUAL_METHOD(returnType, name, idx, args, argsRaw) __forceinline returnType name args { return v<returnType, idx>argsRaw; }
