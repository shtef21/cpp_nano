#pragma once

#include <Windows.h>
#include <vector>

namespace ConsoleConst
{
	enum FOREGROUND
	{
		FG_BLACK = 0x0000,
		FG_DARK_BLUE = 0x0001,
		FG_DARK_GREEN = 0x0002,
		FG_DARK_CYAN = 0x0003,
		FG_DARK_RED = 0x0004,
		FG_DARK_MAGENTA = 0x0005,
		FG_DARK_YELLOW = 0x0006,
		FG_GREY = 0x0007,
		FG_DARK_GREY = 0x0008,
		FG_BLUE = 0x0009,
		FG_GREEN = 0x000A,
		FG_CYAN = 0x000B,
		FG_RED = 0x000C,
		FG_MAGENTA = 0x000D,
		FG_YELLOW = 0x000E,
		FG_WHITE = 0x000F
	};

	enum BACKGROUND
	{
		BG_BLACK = 0x0000,
		BG_DARK_BLUE = 0x0010,
		BG_DARK_GREEN = 0x0020,
		BG_DARK_CYAN = 0x0030,
		BG_DARK_RED = 0x0040,
		BG_DARK_MAGENTA = 0x0050,
		BG_DARK_YELLOW = 0x0060,
		BG_GREY = 0x0070,
		BG_DARK_GREY = 0x0080,
		BG_BLUE = 0x0090,
		BG_GREEN = 0x00A0,
		BG_CYAN = 0x00B0,
		BG_RED = 0x00C0,
		BG_MAGENTA = 0x00D0,
		BG_YELLOW = 0x00E0,
		BG_WHITE = 0x00F0
	};

	enum SOLID_CHAR
	{
		FULL = 0x2588,
		STRONG = 0x2593,
		MEDIUM = 0x2592,
		WEAK = 0x2591,
		EMPTY = 0x32
	};

	// Get more values at https://docs.microsoft.com/en-us/windows/console/char-info-str
	enum POINTER
	{
		PTR_NONE = 0x0000,
		PTR_LEFT_VERTICAL = 0x1000,
		PTR_UNDERSCORE = 0x8000
	};
}

using namespace ConsoleConst;

typedef unsigned int uint;

class ConsoleApi
{
private:


	uint width, height, f_width, f_height;

	SMALL_RECT init_dimensions()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		return csbi.srWindow;
	}

	COORD init_font_dimensions()
	{
		CONSOLE_FONT_INFO cfi;
		GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
		f_width = cfi.dwFontSize.X;
		f_height = cfi.dwFontSize.Y;
		return cfi.dwFontSize;
	}

public:

	ConsoleApi()
	{
		init_dimensions();
		init_font_dimensions();

	}

	COORD get_buffer_size()
	{
		init_dimensions();
		return { (short)width, (short)height };
	}

	void set_buffer_size(COORD size)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT write_area = { 0, 0, size.X, size.Y };
		SetConsoleWindowInfo(handle, TRUE, &write_area);
	}

} Console;
