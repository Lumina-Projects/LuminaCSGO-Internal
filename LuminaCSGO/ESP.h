#pragma once
#include "features.h"

static bool WorldToScreen(const Vector& in, ImVec2& out, bool floor = true) noexcept {
    const auto& matrix = Interface.Engine->WorldToScreenMatrix();
    const auto w = matrix._41 * in.x + matrix._42 * in.y + matrix._43 * in.z + matrix._44;
    if (w < 0.001f) return false;
    out = ImGui::GetIO().DisplaySize / 2.0f;
    out.x *= 1.0f + (matrix._11 * in.x + matrix._12 * in.y + matrix._13 * in.z + matrix._14) / w;
    out.y *= 1.0f - (matrix._21 * in.x + matrix._22 * in.y + matrix._23 * in.z + matrix._24) / w;
    if (floor) out = ImFloor(out);
    return true;
}

static constexpr auto operator-(float sub, const std::array<float, 3>& a) noexcept { return Vector{ sub - a[0], sub - a[1], sub - a[2] }; }

struct BoundingBox {
private:
    bool valid;
public:
    ImVec2 min, max;
    std::array<ImVec2, 8> vertices;

    BoundingBox(const Vector& mins, const Vector& maxs, const std::array<float, 3>& scale, const Matrix3x4* matrix = nullptr) noexcept {
        min.y = min.x = std::numeric_limits<float>::max();
        max.y = max.x = -std::numeric_limits<float>::max();
        const auto scaledMins = mins + (maxs - mins) * 2 * (0.25f - scale);
        const auto scaledMaxs = maxs - (maxs - mins) * 2 * (0.25f - scale);

        for (int i = 0; i < 8; ++i) {
            const Vector point{
                i & 1 ? scaledMaxs.x : scaledMins.x,
                i & 2 ? scaledMaxs.y : scaledMins.y,
                i & 4 ? scaledMaxs.z : scaledMins.z 
            };

            if (!WorldToScreen(matrix ? point.Transform(*matrix) : point, vertices[i])) {
                valid = false;
                return;
            }

            min.x = std::min(min.x, vertices[i].x);
            min.y = std::min(min.y, vertices[i].y);
            max.x = std::max(max.x, vertices[i].x);
            max.y = std::max(max.y, vertices[i].y);
        }
        valid = true;
    }

    BoundingBox(const Vector& obbMins, const Vector& obbMaxs, const Matrix3x4 vMatrix) noexcept : BoundingBox{ obbMins, obbMaxs, { 0.25f, 0.25f, 0.25f }, &vMatrix } {}
    BoundingBox(const Vector& center) noexcept : BoundingBox{ center - 2.0f, center + 2.0f, { 0.25f, 0.25f, 0.25f } } {}

    explicit operator bool() const noexcept
    {
        return valid;
    }
};

