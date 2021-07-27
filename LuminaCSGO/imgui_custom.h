#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "includes.h"
#include "ImGui/imgui_internal.h"

namespace ImGui {
	void BringDown(int y) { SetCursorPosY(GetCursorPosY() + y); }
	void BringDownEx(int y) { SetCursorPosY(y); }
	void BringUp(int y) { SetCursorPosY(GetCursorPosY() - y); }
	void BringRight(int x) { SetCursorPosX(GetCursorPosX() + x); }
	void BringLeft(int x) { SetCursorPosX(GetCursorPosX() - x); }
	void BringRightAndDown(ImVec2 xy) { BringRight(xy.x); BringDown(xy.y); }
	void BringRightAndUp(ImVec2 xy) { BringRight(xy.x); BringUp(xy.y); }
	void BringLeftAndDown(ImVec2 xy) { BringLeft(xy.x); BringDown(xy.y); }
	void BringLeftAndUp(ImVec2 xy) { BringLeft(xy.x); BringUp(xy.y); }

	bool ColorBarEx(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems) return false;
		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = CalcTextSize(label, NULL, true);
		ImVec2 pos = window->DC.CursorPos;
		if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
		ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
		const ImRect bb(pos, pos + size);
		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, id)) return false;
		if (window->Flags & ImGuiItemFlags_ButtonRepeat) flags |= ImGuiButtonFlags_Repeat;
		auto black = ImGui::GetColorU32(ImVec4(0.0, 0.0, 0.0, 0.43));
		ImVec2 p = ImGui::GetCursorScreenPos();
		window->DrawList->AddRectFilledMultiColor(ImVec2(p.x, p.y - 6), ImVec2(p.x + ImGui::GetWindowWidth() / 2, p.y - 4), ImColor(12, 12, 12), ImColor(12, 12, 12), ImColor(12, 12, 12), ImColor(12, 12, 12));
		window->DrawList->AddRectFilledMultiColor(ImVec2(p.x + ImGui::GetWindowWidth() / 2, p.y - 6), ImVec2(p.x + ImGui::GetWindowWidth(), p.y - 4), ImColor(12, 12, 12), ImColor(12, 12, 12), ImColor(12, 12, 12), ImColor(12, 12, 12));
		window->DrawList->AddRectFilledMultiColor(ImVec2(p.x + 1, p.y - 5), ImVec2(p.x + ImGui::GetWindowWidth() / 2, p.y - 3), ImColor(201, 3, 93), ImColor(131, 20, 152), ImColor(131, 20, 152), ImColor(201, 3, 93));
		window->DrawList->AddRectFilledMultiColor(ImVec2(p.x + ImGui::GetWindowWidth() / 2, p.y - 5), ImVec2(p.x + ImGui::GetWindowWidth() - 1, p.y - 3), ImColor(131, 20, 152), ImColor(66, 42, 215), ImColor(66, 42, 215), ImColor(131, 20, 152));
		window->DrawList->AddRectFilledMultiColor(ImVec2(p.x + 1, p.y - 4), ImVec2(p.x + ImGui::GetWindowWidth() / 2, p.y - 2), black, black, black, black);
		window->DrawList->AddRectFilledMultiColor(ImVec2(p.x + ImGui::GetWindowWidth() / 2, p.y - 4), ImVec2(p.x + ImGui::GetWindowWidth() - 1, p.y - 2), black, black, black, black);
		return false;
	}

	bool ColorBar(const char* label, const ImVec2& size_arg) {
		return ColorBarEx(label, size_arg, 0);
	}

	void CreateGroupBox(const char* title, const char* unique_id, int pos)
	{

		PushStyleColor(ImGuiCol_ChildBg, IM_COL32(16, 13, 32, 50));
		PushStyleColor(ImGuiCol_Border, IM_COL32(23, 21, 21, 255));

		ImVec2 size;
		switch (pos) {
		case 1: //Full left
			size = ImVec2(320, 540);
			SetCursorPos(ImVec2(10, 10));
			break;
		case 2: //Full right
			size = ImVec2(320, 540);
			SetCursorPos(ImVec2(340, 10));
			break;
		case 3: //Smalltopleft
			size = ImVec2(320, (540 / 2) - 5);
			SetCursorPos(ImVec2(10, 10));
			break;
		case 4: //Smalltopright
			size = ImVec2(320, (540 / 2) - 5);
			SetCursorPos(ImVec2(340, 10));
			break;
		case 5: //Smallbottumleft
			size = ImVec2(320, (540 / 2) - 5);
			SetCursorPos(ImVec2(10, 285));
			break;
		case 6: //smallbottumright
			size = ImVec2(320, (540 / 2) - 5);
			SetCursorPos(ImVec2(340, 285));
			break;
		}

		BeginChild(title, size, true);
		{
			PopStyleColor();
			PopStyleColor();

			PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
			PushStyleColor(ImGuiCol_Border, IM_COL32(23, 21, 21, 255));
			BeginChild(unique_id, ImVec2(size.x, 30), true);
			{
				PopStyleColor();
				PopStyleColor();
			    BringRightAndDown(ImVec2(10, 6));
				ImGui::PushFont(Globals::SmallFont);
				ImGui::Text(title);
				ImGui::PopFont();
			}
			EndChild();

			Spacing();
			Spacing();
		}
	}

	void EndGroupBox() { EndChild(); }
}