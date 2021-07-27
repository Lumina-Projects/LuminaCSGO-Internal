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
        style->FrameBorderSize = 0.f;
        style->Colors[ImGuiCol_WindowBg] = ImColor(151, 0, 4);
        style->Colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 150);
        style->Colors[ImGuiCol_Border] = ImColor(72, 60, 106);
        style->Colors[ImGuiCol_CheckMark] = ImColor(255, 17, 23, 255);
        style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 17, 23, 255);
        style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 17, 23, 200);
        style->Colors[ImGuiCol_FrameBg] = ImColor(168, 0, 4);
        style->Colors[ImGuiCol_FrameBgActive] = ImColor(168, 0, 4);
        style->Colors[ImGuiCol_FrameBgHovered] = ImColor(168, 0, 4);
        style->Colors[ImGuiCol_Button] = ImColor(255, 0, 0, 255);
        style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0, 0);
        style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 0, 0, 0);
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
            ImGui::BringRightAndUp(ImVec2(100, 40));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(0, 0, 0, 0));
            ImGui::BeginChild("##ButtonsBar", ImVec2(595, 50)); {
                ImGui::PopStyleColor();
                ImGui::PushStyleColor(ImGuiCol_Text, Settings::MenuTab == 1 ? ImColor(255, 17, 23, 255) : ImColor(211, 209, 209, 255));
                ImGui::BringRightAndDown(ImVec2(20, 13.5f)); ImGui::PushFont(Globals::IconFont); ImGui::Text("a"); if (ImGui::IsItemClicked()) Settings::MenuTab = 1; ImGui::PopFont(); ImGui::SameLine(); ImGui::BringDown(1); ImGui::Text("Aim");  if (ImGui::IsItemClicked()) Settings::MenuTab = 1; ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Text, Settings::MenuTab == 2 ? ImColor(255, 17, 23, 255) : ImColor(211, 209, 209, 200));
                ImGui::BringRightAndUp(ImVec2(10, 1)); ImGui::PushFont(Globals::IconFont); ImGui::Text("v"); if (ImGui::IsItemClicked()) Settings::MenuTab = 2; ImGui::PopFont(); ImGui::SameLine(); ImGui::BringDown(1); ImGui::Text("Visuals");  if (ImGui::IsItemClicked()) Settings::MenuTab = 2; ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Text, Settings::MenuTab == 3 ? ImColor(255, 17, 23, 255) : ImColor(211, 209, 209, 200));
                ImGui::BringRightAndUp(ImVec2(10, 1)); ImGui::PushFont(Globals::IconFont); ImGui::Text("m"); if (ImGui::IsItemClicked()) Settings::MenuTab = 3; ImGui::PopFont(); ImGui::SameLine(); ImGui::BringDown(1); ImGui::Text("Misc");  if (ImGui::IsItemClicked()) Settings::MenuTab = 3;
                ImGui::PopStyleColor(3);
                ImGui::EndChild();
            }
            ImGui::EndChild();
        }
        ImGui::BringRightAndDown(ImVec2(15, 5));
        ImGui::PushStyleColor(ImGuiCol_Border, ImColor(23, 21, 21, 255));
        ImGui::BeginChild("##MenuBar", ImVec2(670, 560), true); {
            ImGui::PopStyleColor();
            switch (Settings::MenuTab) {
            case 1:
                break;
            case 2:
                ImGui::CreateGroupBox("ESP", "esp_child", 3);
                ImGui::Checkbox("Enable", &Settings::Visuals.bEnable);
                ImGui::Checkbox("Box", &Settings::Visuals.bEnableBox);
                if (Settings::Visuals.bEnableBox) {
                    ImGui::SameLine();
                    if (ImGui::BeginCombo("##BoxESPTypes", Settings::Visuals.Box.szBoxTypes[Settings::Visuals.Box.iBoxType], ImGuiComboFlags_NoArrowButton)) {
                        for (int i = 0; i < IM_ARRAYSIZE(Settings::Visuals.Box.szBoxTypes); i++) {
                            const bool bIsSelected = (Settings::Visuals.Box.iBoxType == i);
                            if (ImGui::Selectable(Settings::Visuals.Box.szBoxTypes[i], &bIsSelected)) Settings::Visuals.Box.iBoxType = i;
                            if (bIsSelected) ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }
                }
                ImGui::Checkbox("Snapline", &Settings::Visuals.bSnapline);
                ImGui::Checkbox("Name", &Settings::Visuals.bName);
                ImGui::EndGroupBox();
                break;
            case 3:
                ImGui::CreateGroupBox("Misc", "misc_child", 1);
                ImGui::Checkbox("Recoil Crosshair", (bool*)&Settings::Misc.bRecoilCrosshair);
                ImGui::EndGroupBox();
                break;
            default:
                break;
            }
            ImGui::EndChild();
        }
		ImGui::End();
	}
}