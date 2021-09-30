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

	// Index as shown on screen (each char is 1, but '\t' is 1-4 spaces)
	int adjusted_idx_until(std::string s, int ch_boundary)
	{
		if (s.length() == 0)
			return 0;
		int scr_idx = 0;
		for (int i = 0; i < s.length() && i < ch_boundary; ++i)
			if (s[i] == '\t')
				scr_idx += 4 - i % 4;
			else
				++scr_idx;
		return scr_idx;
	}

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

		Console_Cursor mark_to = cursor;
		Console_Cursor::set_min_max(mark_from, mark_to);

		clear_screen();
		int cnt = 0;
		// lines_written and chars_written is used for setting the cursor
		int lines_written = 0;
		int chars_written = 0;
		for (auto it = begin; it != end && y + cnt < y_max; ++it, ++cnt, ++lines_written)
		{
			std::string to_write;
			to_write = console.draw_string_constrained(x, y + cnt, x_max, *it, true, fg_text_area, bg_text_area);

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
		// Mark lines
		if (mark_from != mark_to)
		{
			console.draw_attr(
				adjusted_idx_until(*(begin + mark_from.line_idx), mark_from.ch_idx) + 1,
				mark_from.line_idx + 1, fg_text_area, bg_marked_ch
			);
			console.draw_attr(
				adjusted_idx_until(*(begin + mark_to.line_idx), mark_to.ch_idx) + 1,
				mark_to.line_idx + 1, fg_text_area, bg_marked_ch
			);
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
