#include <stdexcept>

#include "frontend/libraries/borderless/borderless.hpp"

#include <oleidl.h>

int CALLBACK wWinMain(HINSTANCE /*inst*/, HINSTANCE /*prev*/, LPWSTR /*cmd*/, int /*show*/) {

	OleInitialize(NULL);

	try
	{
		BorderlessWindow window;
	}
	catch (const std::exception& e)
	{
		::MessageBoxA(nullptr, e.what(), "QuarcCode Exception Handler", MB_OK | MB_ICONERROR);
	}

	OleUninitialize();
}
