#pragma once
#include "includes.h"

class CUserCmd {
private:
	unsigned char     pad_0x0[0x4];
public:
	int			      m_nCommandNumber;
	int			      m_nTickCount;
	Vector			  m_vecAngles;
	Vector	          m_vecDirection;
	FLOAT		      m_flForwardMove;
	FLOAT		      m_flSideMove;
	FLOAT		      m_flUpMove;
	int			      m_nButtons;
	char			  m_chImpulse;
	int			      m_nWeaponSelect;
	int			      m_nWeaponType;
	short             m_shSeed;
	short		      m_shMouseDX;
	short		      m_shMouseDY;
	BOOLEAN		      m_bHasBeenPredicted;
private:
	unsigned char     pad_0x1[0x18];
};