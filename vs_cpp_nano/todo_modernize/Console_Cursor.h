#pragma once

struct Console_Cursor
{
	// line_idx = ptr_y
	int line_idx;
	// ch_idx = ptr_x
	int ch_idx;
	Console_Cursor(int ptr_x, int ptr_y) : ch_idx(ptr_x), line_idx(ptr_y) {}
	void set_values(int ptr_x, int ptr_y) { ch_idx = ptr_x; line_idx = ptr_y; }
	bool operator==(const Console_Cursor& b) const { return line_idx == b.line_idx && ch_idx == b.ch_idx; }
	bool operator!=(const Console_Cursor& b) const { return !(*this == b); }
	bool operator>(const Console_Cursor& b) const
	{
		if (line_idx > b.line_idx)
			return true;
		else if (line_idx < b.line_idx)
			return false;
		else if (ch_idx > b.ch_idx)
			return true;
		else if (ch_idx <= b.ch_idx)
			return false;
	}
	bool operator<(const Console_Cursor& b) const { return b > *this; }
	bool operator>=(const Console_Cursor& b) const { return *this > b || b == *this; }
	bool operator<=(const Console_Cursor& b) const { return *this < b || b == *this; }
	static Console_Cursor empty() { return { 0x8000, 0x8000 }; }
	static void set_min_max(Console_Cursor& min, Console_Cursor& max)
	{
		if (min > max)
		{
			Console_Cursor temp = min;
			min = max;
			max = temp;
		}
	}
};

