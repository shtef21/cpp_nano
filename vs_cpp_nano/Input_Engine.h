#pragma once
#ifndef NANO_CPP_INPUT_ENGINE
#define NANO_CPP_INPUT_ENGINE

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <Windows.h>

#include "Input_Engine.h"
#include "Console_Cursor.h"
// ceil()
#include <math.h>

using std::string;
typedef unsigned char uchar;


/* PAGINATION

    the screen can fit at maximum HEIGHT_WRITEABLE lines
    therefore buffer consists of BUFFER_SIZE / HEIGHT_WRITEABLE + 1 pages
    to get current page

    Example:

    buffer = {
        "foo",
        "bar",
        "row3",
        "",
        "hello!"
    }
    screen:
    XXXXXXXXXX
    X        X
    X        X
    XXXXXXXXXX
    all pages:
    XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX
    Xfoo     X Xrow3    X Xhello!  X
    Xbar     X X        X X        X
    XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX

    writeable height = 2
    buffer size = 5
    ptr_y = 0, 1... 2, 3... 4, 5
    y/w_h = 0, 0... 1, 1... 2, 2

    curr_page_start_idx = writeable_height * (ptr_y / writeable_height)
    (programming != math so writeable_height cannot be crossed out)
*/

/*
GetAsyncKeyState(code)

code...
VK_LSHIFT	    Left-shift key.
VK_RSHIFT	    Right-shift key.
VK_LCONTROL	    Left-control key.
VK_RCONTROL	    Right-control key.
VK_LMENU	    Left-menu key.
VK_RMENU	    Right-menu key.

if (GetAsyncKeyState(code) & 0x8000)
    // most significant bit set = currently pressed
if (GetAsyncKeyState(code) & 0x0001)
    // least significant bit set = pressed since last time
*/

namespace NANO
{
    struct CH
    {
    public:
        // Single characters
        static const uchar CH_ESC = 27, CH_ENTER = 13, CH_DELETE = 8, CH_TAB = '\t';
        // Preceded by code 224:
        static const uchar CH_REVERSE_DEL = 83, CH_ARROW_UP = 72, CH_ARROW_DOWN = 80, CH_ARROW_LEFT = 75, CH_ARROW_RIGHT = 77, CH_PAGE_UP = 73, CH_PAGE_DOWN = 81;
        static bool is_control(int ch_code);
        static bool is_printable(int ch_code);
        static bool is_arrow(int ch_code);
        static bool _enter()
        {
            return GetAsyncKeyState(VK_RETURN) & 0x8000;
        }
        static bool _lctrl()
        {
            return GetAsyncKeyState(VK_LCONTROL) & 0x8000;
        }
    };
}

class Input_Engine
{
private:
    std::vector<string>& buffer_ref;
    // Coordinates (indexes) of buffer
    int ptr_x, ptr_y;
    int prev_char;
    int lines_per_page;
    int characters_per_line;

    /*
        Issue with moving cursor line up or down (char '_' represents cursor, [tab] is '\t' char):
            "ab_cd" cursor move down to "g" results in "g_"
            "ab_cd" cursor move down to "zasdfkljh" results in "za_sdfkljh"
            but
            "ab[tab]cd_ef" moving down to "ghijklmn" should result in...
                ... "ghijkl_mn", but results in "ghijk_lmn" because '\t' is one char but on screen...
                ... it may be shown as 1 to four ' ' characters

        Because of that, it is necessary to calculate various virtual lengths to get proper cursor position
    */

    int calculate_virtual_length(int line_idx, int ch_idx_bound = -1);
    int predict_ch_idx(int line_idx, int virtual_len_bound);

    bool text_marked_flag;
    Console_Cursor marked_start_pos;

public:
    Input_Engine() = delete;
    Input_Engine(std::vector<string>& buffer_ref, int _lpg, int _cpl);

    std::vector<string>::iterator paginated_start();
    std::vector<string>::iterator paginated_end();

    inline bool is_text_marked()
    {
        return text_marked_flag;
    }
    inline Console_Cursor get_marked_start_pos()
    {
        return marked_start_pos;
    }

    inline int get_x_idx();
    inline int get_y_idx();
    inline int line_stretch(string& s)
    {
        return s.length() / characters_per_line + 1;
    }

