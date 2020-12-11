#define _CRT_SECURE_NO_WARNINGS

// Generic includes
#include <iostream>
#include <conio.h>
//#include <fstream>
#include <stdio.h>

// Containers
#include <vector>
#include <string>

// User includes
#include "Nano.h"

using std::string;

void ending_dialogue(string abs_file_path, string content);

int main(int argc, char* argv[])
{
    /*if (argc != 2)
    {
        std::cout << "You are missing the file name.\n";
        exit(EXIT_FAILURE);
    }*/
    //string abs_file_path = NANO::Files::get_curr_dir() + argv[1];
    string abs_file_path = "C:/Users/stjep/OneDrive/Dokumenti/GitHub/cpp_nano/vs_cpp_nano/Debug/abc.txt";
    std::vector<string> lines = NANO::Files::read_file_lines(abs_file_path);

    Nano nano(lines);
    nano.run();

    ending_dialogue(abs_file_path, nano.get_content());
    return 0;
}

void ending_dialogue(string abs_file_path, string content)
{

    std::cout << "Write file out (y/n)? ";
    char c = 0;
    c = _getch();
    while (c != 'y' && c != 'n')
    {
        std::cout << "Invalid input. Your input: " << c << " allowed characters: y, n\nWrite file out (y/n)? ";
        c = _getch();
    }
    if (c == 'y')
    {
        bool write_again = true;

        while (write_again)
        {
            // std::ofstream ofs;
            // ofs.open(abs_file_path, std::ios::out | std::ios::trunc);
            FILE* ofs = fopen(&abs_file_path[0], "w");
            if (!ofs)
            {
                write_again = false;
                std::cout << "\nOpening failed. press (r) to repeat, or anything else to waste content...\n";
                c = _getch();
                if (c == 'r')
                    write_again = true;
            }
            else
            {
                //ofs << content;
                fprintf(ofs, "%s", content);
                std::cout << "\nContent successfully written.\n";
                write_again = false;
                //ofs.close();
                fclose(ofs);
            }
        }

    }
}
