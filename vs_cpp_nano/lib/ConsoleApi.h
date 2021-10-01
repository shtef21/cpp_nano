#pragma once

#include <Windows.h>

class Console
{
private:
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND hwnd;

public:

	Console()
	{
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		hwnd = GetConsoleWindow();
	}

	int get_width()
	{
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}

	int get_height()
	{
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}

	void set_size(int width, int height)
	{
		MoveWindow(hwnd, 100, 100, width, height, TRUE);
	}

} Console;