    int get_and_process_input();

    inline void debug_pointer();
    inline void pointer_left();
    inline void pointer_right();
    inline void pointer_up();
    inline void pointer_down();

    inline int get_current_page_number();
    inline int get_total_pages_number();
    inline void page_up();
    inline void page_down();

    inline void add_char(int ch);
    inline void delete_char();
    inline void reverse_delete_char();
    void process_newline();
    // inline void add_string(const string& s);
    inline void add_new_line(string initial_str = string());
};

// ---------------------------------- IMPLEMENTATION ---------------------------------- //

Input_Engine::Input_Engine(std::vector<string>& buffer_ref, int _lpg, int _cpl) : buffer_ref(buffer_ref), ptr_x(0), ptr_y(0), lines_per_page(_lpg), characters_per_line(_cpl),
marked_start_pos(0, 0)
{
    text_marked_flag = false;
}

std::vector<string>::iterator Input_Engine::paginated_start()
{
    return buffer_ref.begin() + ((this->get_current_page_number() - 1) * this->lines_per_page);
}
std::vector<string>::iterator Input_Engine::paginated_end()
{
    // if this is not last page, return next page start, otherwise return buffer end
    int current_page = this->get_current_page_number();
    if (current_page < this->get_total_pages_number())
        return this->buffer_ref.begin() + (current_page * this->lines_per_page);
    else
        return this->buffer_ref.end();
}

int Input_Engine::get_and_process_input()
{
    // TODO: add way to print debug info on Console_Manager_CI.h
    //std::cout << "(x, y) = (" << ptr_x << ", " << ptr_y << ")\n";
    // TODO: add way to print debug info on Console_Manager_CI.h
    //std::cout << "(vx, vy) = (" << this->get_virtual_x_idx() << ", " << this->get_virtual_y_idx() << ")\n";
    //if (ptr_x < buffer_ref[ptr_y].length())
        // TODO: add way to print debug info on Console_Manager_CI.h
        //std::cout << "[" << ptr_y << "][" << ptr_x << "]=\'" << buffer_ref[ptr_y][ptr_x] << "\'\n";

    int ch = _getch();
    if (ch == 224)
    {
        switch ((ch = _getch()))
        {
        case NANO::CH::CH_ARROW_UP:
            pointer_up();
            break;
        case NANO::CH::CH_ARROW_DOWN:
            pointer_down();
            break;
        case NANO::CH::CH_ARROW_LEFT:
            pointer_left();
            break;
        case NANO::CH::CH_ARROW_RIGHT:
            pointer_right();
            break;
        case NANO::CH::CH_REVERSE_DEL:
            reverse_delete_char();
            break;
        case NANO::CH::CH_PAGE_UP:
            page_up();
            break;
        case NANO::CH::CH_PAGE_DOWN:
            page_down();
            break;
        default:
            // TODO: add way to print debug info on Console_Manager_CI.h
            //std::cout << "Unrecognised or forbidden control character.\n";
            break;
        }
    }
    else if (NANO::CH::is_printable(ch) || ch == NANO::CH::CH_TAB)
    {
        add_char(ch);
        this->prev_char = ch;
    }
    else
    {
        if (NANO::CH::_enter() && NANO::CH::_lctrl())
        {
            // Start/stop marking text
            this->text_marked_flag = !text_marked_flag;
            // Store position in any case
            this->marked_start_pos = Console_Cursor(ptr_x, ptr_y);
        }
        else
            switch (ch)
            {
                // case NANO::CH::CH_TAB:
                //     // add_string("    ");
                //     break;
            case NANO::CH::CH_ESC:
                break;
            case NANO::CH::CH_ENTER:
                this->process_newline();
                break;
            case NANO::CH::CH_DELETE:
                delete_char();
                break;
            default:
                break;
            }
    }
    return ch;
}

