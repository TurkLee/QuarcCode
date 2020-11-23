#include "interface.hpp"

#include <windows.h>
#include <shobjidl.h>

#include "../../../backend/editor/editor.h"

QuarcInterface::QuarcInterface()
{
	static TextEditor editor;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File", true))
		{

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit", true))
		{
			if (editor.CanUndo()){ if (ImGui::Button("Undo                                         Ctrl+Z", { 200,0 }))editor.Undo(); }
			else{ ImGui::InactiveButton("Undo                                         Ctrl+Z", { 200,0 }); }

			if (editor.CanRedo()) {	if (ImGui::Button("Redo                                         Ctrl+Y", { 200,0 }))	editor.Redo();}
			else{ ImGui::InactiveButton("Redo                                         Ctrl+Y", { 200,0 }); }

			ImGui::Separator();

			if (editor.HasSelection()) {	if (ImGui::Button("Cut                                            Ctrl+X", { 200,0 }))		editor.Cut();}
			else { ImGui::InactiveButton("Cut                                            Ctrl+X", { 200,0 }); }

			if (editor.HasSelection()) {	if (ImGui::Button("Copy                                          Ctrl+C", { 200,0 })) editor.Copy(); }
			else { ImGui::InactiveButton("Copy                                          Ctrl+C", { 200,0 }); }

			if (ImGui::Button("Paste                                         Ctrl+V", { 200,0 })) editor.Paste();

			ImGui::EndMenu();
		}
	}

	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize - ImVec2(0, 19));
	ImGui::SetNextWindowPos({ 0, 19 });
	ImGui::Begin("##maincontent", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
	{
		ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImVec2(50, ImGui::GetIO().DisplaySize.y), ImColor(0.19f, 0.19f, 0.19f));

		ImGui::SetCursorPos({ 50, 0 });
		editor.Render("file", { ImGui::GetIO().DisplaySize.x - 50, ImGui::GetIO().DisplaySize.y - 19 });
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
	}
	ImGui::End();
}
