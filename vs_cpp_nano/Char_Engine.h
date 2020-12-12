#pragma once

#include <Windows.h>

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate
// https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

// https://docs.microsoft.com/en-gb/windows/win32/api/winuser/nf-winuser-getkeyboardstate

struct Char_Engine
{
	//static PBYTE lpKeyState;

	bool lshift() { GetAsyncKeyState(VK_LSHIFT) & 0x8000; }
	bool rshift() { GetAsyncKeyState(VK_RSHIFT) & 0x8000; }
	bool lcontrol() { GetAsyncKeyState(VK_LCONTROL) & 0x8000; }
	bool rcontrol() { GetAsyncKeyState(VK_RCONTROL) & 0x8000; }
	bool lmenu() { GetAsyncKeyState(VK_LMENU) & 0x8000; }
	bool rmenu() { GetAsyncKeyState(VK_RMENU) & 0x8000; }
};
