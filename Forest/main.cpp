#include <iostream>
#include <Windows.h>

#include "Window.h"

#undef main

#if !defined(_DEBUG)
int wWinMain(HINSTANCE hInst, HINSTANCE prevInst, LPWSTR szCmdLine, int nCmdShow)
{
	using namespace Forest::Core;

	Window* window = new Window();

	window->Run();

	delete window;
	window = nullptr;

	return 0;
}
#else
int main(int argc, char*argv[])
{
	using namespace Forest::Core;

	Window* window = new Window();

	window->Run();

	delete window;
	window = nullptr;

	return 0;
}
#endif