#pragma once

#include <Windows.h>

namespace Keypress
{

	// Taken from https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	// Alternatively enter WinUser.h file
	namespace keyup
	{

		bool check(int code)
		{
			return GetAsyncKeyState(code) & 0x0001;
		}

		bool range_pressed(int start, int finish)
		{
			for (int i = start; i <= finish; ++i)
			{
				if (check(i))
				{
					return true;
				}
			}
			return false;
		}

		bool lmouse() { return check(VK_LBUTTON); }
		bool rmouse() { return check(VK_RBUTTON); }
		bool backspace() { return check(VK_BACK); }
		bool tab() { return check(VK_TAB); }
		bool enter() { return check(VK_RETURN); }
		bool shift() { return check(VK_SHIFT); }
		bool ctrl() { return check(VK_CONTROL); }
		bool alt() { return check(VK_MENU); }
		bool caps_lock() { return check(VK_CAPITAL); }
		bool escape() { return check(VK_ESCAPE); }
		bool spacebar() { return check(VK_SPACE); }
		bool page_up() { return check(VK_PRIOR); }
		bool page_down() { return check(VK_NEXT); }
		bool end_key() { return check(VK_END); }
		bool home_key() { return check(VK_HOME); }
		bool arrow_left() { return check(VK_LEFT); }
		bool arrow_right() { return check(VK_RIGHT); }
		bool arrow_up() { return check(VK_UP); }
		bool arrow_down() { return check(VK_DOWN); }
		bool select_all() { return check(VK_SELECT); }
		bool print() { return check(VK_PRINT); }
		bool print_scr() { return check(VK_SNAPSHOT); }
		bool insert() { return check(VK_INSERT); }
		bool delete_key() { return check(VK_DELETE); }
		bool sleep_key() { return check(VK_SLEEP); }
		bool numlock() { return check(VK_NUMLOCK); }
		bool scroll() { return check(VK_SCROLL); }

		bool lshift() { return check(VK_LSHIFT); }
		bool rshift() { return check(VK_RSHIFT); }
		bool lctrl() { return check(VK_LCONTROL); }
		bool rctrl() { return check(VK_RCONTROL); }
		bool lmenu() { return check(VK_LMENU); }
		bool rmenu() { return check(VK_RMENU); }


		bool num_0() { return check(0x30); }
		bool num_1() { return check(0x31); }
		bool num_2() { return check(0x32); }
		bool num_3() { return check(0x33); }
		bool num_4() { return check(0x34); }
		bool num_5() { return check(0x35); }
		bool num_6() { return check(0x36); }
		bool num_7() { return check(0x37); }
		bool num_8() { return check(0x38); }
		bool num_9() { return check(0x39); }
		bool numpad_0() { return check(VK_NUMPAD0); }
		bool numpad_1() { return check(VK_NUMPAD1); }
		bool numpad_2() { return check(VK_NUMPAD2); }
		bool numpad_3() { return check(VK_NUMPAD3); }
		bool numpad_4() { return check(VK_NUMPAD4); }
		bool numpad_5() { return check(VK_NUMPAD5); }
		bool numpad_6() { return check(VK_NUMPAD6); }
		bool numpad_7() { return check(VK_NUMPAD7); }
		bool numpad_8() { return check(VK_NUMPAD8); }
		bool numpad_9() { return check(VK_NUMPAD9); }
		bool numpad_mul() { return check(VK_MULTIPLY); }
		bool numpad_add() { return check(VK_ADD); }
		bool numpad_sep() { return check(VK_SEPARATOR); }
		bool numpad_dec() { return check(VK_DECIMAL); }
		bool numpad_sub() { return check(VK_SUBTRACT); }
		bool numpad_div() { return check(VK_DIVIDE); }

		bool numpad_any() { return range_pressed(VK_NUMPAD0, VK_DIVIDE); }
		int number_get()
		{
			for (int i = 0; i <= 9; ++i)
			{
				if (check(VK_NUMPAD0 + i) || check(0x30 + i))
				{
					return i;
				}
			}
			return -1;
		}

		bool F1() { return check(VK_F1); }
		bool F2() { return check(VK_F2); }
		bool F3() { return check(VK_F3); }
		bool F4() { return check(VK_F4); }
		bool F5() { return check(VK_F5); }
		bool F6() { return check(VK_F6); }
		bool F7() { return check(VK_F7); }
		bool F8() { return check(VK_F8); }
		bool F9() { return check(VK_F9); }
		bool F10() { return check(VK_F10); }
		bool F11() { return check(VK_F11); }
		bool F12() { return check(VK_F12); }
		bool F13() { return check(VK_F13); }
		bool F14() { return check(VK_F14); }
		bool F15() { return check(VK_F15); }
		bool F16() { return check(VK_F16); }
		bool F17() { return check(VK_F17); }
		bool F18() { return check(VK_F18); }
		bool F19() { return check(VK_F19); }
		bool F20() { return check(VK_F20); }
		bool F21() { return check(VK_F21); }
		bool F22() { return check(VK_F22); }
		bool F23() { return check(VK_F23); }
		bool F24() { return check(VK_F24); }
		int F_get()
		{
			for (int i = 0; i <= VK_F24; ++i)
			{
				if (GetAsyncKeyState(VK_F1 + i) & 0x8000)
				{
					return i + 1;
				}
			}
			return 0;
		}

		bool letter_A() { return check(0x41); }
		bool letter_B() { return check(0x42); }
		bool letter_C() { return check(0x43); }
		bool letter_D() { return check(0x44); }
		bool letter_E() { return check(0x45); }
		bool letter_F() { return check(0x46); }
		bool letter_G() { return check(0x47); }
		bool letter_H() { return check(0x48); }
		bool letter_I() { return check(0x49); }
		bool letter_J() { return check(0x4a); }
		bool letter_K() { return check(0x4b); }
		bool letter_L() { return check(0x4c); }
		bool letter_M() { return check(0x4d); }
		bool letter_N() { return check(0x4e); }
		bool letter_O() { return check(0x4f); }
		bool letter_P() { return check(0x50); }
		bool letter_Q() { return check(0x51); }
		bool letter_R() { return check(0x52); }
		bool letter_S() { return check(0x53); }
		bool letter_T() { return check(0x54); }
		bool letter_U() { return check(0x55); }
		bool letter_V() { return check(0x56); }
		bool letter_W() { return check(0x57); }
		bool letter_X() { return check(0x58); }
		bool letter_Y() { return check(0x59); }
		bool letter_Z() { return check(0x5a); }

		bool letter_any()
		{
			unsigned short start = 0x41;
			for (unsigned short i = start; i <= 0x5a; ++i)
			{
				if (check(i))
				{
					return true;
				}
			}
			return false;
		}
		char letter_get()
		{
			unsigned short start = 0x41;
			for (unsigned short i = start; i <= 0x5a; ++i)
			{
				if (check(i))
				{
					return (char)i;
				}
			}
			return 0;
		}
	}

	namespace is_pressed
	{
		// TODO: when finished, copy is_pressed and replace 0x8000 with 0x0001
	}
}