// Calculate virtual length (tabs included) of string (until the end, or until ch_idx_bound)
int Input_Engine::calculate_virtual_length(int line_idx, int ch_idx_bound)
{
    if (ch_idx_bound == -1)
        ch_idx_bound = buffer_ref[line_idx].length();
    int len = 0;
    for (int i = 0; i < this->buffer_ref[line_idx].length() && i < ch_idx_bound; ++i)
        if (buffer_ref[line_idx][i] == '\t') len += 4 - len % 4;
        else ++len;
    return len;
}
// Calculate which char index is needed to surpass or equal virtual_len_bound (result is line_idx virtual length if virtual_len_bound is too long
int Input_Engine::predict_ch_idx(int line_idx, int virtual_len_bound)
{
    if (virtual_len_bound == 0)
        return 0;
    int line_virt_len = 0;
    for (int i = 0; i < buffer_ref[line_idx].length(); ++i)
        if (line_virt_len >= virtual_len_bound)
            return i;
        else if (buffer_ref[line_idx][i] == '\t') line_virt_len += 4 - line_virt_len % 4;
        else ++line_virt_len;
    return buffer_ref[line_idx].length();
}

// NEW: return index at which ptr_x points to
inline int Input_Engine::get_x_idx()
{
    // return raw ptr_x, as it will be displayed using Console_CI_Manager.h
    return this->ptr_x;
}

// index of line that ptr_y points to
inline int Input_Engine::get_y_idx()
{
    return this->ptr_y;
}

// Check if pointer need be changed
inline void Input_Engine::debug_pointer()
{
    bool inform_of_error = true;
    if (ptr_y < 0)
    {
        ptr_y = ptr_x = 0;
    }
    else if (ptr_y >= this->buffer_ref.size())
    {
        ptr_y = this->buffer_ref.size() - 1;
        ptr_x = this->buffer_ref[ptr_y].length();
    }
    else if (ptr_x < 0)
    {
        ptr_x = 0;
    }
    else if (ptr_x > this->buffer_ref[ptr_y].length())
    {
        ptr_x = this->buffer_ref[ptr_y].length();
    }
    else
    {
        // Else it's okay
        inform_of_error = false;
    }

    if (inform_of_error)
    {
        // TODO: add way to print debug info on Console_Manager_CI.h
        //std::cout << "\nThere has been an error with the pointer.\nPress any key to continue...";
        _getch();
    }
}
inline void Input_Engine::pointer_left()
{
    // if pointer at top left corner
    //     move to end of last line
    // else if line beginning
    //     move to previous line end
    // else
    //     move to previous character
    if (ptr_y == 0 && ptr_x == 0)
    {
        ptr_y = this->buffer_ref.size() - 1;
        ptr_x = this->buffer_ref[ptr_y].length();
    }
    else if (ptr_x == 0)
    {
        --ptr_y;
        ptr_x = this->buffer_ref[ptr_y].length();
    }
    else --ptr_x;
}
inline void Input_Engine::pointer_right()
{

    // if pointer at last character + 1
    //     move to first position in buffer
    // else if pointer at last character of current line
    //     move to start of the next line
    // else
    //     move to next character
    if (ptr_y == buffer_ref.size() - 1 && ptr_x == this->buffer_ref[ptr_y].length())
        ptr_y = ptr_x = 0;
    else if (ptr_x == buffer_ref[ptr_y].length())
    {
        ++ptr_y;
        ptr_x = 0;
    }
    else ++ptr_x;
}
inline void Input_Engine::pointer_up()
{
    // If this is the only line, do nothing
    if (this->buffer_ref.size() <= 1)
        return;
    int curr_virt_len = calculate_virtual_length(ptr_y, ptr_x);

    // if current line is first line
    //     pointer need be set to last line (with conditions below)
    if (ptr_y == 0)
        ptr_y = this->buffer_ref.size();
    // ptr_x values depend on \t characters and on length of previous line
    ptr_x = predict_ch_idx(ptr_y - 1, curr_virt_len);
    --ptr_y;
}
inline void Input_Engine::pointer_down()
{
    // if there is only one line in buffer, do nothing
    if (this->buffer_ref.size() <= 1)
        return;
    int curr_virt_len = calculate_virtual_length(ptr_y, ptr_x);

    // if current line is last line
    //     ptr_y need be set to the first line
    //     (at first set to -1 and leave it for statements below)
    if (ptr_y == this->buffer_ref.size() - 1)
        ptr_y = -1;
    // ptr_x values depend on \t characters and on length of previous line
    ptr_x = predict_ch_idx(ptr_y + 1, curr_virt_len);
    ++ptr_y;
}

