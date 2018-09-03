#pragma once

#include <Windows.h>
#include <random>
#include <chrono>

namespace Ascii
{
	enum Colours
	{
		DARK_RED        = FOREGROUND_RED,
		DARK_GREEN      = FOREGROUND_GREEN,
		DARK_BLUE       = FOREGROUND_BLUE,
		DARK_YELLOW     = FOREGROUND_RED | FOREGROUND_GREEN,
		DARK_PURPLE     = FOREGROUND_RED | FOREGROUND_BLUE,
		DARK_CYAN       = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARK_GRAY       = FOREGROUND_INTENSITY,
		RED             = FOREGROUND_INTENSITY | FOREGROUND_RED,
		GREEN           = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		BLUE            = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		YELLOW          = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		PURPLE          = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		CYAN            = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		WHITE           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY		    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		BLACK           = 0,

		BG_DARK_RED     = BACKGROUND_RED,
		BG_DARK_GREEN   = BACKGROUND_GREEN,
		BG_DARK_BLUE    = BACKGROUND_BLUE,
		BG_DARK_YELLOW  = BACKGROUND_RED | BACKGROUND_GREEN,
		BG_DARK_PURPLE  = BACKGROUND_RED | BACKGROUND_BLUE,
		BG_DARK_CYAN    = BACKGROUND_GREEN | BACKGROUND_BLUE,
		BG_DARK_GRAY    = BACKGROUND_INTENSITY,
		BG_RED          = BACKGROUND_INTENSITY | BACKGROUND_RED,
		BG_GREEN        = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		BG_BLUE         = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		BG_YELLOW       = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		BG_PURPLE       = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		BG_CYAN         = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		BG_WHITE        = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		BG_GRAY         = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		BG_BLACK        = 0
	};

	class Vector2
	{
	public:
		short x, y;
		Vector2::Vector2(int xPosition, int yPosition);
		Vector2::Vector2() { x = 0; y = 0; };
	};

	class Rand
	{
	private:
		long long m_seed;
		std::mt19937 m_gen;
	public:
		Rand::Rand();
		Rand::Rand(long long seed);
		int range(int min, int max);
	};

	static HANDLE handle;
	static HWND console;
	static int width, height;

	Vector2 getSize(HANDLE handle);

	void init(HANDLE ConsoleHandle, HWND console, std::string consoleName);
	void setWindowName(std::string consoleName);

	void prstr(char* contents, Vector2 position);
	void prstr(char* contents, Vector2 position, WORD attr);
	void prchar(char letter, Vector2 position);
	void prchar(char letter, Vector2 position, WORD attr);
}