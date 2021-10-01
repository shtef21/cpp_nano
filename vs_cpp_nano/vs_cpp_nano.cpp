
#include <iostream>
#include "lib/Keypress.h"
#include "lib/ConsoleApi.h"

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

        if (keyup::arrow_right())
        {
            Console.set_size(Console.get_width() + 1, Console.get_height());
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
