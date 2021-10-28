#pragma once
// Console.h version with CHAR_INFO instead of wchar_t

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>

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

class Console_CI
{
public:
	struct Texture
	{
		const unsigned short attr;
		Texture(unsigned short console_attr) : attr(console_attr) {}
		Texture(FOREGROUND fg = FOREGROUND::FG_WHITE, BACKGROUND bg = BACKGROUND::BG_BLACK, POINTER pt = POINTER::PTR_NONE) : attr(pt | bg | fg) {}
	};
private:
	HANDLE console_out_handle;
	//HANDLE console_in_handle;
	SMALL_RECT write_area;
	CONSOLE_CURSOR_INFO console_cursor_info;
	CHAR_INFO *screen_buffer;
	std::wstring console_name;
	unsigned int _width, _height, _font_w, _font_h;
	// Old console data
	HANDLE original_console_handle;
	unsigned short original_console_attr;
	CONSOLE_CURSOR_INFO original_console_cursor_info;
	
	unsigned int total_length() const { return this->_width * this->_height; }
	void throw_error(const char *msg)
	{
		SetConsoleActiveScreenBuffer(original_console_handle);
		delete[] this->screen_buffer;
		system("cls");
		throw msg;
	}
	template<typename T>
	void swap(T& t1, T& t2)
	{
		T temp = t1;
		t1 = t2;
		t2 = temp;
	}
	void correct_coordinates(int& x, int& y)
	{
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;
		if (x > this->_width)
			x = this->_width - 1;
		if (y > this->_height)
			y = this->_height - 1;
	}
	void correct_rectangle_coordinates(int& x1, int& y1, int& x2, int& y2)
	{
		// Proper (x1, y1) is upper left and (x2, y2) bottom right
		if (x1 > x2)
			this->swap(x1, x2);
		if (y1 > y2)
			this->swap(y1, y2);
		this->correct_coordinates(x1, y1);
		this->correct_coordinates(x2, y2);
	}

	void adjust_tab(std::string& str)
	{
		std::string tabless = "";
		tabless.reserve(str.length());
		for (int i = 0; i < str.length(); ++i)
			if (str[i] == '\t')
				tabless += std::string(4 - i % 4, ' ');
			else
				tabless += str[i];
		str = std::move(tabless);
	}

public:
	~Console_CI()
	{
		SetConsoleActiveScreenBuffer(original_console_handle);
		delete[] this->screen_buffer;
		system("cls");
	}
	Console_CI(int w=0, int h=0, bool set_font=false, int fw=0, int fh=0)
	{
		if (w == 0 || h == 0)
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			// Get
		}
		if (fw == 0 || fh == 0)
		{
			CONSOLE_FONT_INFO cfi;
			GetCurrentConsoleFont(
				GetStdHandle(STD_OUTPUT_HANDLE),
				FALSE,
				&cfi
			);
			fw = cfi.dwFontSize.X;
			fh = cfi.dwFontSize.Y;
		}

		// Initialise variables
		this->_width = w;
		this->_height = h;
		this->_font_w = fw;
		this->_font_h = fh;

		this->console_out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		//this->console_in_handle = GetStdHandle(STD_INPUT_HANDLE);
		this->console_name = L"Console application";

		// Store old console values
		CONSOLE_SCREEN_BUFFER_INFO csb_info;
		if (!GetConsoleScreenBufferInfo(this->console_out_handle, &csb_info))
			this->throw_error("Unsuccessful call of GetConsoleScreenBufferInfo");

		// Make console
		this->write_area = { 0, 0, 1, 1 };
		SetConsoleWindowInfo(this->console_out_handle, TRUE, &this->write_area);

		COORD coord = { (short)this->_width, (short)this->_height };
		if (!SetConsoleScreenBufferSize(this->console_out_handle, coord))
			this->throw_error("Unsuccessful call of SetConsoleScreenBufferSize");

		if (!SetConsoleActiveScreenBuffer(this->console_out_handle))
			this->throw_error("Unsuccessful call of SetConsoleActiveScreenBuffer");

		if (set_font == true)
		{
			CONSOLE_FONT_INFOEX cfi;
			cfi.cbSize = sizeof(cfi);
			cfi.nFont = 0;
			cfi.dwFontSize.X = this->_font_w;
			cfi.dwFontSize.Y = this->_font_h;
			cfi.FontFamily = FF_DONTCARE;
			cfi.FontWeight = FW_NORMAL;
			wcscpy_s(cfi.FaceName, L"Consolas");
			if (!SetCurrentConsoleFontEx(this->console_out_handle, false, &cfi))
				this->throw_error("Unsuccessful call of SetCurrentConsoleFontEx");
		}

		if (!GetConsoleScreenBufferInfo(this->console_out_handle, &csb_info))
			this->throw_error("GetConsoleScreenBufferInfo");
		if (this->_height > csb_info.dwMaximumWindowSize.Y)
			this->throw_error("Screen or font height too big");
		if (this->_width > csb_info.dwMaximumWindowSize.X)
			this->throw_error("Screen or font width too big");

		this->write_area = { 0, 0, (short)(this->_width-1), (short)(this->_height-1) };
		if (!SetConsoleWindowInfo(this->console_out_handle, TRUE, &this->write_area))
			this->throw_error("Unsuccessful call of SetConsoleWindowInfo");

		this->screen_buffer = new CHAR_INFO[this->total_length()];
		memset(this->screen_buffer, 0, sizeof(CHAR_INFO) * this->total_length());

