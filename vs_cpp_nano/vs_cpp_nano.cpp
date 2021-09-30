
#include <iostream>
#include "lib/Keypress.h"

using namespace Keypress;

int main()
{
    bool esc_pressed = false;
    
    while (!esc_pressed)
    {
        if (keyup::escape())
        {
            esc_pressed = true;
        }

        if (keyup::is_keyup() == false)
        {
            std::cout << "No press\n";
            continue;
        }

        char letter = keyup::letter_get();
        if (letter != 0)
        {
            std::cout << letter;
        }

        int f_get = keyup::F_get();
        if (f_get != 0)
        {
            std::cout << "[F" << f_get << "]";
        }

        int num_get = keyup::number_get();
        if (num_get != -1)
        {
            std::cout << num_get;
        }
    }

    std::cout << "Hello";
    return 0;
}

/*#include <string>
#include "Nano.h"

int main(int argc, char* argv[])
{
    std::string file_path = argc > 1 ? argv[1] : "abc.txt";

    Nano nano = Nano(file_path);
    nano.run();

    return 0;
}
*/
