#pragma once

#include <Windows.h>

namespace Keypress
{
	// Taken from https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	// Alternatively enter WinUser.h file
	namespace is_pressed
	{
		bool lmouse() { return GetAsyncKeyState(VK_LBUTTON) & 0x8000; }
		bool rmouse() { return GetAsyncKeyState(VK_RBUTTON) & 0x8000; }
		bool backspace() { return GetAsyncKeyState(VK_BACK) & 0x8000; }
		bool tab() { return GetAsyncKeyState(VK_TAB) & 0x8000; }
		bool enter() { return GetAsyncKeyState(VK_RETURN) & 0x8000; }
		bool shift() { return GetAsyncKeyState(VK_SHIFT) & 0x8000; }
		bool ctrl() { return GetAsyncKeyState(VK_CONTROL) & 0x8000; }
		bool alt() { return GetAsyncKeyState(VK_MENU) & 0x8000; }
		bool caps_lock() { return GetAsyncKeyState(VK_CAPITAL) & 0x8000; }
		bool escape() { return GetAsyncKeyState(VK_ESCAPE) & 0x8000; }
		bool spacebar() { return GetAsyncKeyState(VK_SPACE) & 0x8000; }
		bool page_up() { return GetAsyncKeyState(VK_PRIOR) & 0x8000; }
		bool page_down() { return GetAsyncKeyState(VK_NEXT) & 0x8000; }
		bool end_key() { return GetAsyncKeyState(VK_END) & 0x8000; }
		bool home_key() { return GetAsyncKeyState(VK_HOME) & 0x8000; }
		bool arrow_left() { return GetAsyncKeyState(VK_LEFT) & 0x8000; }
		bool arrow_right() { return GetAsyncKeyState(VK_RIGHT) & 0x8000; }
		bool arrow_up() { return GetAsyncKeyState(VK_UP) & 0x8000; }
		bool arrow_down() { return GetAsyncKeyState(VK_DOWN) & 0x8000; }
		bool select_all() { return GetAsyncKeyState(VK_SELECT) & 0x8000; }
		bool print() { return GetAsyncKeyState(VK_PRINT) & 0x8000; }
		bool print_scr() { return GetAsyncKeyState(VK_SNAPSHOT) & 0x8000; }
		bool insert() { return GetAsyncKeyState(VK_INSERT) & 0x8000; }
		bool delete_key() { return GetAsyncKeyState(VK_DELETE) & 0x8000; }

		bool num_0() { return GetAsyncKeyState(0x30) & 0x8000; }
		bool num_1() { return GetAsyncKeyState(0x31) & 0x8000; }
		bool num_2() { return GetAsyncKeyState(0x32) & 0x8000; }
		bool num_3() { return GetAsyncKeyState(0x33) & 0x8000; }
		bool num_4() { return GetAsyncKeyState(0x34) & 0x8000; }
		bool num_5() { return GetAsyncKeyState(0x35) & 0x8000; }
		bool num_6() { return GetAsyncKeyState(0x36) & 0x8000; }
		bool num_7() { return GetAsyncKeyState(0x37) & 0x8000; }
		bool num_8() { return GetAsyncKeyState(0x38) & 0x8000; }
		bool num_9() { return GetAsyncKeyState(0x39) & 0x8000; }
		bool numpad_0() { return GetAsyncKeyState(VK_NUMPAD0) & 0x8000; }
		bool numpad_1() { return GetAsyncKeyState(VK_NUMPAD1) & 0x8000; }
		bool numpad_2() { return GetAsyncKeyState(VK_NUMPAD2) & 0x8000; }
		bool numpad_3() { return GetAsyncKeyState(VK_NUMPAD3) & 0x8000; }
		bool numpad_4() { return GetAsyncKeyState(VK_NUMPAD4) & 0x8000; }
		bool numpad_5() { return GetAsyncKeyState(VK_NUMPAD5) & 0x8000; }
		bool numpad_6() { return GetAsyncKeyState(VK_NUMPAD6) & 0x8000; }
		bool numpad_7() { return GetAsyncKeyState(VK_NUMPAD7) & 0x8000; }
		bool numpad_8() { return GetAsyncKeyState(VK_NUMPAD8) & 0x8000; }
		bool numpad_9() { return GetAsyncKeyState(VK_NUMPAD9) & 0x8000; }
		bool numpad_mul() { return GetAsyncKeyState(VK_MULTIPLY) & 0x8000; }
		bool numpad_add() { return GetAsyncKeyState(VK_ADD) & 0x8000; }
		bool numpad_sub() { return GetAsyncKeyState(VK_SUBTRACT) & 0x8000; }
		bool numpad_div() { return GetAsyncKeyState(VK_DIVIDE) & 0x8000; }
		bool F1() { return GetAsyncKeyState(VK_F1) & 0x8000; }
		bool F2() { return GetAsyncKeyState(VK_F2) & 0x8000; }
		bool F3() { return GetAsyncKeyState(VK_F3) & 0x8000; }
		bool F4() { return GetAsyncKeyState(VK_F4) & 0x8000; }
		bool F5() { return GetAsyncKeyState(VK_F5) & 0x8000; }
		bool F6() { return GetAsyncKeyState(VK_F6) & 0x8000; }
		bool F7() { return GetAsyncKeyState(VK_F7) & 0x8000; }
		bool F8() { return GetAsyncKeyState(VK_F8) & 0x8000; }
		bool F9() { return GetAsyncKeyState(VK_F9) & 0x8000; }
		bool F10() { return GetAsyncKeyState(VK_F10) & 0x8000; }
		bool F11() { return GetAsyncKeyState(VK_F11) & 0x8000; }
		bool F12() { return GetAsyncKeyState(VK_F12) & 0x8000; }
		bool F13() { return GetAsyncKeyState(VK_F13) & 0x8000; }
		bool F14() { return GetAsyncKeyState(VK_F14) & 0x8000; }
		bool F15() { return GetAsyncKeyState(VK_F15) & 0x8000; }
		bool F16() { return GetAsyncKeyState(VK_F16) & 0x8000; }
		bool F17() { return GetAsyncKeyState(VK_F17) & 0x8000; }
		bool F18() { return GetAsyncKeyState(VK_F18) & 0x8000; }
		bool F19() { return GetAsyncKeyState(VK_F19) & 0x8000; }
		bool F20() { return GetAsyncKeyState(VK_F20) & 0x8000; }
		bool F21() { return GetAsyncKeyState(VK_F21) & 0x8000; }
		bool F22() { return GetAsyncKeyState(VK_F22) & 0x8000; }
		bool F23() { return GetAsyncKeyState(VK_F23) & 0x8000; }
		bool F24() { return GetAsyncKeyState(VK_F24) & 0x8000; }
		