		SetConsoleTitle(&this->console_name[0]);
	}

	int get_width() const { return this->_width; }
	int get_height() const { return this->_height; }

	void print()
	{
		WriteConsoleOutput(
			this->console_out_handle,
			this->screen_buffer,
			{ (short)this->_width, (short)this->_height },
			{ 0,0 },
			&this->write_area
		);
	}

	void set_cursor(int x, int y)
	{
		this->correct_coordinates(x, y);
		SetConsoleCursorPosition(this->console_out_handle, { (short)x, (short)y });
	}
	void set_name(std::string s)
	{
		this->console_name = L"";
		for (int i = 0; i < s.length(); ++i)
			this->console_name += (wchar_t)s[i];
		SetConsoleTitle(&this->console_name[0]);
	}
	std::wstring get_name() const
	{
		return this->console_name;
	}

	void draw(int x, int y, short c = SOLID_CHAR::FULL, Texture t = Texture())
	{
		if (x >= 0 && x < this->_width && y >= 0 && y < this->_height)
		{
			this->screen_buffer[y * this->_width + x].Char.UnicodeChar = c;
			this->screen_buffer[y * this->_width + x].Attributes = t.attr;
		}
	}
	void draw(int x, int y, short c, FOREGROUND fg, BACKGROUND bg)
	{
		if (x >= 0 && x < this->_width && y >= 0 && y < this->_height)
		{
			this->screen_buffer[y * this->_width + x].Char.UnicodeChar = c;
			this->screen_buffer[y * this->_width + x].Attributes = fg | bg;
		}
	}
	void draw_attr(int x, int y, FOREGROUND fg, BACKGROUND bg)
	{
		if (x >= 0 && x < this->_width && y >= 0 && y < this->_height)
			this->screen_buffer[y * this->_width + x].Attributes = fg | bg;
	}
	void draw_char(int x, int y, short c = SOLID_CHAR::FULL)
	{
		if (x >= 0 && x < this->_width && y >= 0 && y < this->_height)
		{
			this->screen_buffer[y * this->_width + x].Char.UnicodeChar = c;
		}
	}
	void draw_string(int x, int y, std::string c, bool draw_whitespace, FOREGROUND fg = FOREGROUND::FG_WHITE, BACKGROUND bg = BACKGROUND::BG_BLACK)
	{
		adjust_tab(c);
		for (size_t i = 0; i < c.size(); i++)
		{
			if (c[i] != ' ' || draw_whitespace)
			{
				this->draw(x + i, y, c[i], Texture(fg | bg));
			}
		}
	}
	// Method returns part of the string that it could not write
	std::string draw_string_constrained(int x, int y, int max_x, std::string c, bool draw_whitespace, FOREGROUND fg = FOREGROUND::FG_WHITE, BACKGROUND bg = BACKGROUND::BG_BLACK)
	{
		adjust_tab(c);
		for (size_t i = 0; i < c.size() && x + i <= max_x; i++)
		{
			if (x + i == max_x)
			{
				return c.substr(i);
			}
			if (c[i] != ' ' || draw_whitespace)
			{
				this->draw(x + i, y, c[i], Texture(fg | bg));
			}
		}
		return "";
	}
	void draw_background(int x, int y, Texture t = Texture())
	{
		if (x >= 0 && x < this->_width && y >= 0 && y < this->_height)
		{
			this->screen_buffer[y * this->_width + x].Attributes = t.attr;
		}
	}

	void draw_rectangle(int x1, int y1, int x2, int y2, short c, Texture t = Texture())
	{
		this->correct_rectangle_coordinates(x1, y1, x2, y2);
		for (int i = x1; i <= x2; ++i)
			for (int j = y1; j <= y2; ++j)
				this->draw(i, j, c, t);
	}
	void draw_rectangle(int x1, int y1, int x2, int y2, short c, Texture border, Texture fill)
	{
		this->correct_rectangle_coordinates(x1, y1, x2, y2);
		for (int i = x1; i <= x2; ++i)
			for (int j = y1; j <= y2; ++j)
				if (i == x1 || j == y1 || i == x2 || j == y1)
					this->draw(i, j, c, border);
				else
					this->draw(i, j, c, fill);
	}

	void draw_rectangle_neg(int x1, int y1, int x2, int y2, short c, FOREGROUND fg = FOREGROUND::FG_WHITE, BACKGROUND bg = BACKGROUND::BG_BLACK)
	{
		if (x1 < 0)
			x1 = _width - x1;
		if (y1 < 0)
			y1 = _height - y1;
		if (x2 < 0)
			x2 = _width + x2;
		if (y2 < 0)
			y2 = _height + y2;
		this->draw_rectangle(x1, y1, x2, y2, c, Texture(fg | bg));
	}
};

#ifdef do_not_compile_this

void Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F)
{
	Clip(x1, y1);
	Clip(x2, y2);
	for (int x = x1; x < x2; x++)
		for (int y = y1; y < y2; y++)
			Draw(x, y, c, col);
}

void DrawString(int x, int y, std::wstring c, short col = 0x000F)
{
	for (size_t i = 0; i < c.size(); i++)
	{
		m_bufScreen[y * m_nScreenWidth + x + i].Char.UnicodeChar = c[i];
		m_bufScreen[y * m_nScreenWidth + x + i].Attributes = col;
	}
}

void DrawStringAlpha(int x, int y, std::wstring c, short col = 0x000F)
{
	for (size_t i = 0; i < c.size(); i++)
	{
		if (c[i] != L' ')
		{
			m_bufScreen[y * m_nScreenWidth + x + i].Char.UnicodeChar = c[i];
			m_bufScreen[y * m_nScreenWidth + x + i].Attributes = col;
		}
	}
}

#endif
