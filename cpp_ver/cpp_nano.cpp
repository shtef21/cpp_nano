// Generic includes
#include <iostream>
#include <fstream>

// Containers
#include <vector>
#include <string>

// User includes
#include "assets\Nano"

using std::string;

void ending_dialogue(string abs_file_path, string content);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "You are missing the file name.\n";
        exit(EXIT_FAILURE);
    }
    string abs_file_path = NANO::Files::get_curr_dir() + argv[1];
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
