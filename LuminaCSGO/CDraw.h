#pragma once
#include "includes.h"

namespace CDraw {
	void DrawLine(int x, int y, int w, int h, ImColor color, int thickness, bool outline = false) {
		if (outline) {
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + 1, y + 1), ImVec2(w - 2, h - 2), ImColor(0, 0, 0), 1);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x - 1, y - 1), ImVec2(w + 2, h + 2), ImColor(0, 0, 0), 1);
		}
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(w, h), color, thickness);
	}

	void DrawText(int x, int y, ImColor color, const char* text, bool outline = false) {
		if (outline) {
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetDefaultFont(), ImGui::GetDefaultFont()->FontSize, ImVec2(x + 2, y + 2), ImColor(0, 0, 0), text);
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetDefaultFont(), ImGui::GetDefaultFont()->FontSize, ImVec2(x - 2, y - 2), ImColor(0, 0, 0), text);
		}
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetDefaultFont(), ImGui::GetDefaultFont()->FontSize, ImVec2(x, y), color, text);
	}

	void DrawRect(int x, int y, int w, int h, ImColor color, int thickness, bool outline = false) {
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(w, h), color, 0, 0, thickness);
		if (outline) {
			ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x + 1, y + 1), ImVec2(w - 2, h - 2), ImColor(0, 0, 0), 0, 0);
			ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x - 1, y - 1), ImVec2(w + 2, h + 2), ImColor(0, 0, 0), 0, 0);
		}
	}
}