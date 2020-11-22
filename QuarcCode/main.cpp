#include <stdexcept>

#include "frontend/libraries/borderless/borderless.hpp"

int CALLBACK wWinMain(HINSTANCE /*inst*/, HINSTANCE /*prev*/, LPWSTR /*cmd*/, int /*show*/) {
	try
	{
		BorderlessWindow window;
	}
	catch (const std::exception& e)
	{
		::MessageBoxA(nullptr, e.what(), "Unhandled Exception", MB_OK | MB_ICONERROR);
	}
}
