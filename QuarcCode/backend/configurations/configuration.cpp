#include "configuration.h"

#define _CRT_SECURE_NO_WARNINGS

QuarcSaver::QuarcSaver()
{

}

std::string GetTempDataPath()
{
	return getenv("APPDATA");
}

void QuarcSaver::SaveLatestFiles()
{
	CreateDirectoryA(std::string(GetTempDataPath() + "//QuarcCode").c_str(), NULL);

	Saver::InitPath(std::string(GetTempDataPath() + "//QuarcCode//data.qcd").c_str());

	Saver::SaveCvar((char*)"Data", (char*)"latest_files", (int)qFiles.files_map.size());

	for (auto iter = qFiles.files_map.begin(); iter != qFiles.files_map.end(); iter++)
	{
		std::string section_name = "LatestFile_";
		section_name.append(std::to_string(distance(qFiles.files_map.begin(), iter)));

		Saver::SaveCvar((char*)section_name.c_str(), (char*)"path", iter->path.c_str());
		Saver::SaveCvar((char*)section_name.c_str(), (char*)"filename", iter->filename.c_str());
		Saver::SaveCvar((char*)section_name.c_str(), (char*)"extension", iter->extension.c_str());
	}
}

void QuarcSaver::LoadLatestFiles()
{
	CreateDirectoryA(std::string(GetTempDataPath() + "//QuarcCode").c_str(), NULL);

	Saver::InitPath(std::string(GetTempDataPath() + "//QuarcCode//data.qcd").c_str());

	qFiles.files_map.clear();

	for (auto iter = 0; iter < Saver::LoadCvar((char*)"Data", (char*)"latest_files", (int)qFiles.files_map.size()); iter++)
	{
		std::string section_name = "LatestFile_";
		section_name.append(std::to_string(iter));

		qFiles.files_map.push_back({
			Saver::LoadCvar((char*)section_name.c_str(), (char*)"path", ""),
			Saver::LoadCvar((char*)section_name.c_str(), (char*)"filename", ""),
			Saver::LoadCvar((char*)section_name.c_str(), (char*)"extension", "")
			});
	}
}

QuarcSaver qSaver;