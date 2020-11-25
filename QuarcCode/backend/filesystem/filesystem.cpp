#include "filesystem.h"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

std::string QuarcFiles::openAndConvertate()
{
	std::wstring to_convert = qUtils->selectFileW();

	std::string converted_str(to_convert.begin(), to_convert.end());

	return converted_str;
}

std::string  QuarcFiles::base_name(std::string& path, std::string& delims)
{
	return path.substr(path.find_last_of(delims) + 1);
}

std::string QuarcFiles::remove_extension(std::string& filename)
{
	typename std::string::size_type const p(filename.find_last_of('.'));
	return p > 0 && p != std::string::npos ? filename.substr(0, p) : filename;
}

std::string QuarcFiles::get_file_extension(const std::string& FileName)
{
	if (FileName.find_last_of(".") != std::string::npos)
		return FileName.substr(FileName.find_last_of(".") + 1);
	return "";
}

void QuarcFiles::OpenFile()
{
	std::string filepath = openAndConvertate();

	if (filepath != "")
		files_map.push_back({ filepath , base_name(filepath, qFiles.delimer), get_file_extension(filepath) });
}

QuarcFiles qFiles;