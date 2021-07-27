#pragma once
#include "includes.h"

class CConvar {
public:
	VIRTUAL_METHOD(FLOAT, GetFloat, 12, (), (this))
    VIRTUAL_METHOD(INT, GetInt, 13, (), (this))
	VIRTUAL_METHOD(VOID, SetValue, 14, (LPCSTR value), (this, value))
	VIRTUAL_METHOD(VOID, SetValue, 15, (FLOAT value), (this, value))
	VIRTUAL_METHOD(VOID, SetValue, 16, (INT value), (this, value))
};

class ICVar {
public:
	VIRTUAL_METHOD(CConvar*, FindVar, 15, (LPCSTR name), (this, name))
};