inline int Input_Engine::get_current_page_number()
{
    return this->ptr_y / this->lines_per_page + 1;
}
inline int Input_Engine::get_total_pages_number()
{
    return this->buffer_ref.size() / this->lines_per_page + 1;
}
inline void Input_Engine::page_up()
{
    if (this->get_current_page_number() > 1)
    {
        ptr_y -= this->lines_per_page;
        if (ptr_x > this->buffer_ref[ptr_y].length())
        {
            ptr_x = this->buffer_ref[ptr_y].length();
        }
    }
}
inline void Input_Engine::page_down()
{
    if (this->get_current_page_number() < this->get_total_pages_number())
    {
        ptr_y += this->lines_per_page;
    }
}

inline void Input_Engine::add_char(int ch)
{
    buffer_ref[ptr_y].reserve(int(buffer_ref[ptr_y].length() * 1.2) + 1);
    if (ptr_x >= buffer_ref[ptr_y].length())
        buffer_ref[ptr_y] += char(ch);
    else
        buffer_ref[ptr_y].insert(ptr_x, 1, char(ch));
    ++ptr_x;
}

// Delete character at buffer[ptr_y][ptr_x]
inline void Input_Engine::delete_char()
{
    // if pointer is at first character of first line
    // else if pointer is at first character of current line
    // else
    if (ptr_y == 0 && ptr_x == 0);
    else if (ptr_x == 0)
    {
        ptr_x = this->buffer_ref[ptr_y - 1].length();
        this->buffer_ref[ptr_y - 1] += this->buffer_ref[ptr_y];
        this->buffer_ref.erase(this->buffer_ref.begin() + ptr_y);
        --ptr_y;
    }
    else
    {
        this->buffer_ref[ptr_y].erase(ptr_x - 1, 1);
        --ptr_x;
    }
}

inline void Input_Engine::reverse_delete_char()
{
    // if pointer is at last character of last line
    // else if pointer is at last character + 1 of current line
    // else
    if (ptr_y == this->buffer_ref.size() - 1 && ptr_x == this->buffer_ref[ptr_y].length());
    else if (ptr_x == this->buffer_ref[ptr_y].length())
    {
        this->buffer_ref[ptr_y] += this->buffer_ref[ptr_y + 1];
        this->buffer_ref.erase(this->buffer_ref.begin() + ptr_y + 1);
    }
    else
    {
        this->buffer_ref[ptr_y].erase(ptr_x, 1);
    }
}

inline void Input_Engine::process_newline()
{
    if (ptr_x == 0)
    {
        this->add_new_line(this->buffer_ref[ptr_y]);
        buffer_ref[ptr_y - 1] = string();
    }
    else if (ptr_x >= this->buffer_ref[ptr_y].length())
    {
        this->add_new_line();
    }
    else
    {
        string p1 = this->buffer_ref[ptr_y].substr(0, ptr_x);
        string p2 = this->buffer_ref[ptr_y].substr(ptr_x);
        this->buffer_ref[ptr_y] = p1;
        this->add_new_line(p2);
    }
}

inline void Input_Engine::add_new_line(string initial_str)
{
    buffer_ref.reserve(int((buffer_ref.size() + initial_str.length()) * 1.2) + 1);
    if (ptr_y >= buffer_ref.size())
        buffer_ref.push_back(initial_str);
    else
        buffer_ref.insert(buffer_ref.begin() + ptr_y + 1, initial_str);
    ++ptr_y;
    ptr_x = 0;
}

bool NANO::CH::is_control(int ch_code)
{
    switch (ch_code)
    {
    case 8:
        // BACKSPACE
    case 9:
        // HORIZONTAL TAB
    case 10:
        // ENTER
    case 27:
        // ESCAPE
    case 224:
        return true;
        break;
    }
    return false;
}
// '\t' not included
bool NANO::CH::is_printable(int ch_code)
{
    // Printable ASCII: ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ ` a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~
    return ch_code > 31 && ch_code < 127;
}

bool NANO::CH::is_arrow(int ch_code)
{
    switch (ch_code)
    {
    case CH_ARROW_UP:
    case CH_ARROW_DOWN:
    case CH_ARROW_LEFT:
    case CH_ARROW_RIGHT:
        return true;
        break;
    default:
        return false;
    }
}

#endif
