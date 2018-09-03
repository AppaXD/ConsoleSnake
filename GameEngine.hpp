#pragma once

#include "AsciiEngine.hpp"

namespace age
{
	static HANDLE handle;
	static HWND console;

	void init(std::string consoleName);
	void init(std::string consoleName, HANDLE consoleHandle);
	void init(std::string consoleName, HANDLE consoleHandle, HWND consoleWindow);

	void print(char contents, Ascii::Vector2 position, short attr = Ascii::Colours::GRAY);
	void print(std::string contents, Ascii::Vector2 position, short attr = Ascii::Colours::GRAY);

	void setCursorVisible(bool visible);
}