		bool lshift() { return GetAsyncKeyState(VK_LSHIFT) & 0x8000; }
		bool rshift() { return GetAsyncKeyState(VK_RSHIFT) & 0x8000; }
		bool lcontrol() { return GetAsyncKeyState(VK_LCONTROL) & 0x8000; }
		bool rcontrol() { return GetAsyncKeyState(VK_RCONTROL) & 0x8000; }
		bool lmenu() { return GetAsyncKeyState(VK_LMENU) & 0x8000; }
		bool rmenu() { return GetAsyncKeyState(VK_RMENU) & 0x8000; }
	}

	namespace keyup
	{
		bool lmouse() { return GetAsyncKeyState(VK_LBUTTON) & 0x0001; }
		bool rmouse() { return GetAsyncKeyState(VK_RBUTTON) & 0x0001; }
		bool backspace() { return GetAsyncKeyState(VK_BACK) & 0x0001; }
		bool tab() { return GetAsyncKeyState(VK_TAB) & 0x0001; }
		bool enter() { return GetAsyncKeyState(VK_RETURN) & 0x0001; }
		bool shift() { return GetAsyncKeyState(VK_SHIFT) & 0x0001; }
		bool ctrl() { return GetAsyncKeyState(VK_CONTROL) & 0x0001; }
		bool alt() { return GetAsyncKeyState(VK_MENU) & 0x0001; }
		bool caps_lock() { return GetAsyncKeyState(VK_CAPITAL) & 0x0001; }
		bool escape() { return GetAsyncKeyState(VK_ESCAPE) & 0x0001; }
		bool spacebar() { return GetAsyncKeyState(VK_SPACE) & 0x0001; }
		bool page_up() { return GetAsyncKeyState(VK_PRIOR) & 0x0001; }
		bool page_down() { return GetAsyncKeyState(VK_NEXT) & 0x0001; }
		bool end_key() { return GetAsyncKeyState(VK_END) & 0x0001; }
		bool home_key() { return GetAsyncKeyState(VK_HOME) & 0x0001; }
		bool arrow_left() { return GetAsyncKeyState(VK_LEFT) & 0x0001; }
		bool arrow_right() { return GetAsyncKeyState(VK_RIGHT) & 0x0001; }
		bool arrow_up() { return GetAsyncKeyState(VK_UP) & 0x0001; }
		bool arrow_down() { return GetAsyncKeyState(VK_DOWN) & 0x0001; }
		bool select_all() { return GetAsyncKeyState(VK_SELECT) & 0x0001; }
		bool print() { return GetAsyncKeyState(VK_PRINT) & 0x0001; }
		bool print_scr() { return GetAsyncKeyState(VK_SNAPSHOT) & 0x0001; }
		bool insert() { return GetAsyncKeyState(VK_INSERT) & 0x0001; }
		bool delete_key() { return GetAsyncKeyState(VK_DELETE) & 0x0001; }

