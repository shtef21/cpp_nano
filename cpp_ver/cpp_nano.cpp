// Generic includes
#include <iostream>
#include <fstream>
#include <algorithm>

// Containers
#include <vector>
#include <string>

// User includes
#include "assets\Nano"
#include "assets\curr_dir.h"

using std::string;

namespace String
{
    std::vector<string> split(const string& text, std::string delimiter);
    void remove(string& text, char c);
    void remove(string& text, string characters_to_remove);
}

string get_curr_dir();
string read_file(string abs_file_path);
void ending_dialogue(string abs_file_path, string content);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "You are missing the file name.\n";
        exit(EXIT_FAILURE);
    }
    string file_name = argv[1];
    string abs_file_path = get_curr_dir() + file_name;

    {
        string file_content = read_file(abs_file_path);
        
        std::cout << "File content:\nBEGIN\n" << file_content << "\nEND\n";
        String::remove(file_content, '\r');
        std::cout << "File content:\nBEGIN\n" << file_content << "\nEND\n";
        
        std::vector<string> lines = String::split(file_content, "\n");


        {
        std::cout << "Sending...\nBEGIN\n";
        for (auto it = lines.begin(); it != lines.end(); ++it)
            std::cout << "Line>" << *it << "\n";
        std::cout << "END\n";
        }

        Nano nano(lines);
        nano.run();

        ending_dialogue(abs_file_path, nano.get_content());
    }

    

    return 0;
}

void ending_dialogue(string abs_file_path, string content)
{
    std::cout << "Write file out (y/n)? ";
    char c = 0;
    std::cin >> c;
    while (c != 'y' && c != 'n')
    {
        std::cout << "Invalid input. Your input: " << c << " allowed characters: y, n\nWrite file out (y/n)? ";
        std::cin >> c;
    }
    if (c == 'y')
    {
        bool write_again = true;
        std::ofstream ofs;

        while (write_again)
        {
            ofs.open(abs_file_path, std::ofstream::out | std::ofstream::trunc);
            if (!ofs)
            {
                write_again = false;
                std::cout << "Opening failed. press (r) to repeat, or anything else to waste content...\n";
                std::cin >> c;
                if (c == 'r')
                    write_again = true;
            }
            else
            {
                ofs << content;
                std::cout << "Content successfully written.\n";
                write_again = false;
                ofs.close();
            }
        }

    }
}

string get_curr_dir()
{
    char buff[500]={};
    curr_dir(buff, 500);
    return std::move(string(buff) + '\\');
}

string read_file(string abs_file_path)
{
    std::ifstream ifs = std::ifstream(abs_file_path);
    if (!ifs)
    {
        std::cout << "File does not exist.\n";
        exit(EXIT_FAILURE);
    }
    string file_content = string(std::istreambuf_iterator<char>(ifs),(std::istreambuf_iterator<char>()));
    ifs.close();
    return file_content;
}

std::vector<string> String::split(const string& text, std::string delimiter)
{
    std::vector<string> lines;

    for (auto it = text.begin(); it != text.end(); ++it)
    {
        string s = "";
        while (*it != '\n' && it != text.end())
        {
            s += *it;
            ++it;
        }
        if (it != text.end())
        {
            if (*it == '\n')
                ++it;
        }
        lines.push_back(s);
    }
    return lines;

    /*
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

void String::remove(string& text, char c)
{
    text.erase(std::remove(text.begin(), text.end(), c), text.end());
}

void String::remove(string& text, string characters_to_remove)
{
    for (auto it = characters_to_remove.begin(); it != characters_to_remove.end(); ++it)
        remove(text, *it);
}
