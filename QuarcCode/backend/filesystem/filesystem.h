#pragma once

#include <Windows.h>
#include <string>
#include <list>
#include <sstream>
#include <ostream>
#include <fstream>
#include <locale>
#include <codecvt>

#include "../utilites/utilites.hpp"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

class QuarcFiles
{
public:
	void OpenFile();


private:
	struct file
	{
		std::string path;
		std::string filename;
	};

public:
	std::list<file> files_map;
};

extern QuarcFiles qFiles;