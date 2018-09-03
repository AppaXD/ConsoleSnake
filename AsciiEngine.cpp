#include "AsciiEngine.hpp"
#include <iostream>

Ascii::Vector2::Vector2(int xPosition, int yPosition)
{
	x = xPosition;
	y = yPosition;
}

Ascii::Vector2 Ascii::getSize(HANDLE handle)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return Ascii::Vector2(csbi.dwSize.X, csbi.dwSize.Y);
}

void Ascii::init(HANDLE ConsoleHandle, HWND wConsole, std::string consoleName)
{
	console = wConsole;
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	handle = ConsoleHandle;
	SetConsoleTitle(consoleName.c_str());
}

void Ascii::setWindowName(std::string consoleName)
{
	SetConsoleTitle(consoleName.c_str());
}

void Ascii::prstr(char* contents, Vector2 position)
{
	COORD pos;
	pos.X = position.x;
	pos.Y = position.y;
	DWORD written;
	WriteConsoleOutputCharacter(handle, contents, strlen(contents), pos, &written);
}

void Ascii::prstr(char* contents, Vector2 position, WORD attr)
{
	COORD pos;
	pos.X = position.x;
	pos.Y = position.y;
	DWORD written;
	size_t len = strlen(contents);

	WORD attrs[80];
	for (unsigned int i = 0; i < len; i++)
	{
		attrs[i] = attr;
	}

	WriteConsoleOutputAttribute(handle, attrs, len, pos, &written);
	WriteConsoleOutputCharacter(handle, contents, len, pos, &written);
}

void Ascii::prchar(char letter, Vector2 position)
{
	COORD pos;
	pos.X = position.x;
	pos.Y = position.y;
	DWORD written;
	const char* ch = &letter;
	WriteConsoleOutputCharacter(handle, ch, strlen(ch), pos, &written);
}

void Ascii::prchar(char letter, Vector2 position, WORD attr)
{
	COORD pos;
	pos.X = position.x;
	pos.Y = position.y;
	DWORD written;
	const char* ch = &letter;
	size_t len = strlen(ch);

	WORD attrs[128];
	for (unsigned int i = 0; i < len; i++)
	{
		attrs[i] = attr;
	}

	WriteConsoleOutputAttribute(handle, attrs, len, pos, &written);
	WriteConsoleOutputCharacter(handle, ch, len, pos, &written);
}

Ascii::Rand::Rand()
{
	m_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	m_gen = std::mt19937(m_seed);
}

Ascii::Rand::Rand(long long seed)
{
	m_seed = seed;
	m_gen = std::mt19937(m_seed);
}

int Ascii::Rand::range(int min, int max)
{
	std::uniform_int_distribution<int> rng(min, max);
	return rng(m_gen);
}