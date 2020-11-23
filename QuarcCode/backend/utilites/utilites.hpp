#pragma once

#include <windows.h>
#include <string>
#include <shobjidl.h> 
#include <locale>
#include <codecvt>

class QuarcUtils
{
public:
	std::wstring selectFileW();
};

extern QuarcUtils* qUtils;