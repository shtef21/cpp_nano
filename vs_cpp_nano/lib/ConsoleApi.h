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

class Console
{
private:
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_FONT_INFO cfi;
	HANDLE c_handle;
	HWND hwnd;
	CHAR_INFO* buffer;

	void set_buffer(int cols, int rows)
	{
		if (this->buffer != nullptr)
		{
			delete[] this->buffer;
		}
		int total = rows * cols;
		this->buffer = new CHAR_INFO[total];
		memset(this->buffer, 0, sizeof(CHAR_INFO) * total);
	}

	void refresh_buffer()
	{
		SetConsoleScreenBufferSize(this->c_handle, this->get_size_buffer());
	}

public:

	Console()
	{
		this->buffer = nullptr;
		this->c_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(c_handle, &csbi);
		GetCurrentConsoleFont(c_handle, FALSE, &cfi);
		hwnd = GetConsoleWindow();
		refresh_buffer();
	}

	// Get column and row count of buffer
	COORD get_size_buffer()
	{
		GetConsoleScreenBufferInfo(c_handle, &csbi);
		COORD size = {
			csbi.srWindow.Right - csbi.srWindow.Left + 1,
			csbi.srWindow.Bottom - csbi.srWindow.Top + 1
		};
		return size;
	}

	// Get pixel width and height of buffer
	COORD get_size_buffer_px()
	{
		GetConsoleScreenBufferInfo(c_handle, &csbi);
		COORD font_size = this->get_font_size();
		COORD size = {
			csbi.srWindow.Right - csbi.srWindow.Left + 1,
			csbi.srWindow.Bottom - csbi.srWindow.Top + 1
		};
		size.X *= font_size.X;
		size.Y *= font_size.Y;
		return size;
	}

	// Get size of window not counting the write area
	COORD get_padding()
	{
		COORD padd;
		COORD bsize = this->get_size_buffer_px();
		COORD wsize = this->get_window_size();

		padd.X = wsize.X - bsize.X;
		padd.Y = wsize.Y - bsize.Y;
		return padd;
	}

	void set_size_abs(int columns, int rows)
	{
		RECT pos = this->get_window_pos();
		COORD padd = this->get_padding();
		COORD font = this->get_font_size();
		MoveWindow(this->hwnd, pos.left, pos.top, columns * font.X + padd.X, rows * font.Y + padd.Y, TRUE);
		refresh_buffer();
	}

	void set_size_rel(int col_change, int row_change)
	{
		COORD curr = this->get_size_buffer();
		RECT pos = this->get_window_pos();
		COORD font = get_font_size();
		LONG new_right = pos.right + (col_change * font.X);
		LONG new_bottom = pos.bottom + (row_change * font.Y);
		MoveWindow(this->hwnd, pos.left, pos.top, new_right - pos.left, new_bottom - pos.top, TRUE);
		refresh_buffer();
	}

	COORD get_font_size()
	{
		COORD size = { cfi.dwFontSize.X, cfi.dwFontSize.Y };
		return size;
	}

	// Get window position (includes scrollbar and title bar)
	RECT get_window_pos()
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		return rect;
	}

	COORD get_window_size()
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		COORD size;
		size.X = short(rect.right - rect.left);
		size.Y = short(rect.top - rect.bottom);
		return size;
	}

	void set_cursor(int x, int y)
	{
		SetConsoleCursorPosition(this->c_handle, { (short)x, (short)y });
	}

	void write(std::vector<std::string> screen)
	{
		COORD size = this->get_size_buffer();
		SMALL_RECT sr = { 0, 0, size.X - 1, size.Y - 1 };
		CHAR_INFO default_ch;
		

		default_ch.Char.AsciiChar = L' ';
		default_ch.Attributes = FOREGROUND::FG_WHITE | BACKGROUND::BG_BLACK;
		std::vector<CHAR_INFO> buffer(size.X * size.Y, default_ch);

		for (int i = 0; i < screen.size(); ++i)
		{
			if (i >= size.Y)
			{
				break;
			}
			for (int j = 0; j < screen[i].length(); ++j)
			{
				if (j >= size.X)
				{
					break;
				}
				buffer[i * size.X + j].Char.AsciiChar = screen[i][j];
			}
		}

		WriteConsoleOutput(this->c_handle, &buffer[0], size, { 0,0 }, &sr);
	}

} Console;