namespace ESP {
	void RenderPlayerBox(CBaseEntity* player, ImDrawList* draw) {
        if (!Settings::Visuals.bEnableBox) return;

        const auto collideable = player->GetCollideable();
        const BoundingBox bbox{ collideable->obbMins(), collideable->obbMaxs(), player->ToWorldTransform() };
        if (!bbox) return;

        switch (Settings::Visuals.Box.iBoxType) {
        case 0:
            CDraw::DrawRect(bbox.min.x, bbox.min.y, bbox.max.x, bbox.max.y, ImColor(255, 255, 255), 2, true);
            break;
        case 1:
            //draw->AddRectFilled(ImVec2(bbox.min.x, bbox.max.y), ImVec2(bbox.min.x + 1.0f, bbox.max.y - flQuarterHeight), ImColor(255, 255, 255));
            //draw->AddRectFilled(ImVec2(bbox.min.x, bbox.max.y - 1.0f), ImVec2(bbox.min.x + flQuarterWidth, bbox.max.y), ImColor(255, 255, 255));
            //draw->AddRectFilled(bbox.max, ImVec2(bbox.max.x - flQuarterWidth, bbox.max.y - 1.0f), ImColor(255, 255, 255));
            //draw->AddRectFilled(bbox.max, ImVec2(bbox.max.x - 1.0f, bbox.max.y - flQuarterHeight), ImColor(255, 255, 255));
            CDraw::DrawRect(bbox.min.x, bbox.min.y, bbox.min.x + 1.f, bbox.min.y + IM_FLOOR((bbox.max.y - bbox.min.y) * 0.25f), ImColor(255, 255, 255), 2, true);
            CDraw::DrawRect(bbox.min.x, bbox.min.y, bbox.min.x + IM_FLOOR((bbox.max.x - bbox.min.x) * 0.25f), bbox.min.y + 1.f, ImColor(255, 255, 255), 2, true);
            CDraw::DrawRect(bbox.max.x, bbox.min.y, bbox.max.x - IM_FLOOR((bbox.max.x - bbox.min.x) * 0.25f), bbox.min.y + 1.f, ImColor(255, 255, 255), 2, true);
            CDraw::DrawRect(bbox.max.x - 1.0f, bbox.min.y, bbox.max.x, bbox.min.y + IM_FLOOR((bbox.max.y - bbox.min.y) * 0.25f), ImColor(255, 255, 255), 2, true);
            CDraw::DrawRect(bbox.min.x, bbox.max.y, bbox.min.x + 1.0f, bbox.max.y - IM_FLOOR((bbox.max.y - bbox.min.y) * 0.25f), ImColor(255, 255, 255), 2, true);
            CDraw::DrawRect(bbox.min.x, bbox.max.y - 1.0f, bbox.min.x + IM_FLOOR((bbox.max.x - bbox.min.x) * 0.25f), bbox.max.y, ImColor(255, 255, 255), 2, true);
            CDraw::DrawRect(bbox.max.x, bbox.max.x - IM_FLOOR((bbox.max.x - bbox.min.x) * 0.25f), bbox.max.y - 1.0f, ImColor(255, 255, 255), 2, true);
            CDraw::DrawRect(bbox.max.x, bbox.max.y, bbox.max.x - 1.0f, bbox.max.y - IM_FLOOR((bbox.max.y - bbox.min.y) * 0.25f), ImColor(255, 255, 255), 2, true);
            break;
        }
	}

    void RenderName(CBaseEntity* player, ImDrawList* draw, int index) {
        if (!Settings::Visuals.bName) return;

        const auto collideable = player->GetCollideable();
        const BoundingBox bbox{ collideable->obbMins(), collideable->obbMaxs(), player->ToWorldTransform() };
        if (!bbox) return;
        SPlayerInfo pEntityInfo;
        Interface.Engine->GetPlayerInfo(index, &pEntityInfo);
        CDraw::DrawTextA((bbox.min.x + bbox.max.x) / 2 - ImGui::CalcTextSize(pEntityInfo.m_szName).x / 2, bbox.min.y - 15 - 0, ImColor(255, 255, 255), pEntityInfo.m_szName, true);
    }

    void RenderSnapline(CBaseEntity* player) {
        if (!Settings::Visuals.bSnapline) return;

        const auto collideable = player->GetCollideable();
        const BoundingBox bbox{ collideable->obbMins(), collideable->obbMaxs(), player->ToWorldTransform() };
        if (!bbox) return;
        ImVec2& WindowScreenSize = ImGui::GetIO().DisplaySize;
        ImVec2 p1, p2;
        p1.x = WindowScreenSize.x / 2;
        p2.x = (bbox.min.x + bbox.max.x) / 2;
        p1.y = WindowScreenSize.y;
        p2.y = bbox.max.y;
        CDraw::DrawLine(p1.x, p1.y, p2.x, p2.y, ImColor(255, 255, 255), 2, true);
    }

