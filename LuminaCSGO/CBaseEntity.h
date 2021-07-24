#pragma once
#include "includes.h"

class Collideable {
public:
	VIRTUAL_METHOD(const Vector&, obbMins, 1, (), (this))
	VIRTUAL_METHOD(const Vector&, obbMaxs, 2, (), (this))
};

class CBaseEntity {
public:
	__forceinline INT GetHealth() { return *(int*)(this + 0x100); } /* CBaseEntity::m_iHealth */
    __forceinline PVOID GetNetworkable() { return (PVOID)(this + 0x8); }
	VIRTUAL_METHOD(CCSClientClass*, GetClientClass, 2, (), (this->GetNetworkable()))
	VIRTUAL_METHOD(Collideable*, GetCollideable, 3, (), (this))
	VIRTUAL_METHOD(const Matrix3x4&, ToWorldTransform, 32, (), (this + sizeof(uintptr_t)))
};