		bool num_0() { return GetAsyncKeyState(0x30) & 0x0001; }
		bool num_1() { return GetAsyncKeyState(0x31) & 0x0001; }
		bool num_2() { return GetAsyncKeyState(0x32) & 0x0001; }
		bool num_3() { return GetAsyncKeyState(0x33) & 0x0001; }
		bool num_4() { return GetAsyncKeyState(0x34) & 0x0001; }
		bool num_5() { return GetAsyncKeyState(0x35) & 0x0001; }
		bool num_6() { return GetAsyncKeyState(0x36) & 0x0001; }
		bool num_7() { return GetAsyncKeyState(0x37) & 0x0001; }
		bool num_8() { return GetAsyncKeyState(0x38) & 0x0001; }
		bool num_9() { return GetAsyncKeyState(0x39) & 0x0001; }
		bool numpad_0() { return GetAsyncKeyState(VK_NUMPAD0) & 0x0001; }
		bool numpad_1() { return GetAsyncKeyState(VK_NUMPAD1) & 0x0001; }
		bool numpad_2() { return GetAsyncKeyState(VK_NUMPAD2) & 0x0001; }
		bool numpad_3() { return GetAsyncKeyState(VK_NUMPAD3) & 0x0001; }
		bool numpad_4() { return GetAsyncKeyState(VK_NUMPAD4) & 0x0001; }
		bool numpad_5() { return GetAsyncKeyState(VK_NUMPAD5) & 0x0001; }
		bool numpad_6() { return GetAsyncKeyState(VK_NUMPAD6) & 0x0001; }
		bool numpad_7() { return GetAsyncKeyState(VK_NUMPAD7) & 0x0001; }
		bool numpad_8() { return GetAsyncKeyState(VK_NUMPAD8) & 0x0001; }
		bool numpad_9() { return GetAsyncKeyState(VK_NUMPAD9) & 0x0001; }
		bool numpad_mul() { return GetAsyncKeyState(VK_MULTIPLY) & 0x0001; }
		bool numpad_add() { return GetAsyncKeyState(VK_ADD) & 0x0001; }
		bool numpad_sub() { return GetAsyncKeyState(VK_SUBTRACT) & 0x0001; }
		bool numpad_div() { return GetAsyncKeyState(VK_DIVIDE) & 0x0001; }
		bool F1() { return GetAsyncKeyState(VK_F1) & 0x0001; }
		bool F2() { return GetAsyncKeyState(VK_F2) & 0x0001; }
		bool F3() { return GetAsyncKeyState(VK_F3) & 0x0001; }
		bool F4() { return GetAsyncKeyState(VK_F4) & 0x0001; }
		bool F5() { return GetAsyncKeyState(VK_F5) & 0x0001; }
		bool F6() { return GetAsyncKeyState(VK_F6) & 0x0001; }
		bool F7() { return GetAsyncKeyState(VK_F7) & 0x0001; }
		bool F8() { return GetAsyncKeyState(VK_F8) & 0x0001; }
		bool F9() { return GetAsyncKeyState(VK_F9) & 0x0001; }
		bool F10() { return GetAsyncKeyState(VK_F10) & 0x0001; }
		bool F11() { return GetAsyncKeyState(VK_F11) & 0x0001; }
		bool F12() { return GetAsyncKeyState(VK_F12) & 0x0001; }
		bool F13() { return GetAsyncKeyState(VK_F13) & 0x0001; }
		bool F14() { return GetAsyncKeyState(VK_F14) & 0x0001; }
		bool F15() { return GetAsyncKeyState(VK_F15) & 0x0001; }
		bool F16() { return GetAsyncKeyState(VK_F16) & 0x0001; }
		bool F17() { return GetAsyncKeyState(VK_F17) & 0x0001; }
		bool F18() { return GetAsyncKeyState(VK_F18) & 0x0001; }
		bool F19() { return GetAsyncKeyState(VK_F19) & 0x0001; }
		bool F20() { return GetAsyncKeyState(VK_F20) & 0x0001; }
		bool F21() { return GetAsyncKeyState(VK_F21) & 0x0001; }
		bool F22() { return GetAsyncKeyState(VK_F22) & 0x0001; }
		bool F23() { return GetAsyncKeyState(VK_F23) & 0x0001; }
		bool F24() { return GetAsyncKeyState(VK_F24) & 0x0001; }

		bool lshift() { return GetAsyncKeyState(VK_LSHIFT) & 0x0001; }
		bool rshift() { return GetAsyncKeyState(VK_RSHIFT) & 0x0001; }
		bool lcontrol() { return GetAsyncKeyState(VK_LCONTROL) & 0x0001; }
		bool rcontrol() { return GetAsyncKeyState(VK_RCONTROL) & 0x0001; }
		bool lmenu() { return GetAsyncKeyState(VK_LMENU) & 0x0001; }
		bool rmenu() { return GetAsyncKeyState(VK_RMENU) & 0x0001; }
	}
}
