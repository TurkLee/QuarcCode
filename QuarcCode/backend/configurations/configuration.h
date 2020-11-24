#pragma once

#include "saver.h"
#include "../filesystem//filesystem.h"

#define _CRT_SECURE_NO_WARNINGS

class QuarcSaver
{
public:

	struct settings
	{
		int latestfilessize;
	};

	QuarcSaver();

	void SaveLatestFiles();
	void LoadLatestFiles();
};

extern QuarcSaver qSaver;