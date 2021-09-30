
#include <iostream>
#include "lib/Keypress.h"

using namespace Keypress;

int main()
{
    bool esc_pressed = false;
    
    while (!esc_pressed)
    {
        if (is_pressed::escape())
        {
            esc_pressed = true;
        }

        if (keyup::F1())
        {
            std::cout << "F1 \n";
        }
        if (is_pressed::lmouse())
        {
            std::cout << "Left mouse \n";
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
