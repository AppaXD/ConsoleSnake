#include "GameEngine.hpp"

void age::init(std::string consoleName)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND ConsoleWindow = GetConsoleWindow();

	handle = ConsoleHandle;
	console = ConsoleWindow;

	Ascii::init(handle, console, consoleName);
}

void age::init(std::string consoleName, HANDLE ConsoleHandle)
{
	HWND ConsoleWindow = GetConsoleWindow();
	handle = ConsoleHandle;
	console = ConsoleWindow;

	Ascii::init(handle, console, consoleName);
}

void age::init(std::string consoleName, HANDLE ConsoleHandle, HWND ConsoleWindow)
{
	handle = ConsoleHandle;
	console = ConsoleWindow;

	Ascii::init(handle, console, consoleName);
}

void age::print(char contents, Ascii::Vector2 position, short attr)
{
	Ascii::prchar(contents, position, attr);
}

void age::print(std::string contents, Ascii::Vector2 position, short attr)
{
	char* str = const_cast<char*>(contents.c_str());
	Ascii::prstr(str, position, attr);
}

void age::setCursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = visible;
	SetConsoleCursorInfo(handle, &cursorInfo);
}