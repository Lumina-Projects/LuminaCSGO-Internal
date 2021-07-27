#pragma once
#include "features.h"

namespace Misc {
	void Render() {
		if (!Interface.Engine->IsInGame()) return;
		CBaseEntity* pLocal = Interface.EntityList->GetEntity(Interface.Engine->GetLocalPlayer());
		if (!pLocal || pLocal->GetHealth() < 0) return;

		for (int i = 1; i < Interface.EntityList->GetHighestEntityIndex(); i++) {
			CBaseEntity* pEntity = Interface.EntityList->GetEntity(i);
			if (!pEntity || pEntity->GetHealth() == 0 || pEntity == pLocal || pEntity->GetClientClass()->m_nClassID != 0x28) continue;
		}
	}

	void RenderCreateMoveCVar() {
		Interface.CVar->FindVar("cl_crosshair_recoil")->SetValue(Settings::Misc.bRecoilCrosshair ? TRUE : FALSE); /*we have to put ? TRUE : FALSE because thats how csgo does it*/
		//Interface.CVar->FindVar("thirdperson")->SetValue(TRUE); /*we have to put ? TRUE : FALSE because thats how csgo does it*/ /* Testing */
	}
}