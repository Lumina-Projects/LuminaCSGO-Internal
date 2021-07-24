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
        if (!Settings::BoxESP) return;

        const auto collideable = player->GetCollideable();
        const BoundingBox bbox{ collideable->obbMins(), collideable->obbMaxs(), player->ToWorldTransform() };
        if (!bbox) return;
        draw->AddRect(bbox.min, bbox.max, ImColor(255, 255, 255), 0, 0);
        draw->AddRect(ImVec2(bbox.min.x + 1, bbox.min.y + 1), ImVec2(bbox.max.x - 2, bbox.max.y - 2), ImColor(0, 0, 0), 0, 0);
        draw->AddRect(ImVec2(bbox.min.x - 1, bbox.min.y - 1), ImVec2(bbox.max.x + 2, bbox.max.y + 2), ImColor(0, 0, 0), 0, 0);
	}

    void RenderName(CBaseEntity* player, ImDrawList* draw, int index) {
        if (!Settings::NameESP) return;

        const auto collideable = player->GetCollideable();
        const BoundingBox bbox{ collideable->obbMins(), collideable->obbMaxs(), player->ToWorldTransform() };
        if (!bbox) return;
        SPlayerInfo pEntityInfo;
        Interface.Engine->GetPlayerInfo(index, &pEntityInfo);
        const auto TextSize = ImGui::CalcTextSize(pEntityInfo.m_szName);
        const auto HorizontalOffset = TextSize.x / 2.f;
        const auto VerticalOffset = 0.f;
        draw->AddText(ImGui::GetDefaultFont(), ImGui::GetDefaultFont()->FontSize, ImVec2((bbox.min.x + bbox.max.x) / 2 - HorizontalOffset, bbox.min.y - 7 - VerticalOffset), ImColor(255, 255, 255), pEntityInfo.m_szName);
        draw->AddText(ImGui::GetDefaultFont(), ImGui::GetDefaultFont()->FontSize, ImVec2((bbox.min.x + bbox.max.x) / 2 - HorizontalOffset + 1.f, bbox.min.y - 7 - VerticalOffset + 1.f), ImColor(0, 0, 0), pEntityInfo.m_szName);
    }

	void Render(ImDrawList* drawList) {
		if (!(Settings::EnableESP)) return;

		if (!Interface.Engine->IsInGame()) return;
		CBaseEntity* pLocal = Interface.EntityList->GetEntity(Interface.Engine->GetLocalPlayer());
		if (!pLocal || pLocal->GetHealth() < 0) return;

		for (int i = 1; i < Interface.EntityList->GetHighestEntityIndex(); i++) {
			CBaseEntity* pEntity = Interface.EntityList->GetEntity(i);
			if (!pEntity || pEntity->GetHealth() == 0 || pEntity == pLocal || pEntity->GetClientClass()->m_nClassID != 0x28) continue;
			RenderPlayerBox(pEntity, drawList);
            RenderName(pEntity, drawList, i);
		}
	}
}