#pragma once
#include "includes.h"

namespace Menu {
	bool IsUIOpen() {
		return Settings::ToggleMenu;
	}

	void RenderUI() {
		/*Style*/
        ImGuiStyle* style = &ImGui::GetStyle();
        style->WindowPadding.x = 0.f;
        style->WindowPadding.y = 0.f;
        style->WindowBorderSize = 0.f;
        style->Colors[ImGuiCol_WindowBg] = ImColor(151, 0, 4);
        style->Colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 150);
        style->Colors[ImGuiCol_Border] = ImColor(72, 60, 106);
        style->Colors[ImGuiCol_CheckMark] = ImColor(255, 17, 23, 255);
        style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 17, 23, 255);
        style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 17, 23, 200);
        style->Colors[ImGuiCol_FrameBg] = ImColor(168, 0, 4);
        style->Colors[ImGuiCol_FrameBgActive] = ImColor(168, 0, 4);
        style->Colors[ImGuiCol_FrameBgHovered] = ImColor(168, 0, 4);
		/*Menu*/
		ImGui::Begin("Lumina", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(Globals::WindowPosition.x * 0.5f, Globals::WindowPosition.y * 0.5f), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(700, 650));
        ImGui::Image(Globals::MenuBackground, ImVec2(700, 650));
        ImGui::BringDownEx(0);
        ImGui::BeginChild("##TopBar", ImVec2(ImGui::GetWindowSize().x, 70)); {
            ImGui::BringDown(10);
            ImGui::ColorBar("##TopColorBar", ImVec2(ImGui::GetWindowSize().x, 1));
            ImGui::BringRightAndDown(ImVec2(10, 12));
            ImGui::PushFont(Globals::TitleFont); ImGui::Text("Lumina.cc"); ImGui::PopFont();
            ImGui::EndChild();
        }
        ImGui::BringRightAndDown(ImVec2(15, 5));
        ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(23, 21, 21, 255));
        ImGui::BeginChild("##MenuBar", ImVec2(670, 560), true); {
            ImGui::PopStyleColor();
            ImGui::CreateGroupBox("Visuals", "aimbot_child", 1);
            ImGui::PushFont(Globals::SmallFont);
            ImGui::Checkbox("Enable", &Settings::EnableESP);
            ImGui::Checkbox("Box ESP", &Settings::BoxESP);
            ImGui::Checkbox("Name ESP", &Settings::NameESP);
            ImGui::PopFont();
            ImGui::EndGroupBox();
            ImGui::EndChild();
        }
		ImGui::End();
	}
}