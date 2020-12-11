#pragma once
#ifndef NANO_CPP_MAIN
#define NANO_CPP_MAIN

#ifdef _WIN32
#define NANO_CPP_MAIN_LINE_FEED_TEXT "\n\r"
#elif __linux__
#define NANO_CPP_MAIN_LINE_FEED_TEXT "\n"
#endif

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <stdio.h>
#include "Console_CI_Manager.h"
#include "Input_Engine.h"
#include "Console_Cursor.h"
#include "curr_dir.h"

using std::string;

// Helper functions 
namespace NANO
{
    namespace Buff
    {
        // Put string to vec[y][x] 
        bool put(std::vector<string>& b, const string& s, int idx_y, int idx_x);
        // Paste string to vector
        bool paste(std::vector<string>& b, const std::vector<string>& s_list, int idx_y, int idx_x);
    }

    namespace Str
    {
        std::vector<string> split(const string& text, char delimiter);
        bool replace(std::string& str, const std::string& from, const std::string& to);
        void remove(string& text, char c);
        void remove(string& text, string characters_to_remove);
    }

    namespace Files
    {
        string get_curr_dir();
        string read_file(string abs_file_path);
        std::vector<string> read_file_lines(string abs_file_path);
    }
}

class Nano
{
private:
    string message;
    // TODO: zamijeniti vector sa linked list strukturom zbog ubacivanja usred popisa
    std::vector<string> buffer;

public:

    Nano(std::vector<string> content = std::vector<string>()); //, int width = 120, int height = 40, char border = '@', char background = ' ');

    void run()
    {
        std::cout << "Press any button to start and ESCAPE to exit.\nThis program switches all tabs to four spaces.\n";

        Console_Cursor cursor = { 0, 0 };
        Console_CI_Manager console = Console_CI_Manager();
        Input_Engine engine(this->buffer, console.get_writeable_height(), console.get_characters_per_line());

        int ch = _getch();
        // while char not ESCAPE
        while (ch != 27)
        {
            cursor.set_values(engine.get_x_idx(), engine.get_y_idx());

            if (engine.is_text_marked())
                console.set_lines_coloured(engine.paginated_start(), engine.paginated_end(), cursor, 1, 1, engine.get_marked_start_pos());
            else
                console.set_lines(engine.paginated_start(), engine.paginated_end(), cursor);

            console.show();
            ch = engine.get_and_process_input();
        }
    }

    string get_content()
    {
        if (buffer.size() == 0)
            return "";
        if (buffer.size() == 1)
            return buffer[0];

        int size = 0;
        for (auto it = buffer.begin(); it != buffer.end(); ++it)
            size += it->length();

        string output;
        output.reserve(size);

        output += buffer[0];
        for (auto it = buffer.begin() + 1; it != buffer.end(); ++it)
        {
            output += NANO_CPP_MAIN_LINE_FEED_TEXT + *it;
        }
        return output;
    }

    ~Nano() {}
};

bool NANO::Str::replace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

bool NANO::Buff::put(std::vector<string>& b, const string& s, int idx_y, int idx_x)
{
    if (idx_y < b.size() && idx_x <= b[idx_y].length())
    {
        if (idx_x == 0)
            b[idx_y] = s + b[idx_y];
        else if (idx_x == b[idx_y].length())
            b[idx_y] += s;
        else
            b[idx_y] = b[idx_y].substr(0, idx_x) + s + b[idx_y].substr(idx_x);
        return true;
    }
    return false;
}

bool NANO::Buff::paste(std::vector<string>& b, const std::vector<string>& s_list, int idx_y, int idx_x)
{
    if (s_list.size() == 0)
        return true;
    if (s_list.size() == 1)
        return NANO::Buff::put(b, s_list[0], idx_y, idx_x);

    b.reserve(int((b.size() + s_list.size()) * 1.2));
    if (idx_y < b.size() && idx_x <= b[idx_y].length())
    {
        string sb = "";
        string se = "";
        if (idx_x == 0)
            se = b[idx_y];
        else if (idx_x == b[idx_y].length())
            sb = b[idx_y];
        else
        {
            sb = b[idx_y].substr(0, idx_x);
            se = b[idx_y].substr(idx_x);
        }

        auto itb = s_list.begin();
        auto ite = s_list.end();

        b[idx_y] = sb + *(itb++);
        b.insert(b.begin() + idx_y + 1, *(--ite) + se);
        while (itb != ite)
            b.insert(b.begin() + idx_y + 1, *(itb++));

        return true;
    }
    return false;
}

std::vector<string> NANO::Str::split(const string& text, char delimiter)
{
    if (text.length() == 0)
    {
        return std::vector<string>();
    }
    unsigned int count = 0;
    for (int i = 0; i < text.length(); ++i)
        if (text[i] == delimiter)
            ++count;
    std::vector<string> lines;
    lines.reserve(count + 1);

    for (int i = 0; i < text.length();)
    {
        int j = i;
        while (j < text.length() && text[j] != delimiter) ++j;
        lines.emplace_back(j - i > 0 ? text.substr(i, j - i) : string(""));
        i = j + 1;
    }
    if (text[text.length() - 1] == delimiter)
        lines.push_back("");
    return lines;
    /* StackOverflow:
    std::vector<string> lines;
    auto start = 0U;
    auto end = text.find(delimiter);
    while (end != std::string::npos)
    {
        lines.push_back(text.substr(start, end - start));
        start = end + delimiter.length();
        end = text.find(delimiter, start);
    }
    return lines;*/
}
void NANO::Str::remove(string& text, char c)
{
    text.erase(std::remove(text.begin(), text.end(), c), text.end());
}
void NANO::Str::remove(string& text, string characters_to_remove)
{
    for (auto it = characters_to_remove.begin(); it != characters_to_remove.end(); ++it)
        text.erase(std::remove(text.begin(), text.end(), *it), text.end());
}

string NANO::Files::get_curr_dir()
{
    char buff[1024] = {};
    curr_dir(buff, 1024);
    return std::move(string(buff) + '\\');
}
string NANO::Files::read_file(string abs_file_path)
{
    std::ifstream ifs = std::ifstream(abs_file_path);
    if (!ifs)
    {
        std::cout << "File at path " << abs_file_path << " does not exist.\n";
        exit(EXIT_FAILURE);
    }
    string file_content = string(std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()));
    ifs.close();
    return file_content;
}
std::vector<string> NANO::Files::read_file_lines(string abs_file_path)
{
    string content = NANO::Files::read_file(abs_file_path);
    NANO::Str::remove(content, '\r');
    return NANO::Str::split(content, '\n');
}

// , int width, int height, char border, char background) : buffer(content), ekran(Ekran(width, height, border, background)), message(string())
Nano::Nano(std::vector<string> content) : buffer(content)
{
    if (buffer.size() == 0)
    {
        buffer.push_back("");
    }

    for (int i = 0; i < buffer.size(); ++i)
    {
        // // Keep replacing tabs in row until all have been removed
        // while(NANO::Str::replace(buffer[i], "\t", "    ") == true);
        NANO::Str::remove(buffer[i], '\r');
    }
}

#endif