#pragma once

#include "Console_CI.h"
#include "Console_Cursor.h"

#include <iostream>
#include <string>
#include <vector>


class Console_CI_Manager
{
private:
	Console_CI console;
	int _w, _h;
	int msg_area_h;
	// Coordinates that are allowed for writing characters
	int x_min, x_max, y_min, y_max;

	// This value may be used to avoid unnecessarily setting the pointer (for now it is not used)
	//Console_Cursor previous_cursor;

//public:
//	int get_w() const { return _w; }
//	int get_h() const { return _h; }
//private:

	// Foreground = text color
	FOREGROUND fg_text_area, fg_wall, fg_dark_grey;
	// Background = text background
	BACKGROUND bg_text_area, bg_wall, bg_marked_ch;

public:
	Console_CI_Manager(std::string app_name = "My App") : console()
	{
		this->_w = console.get_width();
		this->_h = console.get_height();
		this->msg_area_h = 3;
		this->x_min = 1;
		this->x_max = _w - 2;
		this->y_min = 1;
		this->y_max = _h - 2;

		// Set skin
		this->fg_text_area = FOREGROUND::FG_WHITE;
		this->bg_text_area = BACKGROUND::BG_BLACK;
		this->fg_wall = FOREGROUND::FG_BLACK;
		this->bg_wall = BACKGROUND::BG_WHITE;
		this->fg_dark_grey = FOREGROUND::FG_DARK_GREY;
		this->bg_marked_ch = BACKGROUND::BG_DARK_BLUE;
		
		console.set_name(app_name);

		// Set border
		console.draw_rectangle_neg(0, 0, -1, -1, ' ', fg_wall, bg_wall);
		// Clear screen
		console.draw_rectangle_neg(1, 1, -2, -2, ' ', fg_text_area, bg_text_area);

		// Set app name in the middle of the first row
		std::string s_app_name;
		for (int i = 0; i < console.get_name().length(); ++i)
			s_app_name += (char)console.get_name()[i];
		console.draw_string(_w / 2 - s_app_name.length() / 2, 0, s_app_name, false, fg_wall, bg_wall);

		set_cursor(0, 1);
	}

	// Clears writeable area of the screen
	void clear_screen()
	{
		console.draw_rectangle_neg(1, 1, -2, -2, ' ', fg_text_area, bg_text_area);
	}

	void set_cursor(int x, int y)
	{
		console.set_cursor(x, y);
	}

	void set_lines(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end, const Console_Cursor& cursor, int x, int y, Console_Cursor mark_from = Console_Cursor::empty())
	{
		if (x < x_min || y < y_min || x > x_max || y > y_max)
			return;
		// There are no marked lines
		if (mark_from == Console_Cursor::empty())
			mark_from = cursor;

		// TODO:
		//     make mark_until and set mark_from/mark_until based on cursor and mark_from values

		clear_screen();
		int cnt = 0;
		// lines_written and chars_written is used for setting the cursor
		int lines_written = 0;
		int chars_written = 0;
		for (auto it = begin; it != end && y + cnt < y_max; ++it, ++cnt, ++lines_written)
		{
			std::string to_write;

			if (cursor == mark_from)
				to_write = console.draw_string_constrained(x, y + cnt, x_max, *it, true, fg_text_area, bg_text_area);
			else
			{
				if (cnt == mark_from.line_idx)
				{
					// Mark second half
					std::string p1, p2;
					p1 = it->substr(0, mark_from.ch_idx);
					p2 = it->substr(mark_from.ch_idx);
					to_write = console.draw_string_constrained(x, y + cnt, x_max, p1, true, fg_text_area, bg_text_area);
					to_write = console.draw_string_constrained(x + p1.length(), y + cnt, x_max, p2, true, fg_text_area, bg_marked_ch);
				}
				else if (cnt == cursor.line_idx)
				{
					// Mark first half
					std::string p1, p2;
					p1 = it->substr(0, cursor.ch_idx);
					p2 = it->substr(cursor.ch_idx);
					to_write = console.draw_string_constrained(x, y + cnt, x_max, p1, true, fg_text_area, bg_marked_ch);
					to_write = console.draw_string_constrained(x + p1.length(), y + cnt, x_max, p2, true, fg_text_area, bg_text_area);
				}
				else
				{
					// Mark entire line
					to_write = console.draw_string_constrained(x, y + cnt, x_max, *it, true, fg_text_area, bg_marked_ch);
				}
			}

			chars_written = (*it).length() - to_write.length();
			// TODO: take tabs in account
			// Set cursor if it matches line
			if (lines_written == cursor.line_idx)
			{
				// If the entire line fits in one line of the screen
				// Else (buffer line spans several screen lines)
				//     calculate proper (x, y) - UNFINISHED
				if (chars_written == it->length())
				{
					int x_pos = 0;
					for (int i = 0; i < it->length() && i < cursor.ch_idx; ++i)
						if ((*it)[i] == '\t')
							x_pos += 4 - (x_pos % 4);
						else
							++x_pos;
					set_cursor(x_pos + 1, y + cnt);
				}
				else;
			}
		}
	}

	int get_writeable_height() const
	{
		return _h - 2;
	}

	int get_characters_per_line() const
	{
		return _w - 2;
	}

	void show()
	{
		console.print();
	}

};
