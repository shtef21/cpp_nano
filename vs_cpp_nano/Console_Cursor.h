#pragma once

struct Console_Cursor
{
	// line_idx = ptr_y
	int line_idx;
	// ch_idx = ptr_x
	int ch_idx;
	Console_Cursor(int ptr_x, int ptr_y) : ch_idx(ptr_x), line_idx(ptr_y) {}
	void set_values(int ptr_x, int ptr_y) { ch_idx = ptr_x; line_idx = ptr_y; }
	bool operator==(Console_Cursor& b) { return line_idx == b.line_idx && ch_idx == b.ch_idx; }
	bool operator!=(Console_Cursor& b) { return !(*this == b); }
};
