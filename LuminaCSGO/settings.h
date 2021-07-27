#pragma once
#include "includes.h"

namespace Settings {
	bool ToggleMenu = true;
	int MenuTab = 1;

	struct {
		bool bEnable = true;
		bool bEnableBox = true;
		struct {
			const char* szBoxTypes[2] = { "2D Box", "2D Corner Box" };
			int iBoxType = 0;
		} Box;
		bool bCornerBox = true;
		bool bHealthbar = true;
		bool bName = false;
		bool bSnapline = true;
	} Visuals;

	struct {
		BOOLEAN bRecoilCrosshair = true;
	} Misc;
}