    void RenderHealthbar(CBaseEntity* player, ImDrawList* draw) {
        if (!Settings::Visuals.bHealthbar) return;

        const auto collideable = player->GetCollideable();
        const BoundingBox bbox{ collideable->obbMins(), collideable->obbMaxs(), player->ToWorldTransform() };
        if (!bbox) return;

        /*Uncomment this when we do a bit better*/
       /* draw->PushClipRect(bbox.min - ImVec2(5.f, 0.f) + ImVec2(0.0f, (100 - player->GetHealth()) / 100.0f * (bbox.max.y - bbox.min.y)), bbox.min - ImVec2(5.f, 0.f) + ImVec2(3.f + 1.0f, (bbox.max.y - bbox.min.y) + 1.0f));
        ImColor green = ImColor(0, 255, 0, 255);
        ImColor yellow = ImColor(255, 255, 0, 255);
        ImColor red = ImColor(255, 0, 0, 255);
        ImVec2 min = bbox.min - ImVec2(5.f, 0.f);
        ImVec2 max = min + ImVec2(3.f, (bbox.max.y - bbox.min.y) / 2.f);
        draw->AddRectFilled(min + ImVec2(1.f, 1.f), bbox.min - ImVec2(5.f, 0.f) + ImVec2(3.f + 1.f, (bbox.max.y + bbox.min.y) + 1.f), ImColor(0, 0, 0), 0, 0);
        draw->AddRectFilledMultiColor(ImFloor(min), ImFloor(max), green, green, yellow, yellow);
        min.y += (bbox.max.y - bbox.min.y) / 2.f;
        max.y += (bbox.max.y - bbox.min.y) / 2.f;
        draw->AddRectFilledMultiColor(ImFloor(min), ImFloor(max), yellow, yellow, red, red);
        draw->PopClipRect();*/
        draw->PushClipRect(bbox.min - ImVec2(5.f, 0.f) + ImVec2(0.0f, (100 - player->GetHealth()) / 100.0f * (bbox.max.y - bbox.min.y)), bbox.min - ImVec2(5.f, 0.f) + ImVec2(3.f + 1.0f, (bbox.max.y - bbox.min.y) + 1.0f));
        ImVec2 min = bbox.min - ImVec2(5.f, 0.f);
        ImVec2 max = min + ImVec2(3.f, (bbox.max.y - bbox.min.y) / 2.f);
        draw->AddRectFilled(min + ImVec2(1.f, 1.f), bbox.min - ImVec2(5.f, 0.f) + ImVec2(3.f + 1.f, (bbox.max.y + bbox.min.y) + 1.f), ImColor(0, 0, 0));
        draw->AddRectFilled(ImFloor(min), ImFloor(max), ImColor(0, 255, 0));
        min.y += (bbox.max.y - bbox.min.y) / 2.f;
        max.y += (bbox.max.y - bbox.min.y) / 2.f;
        draw->AddRectFilled(ImFloor(min), ImFloor(max), ImColor(0, 255, 0));
        draw->PopClipRect();

    }

	void Render(ImDrawList* drawList) {
		if (!(Settings::Visuals.bEnable)) return;
        
		if (!Interface.Engine->IsInGame()) return;
		CBaseEntity* pLocal = Interface.EntityList->GetEntity(Interface.Engine->GetLocalPlayer());
		if (!pLocal || pLocal->GetHealth() < 0) return;

		for (int i = 1; i < Interface.EntityList->GetHighestEntityIndex(); i++) {
			CBaseEntity* pEntity = Interface.EntityList->GetEntity(i);
			if (!pEntity || pEntity->GetHealth() == 0 || pEntity == pLocal || pEntity->GetClientClass()->m_nClassID != 0x28) continue;
			RenderPlayerBox(pEntity, drawList);
            RenderName(pEntity, drawList, i);
            RenderSnapline(pEntity);
            RenderHealthbar(pEntity, drawList);
		}
	}
}