#include <iostream>
#include "lib/Keypress.h"

#include "olcConsoleGameEngine.h"

class Game : public olcConsoleGameEngine
{
private:

public:

    bool OnUserCreate()
    {
        return true;
    }

    bool OnUserUpdate(float f_elapsed)
    {

        for (int i = 0; i < 160; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                Draw(i, j, FG_WHITE, BG_GREEN);
            }
        }

        return true;
    }

    bool OnUserDestroy()
    {
        return true;
    }

};

#include <Windows.h>

class Console
{
public:
    
    short width, height;
    short fontw, fonth;
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE h_console_in = GetStdHandle(STD_INPUT_HANDLE);
    SMALL_RECT window_size;

    CHAR_INFO* screen = nullptr;

public:

    ~Console()
    {
        delete[] screen;
    }

    Console(short width, short height, int font_width, int font_height)
    {
        this->width = width;
        this->height = height;
        this->fontw = font_width;
        this->fonth = font_height;

        // Assign screen buffer
        SetConsoleActiveScreenBuffer(h_console);

        // Physical window size
        this->window_size = { 0, 0, short(width - 1), short(height - 1) };
        SetConsoleWindowInfo(h_console, TRUE, &window_size);

        // Allocate memory for screen
        this->screen = new CHAR_INFO[width * height];
        memset(screen, 0, sizeof(CHAR_INFO) * width * height);

    }

};



int main()
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT rect = { 0, 0, 1, 1 };


    while (!Keypress::keyup::escape());

    return 0;
}
