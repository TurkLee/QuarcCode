#include "filesystem.h"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

std::string openAndConvertate()
{
	std::wstring to_convert = qUtils->selectFileW();

	std::string converted_str(to_convert.begin(), to_convert.end());

	return converted_str;
}

template<class T>
T base_name(T const& path, T const& delims = "/\\")
{
	return path.substr(path.find_last_of(delims) + 1);
}

template<class T>
T remove_extension(T const& filename)
{
	typename T::size_type const p(filename.find_last_of('.'));
	return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
}

std::string get_file_extension(const std::string& FileName)
{
	if (FileName.find_last_of(".") != std::string::npos)
		return FileName.substr(FileName.find_last_of(".") + 1);
	return "";
}

void QuarcFiles::OpenFile()
{
	std::string filepath = openAndConvertate();

	files_map.push_back(file{ filepath , base_name(filepath), get_file_extension(filepath) });
}

QuarcFiles qFiles;