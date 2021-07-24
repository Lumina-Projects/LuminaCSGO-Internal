#pragma once
#include "includes.h"

class CBaseEntityList {
public:
	VIRTUAL_METHOD(CBaseEntity*, GetEntity, 3, (INT index), (this, index))
	VIRTUAL_METHOD(int, GetHighestEntityIndex, 6, (), (this))
};