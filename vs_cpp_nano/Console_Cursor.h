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
	static Console_Cursor empty() { return { 0x8000, 0x8000 }; }
};

