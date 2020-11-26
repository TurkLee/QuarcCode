#include "interface.hpp"

#include <windows.h>
#include <shobjidl.h>

#include "../../../backend/editor/editor.h"
#include "../../../backend/filesystem/filesystem.h"

bool Preferencesbool = false;

QuarcInterface::QuarcInterface()
{

	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Spacing();
		ImGui::SameLine(54);

		if (ImGui::BeginMenu("File", true))
		{
			if (ImGui::Button("Open File                                            ", { 200,0 }))
			{
				qFiles.OpenFile();
			}

			if (ImGui::Button("Save File                                   Ctrl+S", { 200,0 }))
			{
				std::ofstream out;

				out.open(_selectedfilepath);
				out << editor.GetText() << std::endl;
				out.close();
			}

			ImGui::Separator();

			if (ImGui::Button("Preferences                                        ", { 200,0 })) { Preferencesbool = !Preferencesbool; }

			ImGui::EndMenu();
		}

		if (qFiles.files_map.size() > 0)
		{
			if (ImGui::BeginMenu("Edit", true))
			{
				if (editor.CanUndo()) { if (ImGui::Button("Undo                                         Ctrl+Z", { 200,0 }))editor.Undo(); }
				else { ImGui::InactiveButton("Undo                                         Ctrl+Z", { 200,0 }); }

				if (editor.CanRedo()) { if (ImGui::Button("Redo                                         Ctrl+Y", { 200,0 }))	editor.Redo(); }
				else { ImGui::InactiveButton("Redo                                         Ctrl+Y", { 200,0 }); }

				ImGui::Separator();

				if (editor.HasSelection()) { if (ImGui::Button("Cut                                            Ctrl+X", { 200,0 }))		editor.Cut(); }
				else { ImGui::InactiveButton("Cut                                            Ctrl+X", { 200,0 }); }

				if (editor.HasSelection()) { if (ImGui::Button("Copy                                          Ctrl+C", { 200,0 })) editor.Copy(); }
				else { ImGui::InactiveButton("Copy                                          Ctrl+C", { 200,0 }); }

				if (ImGui::Button("Paste                                         Ctrl+V", { 200,0 })) editor.Paste();

				ImGui::EndMenu();
			}
		}
	}

	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize - ImVec2(0, 18));
	ImGui::SetNextWindowPos({ 0, 19 });
	ImGui::Begin("##maincontent", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImGui::GetWindowPos() - ImVec2(0, 19), ImGui::GetWindowPos() + ImVec2(50, ImGui::GetIO().DisplaySize.y), ImColor(0.19f, 0.19f, 0.19f));

		if (!Preferencesbool)
		{
			ImGui::GetOverlayDrawList()->AddRectFilled(ImGui::GetWindowPos() + ImVec2(50, ImGui::GetIO().DisplaySize.y - 40), ImGui::GetWindowPos() + ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), qFiles.files_map.size() > 0 ? ImColor(72, 148, 49, 150) : ImColor(118, 49, 148, 150));
			ImGui::GetOverlayDrawList()->AddText(ImGui::GetWindowPos() + ImVec2(56, ImGui::GetIO().DisplaySize.y - 36), ImColor(0.95f, 0.95f, 0.95f), _selectedfilepath.c_str());

			if (ImGui::IsKeyPressed(VK_CONTROL) && ImGui::IsKeyPressed(0x53))
			{
				std::ofstream out;

				out.open(_selectedfilepath);
				out << editor.GetText() << std::endl;
				out.close();
			}

			if (qFiles.files_map.size() > 0)
			{
				ImGui::SetCursorPos({ 50, 0 });
				ImGui::BeginGroup();
				for (auto iter = qFiles.files_map.begin(); iter != qFiles.files_map.end(); iter++)
				{
					ImGui::PushID(distance(qFiles.files_map.begin(), iter));
					if (ImGui::TabEx(iter->filename.c_str(), ImVec2{ ImGui::CalcTextSize(iter->filename.c_str()).x + 20, 30 }, _selectedtab == distance(qFiles.files_map.begin(), iter)))
						_selectedfilepath = iter->path,
						_selectedtab = distance(qFiles.files_map.begin(), iter);
					ImGui::PopID();

					if (ImGui::IsItemClicked(0))
					{
						editor.SetReadOnly(false);

						std::ifstream t(iter->path);

						if (t.good())
						{
							std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
							editor.SetText(str);
						}

						t.close();
					}
					else if (ImGui::IsItemClicked(1))
					{
						qFiles.files_map.erase(iter);
						editor.SetText("");
						_selectedfilepath = "";
					}

					ImGui::SameLine();
				}
				ImGui::EndGroup();


				ImGui::SetCursorPos({ 50, 30 });
				ImGui::PushFont(firacode);
				editor.Render("file", { ImGui::GetIO().DisplaySize.x - 50, ImGui::GetIO().DisplaySize.y - 55 - 15 });
				ImGui::PopFont();
			}
			else
			{
				ImGui::GetWindowDrawList()->AddText(tahomabig, 32, ImGui::GetWindowPos() + ImVec2(90, 33), ImColor(0.95f, 0.95f, 0.95f), "QuarcCode");
				ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowPos() + ImVec2(91, 70), ImColor(0.95f, 0.95f, 0.95f), "Welcome to QuarcCode. QuarcCode is an ultra - lightweight IDE for developing and compiling C / C ++ projects.\nQuarcCode is also suitable for editing projects in other languages, from Lua scripts to PHP.");
				ImGui::GetWindowDrawList()->AddLine(ImGui::GetWindowPos() + ImVec2(91, 105), ImGui::GetWindowPos() + ImVec2(218, 105), ImColor(0.75f, 0.75f, 0.75f));
				ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowPos() + ImVec2(91, 113), ImColor(0.75f, 0.75f, 0.75f), "Designed with love by pers0na2.");
				ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowPos() + ImVec2(91, ImGui::GetIO().DisplaySize.y - 113), ImColor(0.75f, 0.75f, 0.75f), "MinGW is used to compile C / C ++ projects, as well as pieces of my developments.\nDirectX9 and ImGui are used to render the interface.");
			}
		}
		else
		{

		}
	}
	ImGui::End();
}
