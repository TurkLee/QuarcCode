#pragma once

#include "saver.h"
#include "../filesystem//filesystem.h"

#define _CRT_SECURE_NO_WARNINGS

namespace QuarcSaverN
{
	struct settings
	{
		int latestfilessize;
	};
}

class QuarcSaver
{
public:

	QuarcSaver();

	void SaveSettings();
	void LoadSettings();
};

extern QuarcSaver qSaver;