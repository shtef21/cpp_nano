
#include <iostream>
#include <Windows.h>
#include "lib/Keypress.h"
#include "lib/ConsoleApi.h"

using namespace Keypress;

std::ostream& operator<<(std::ostream& out, const COORD& coord)
{
    out << "(" << coord.X << ", " << coord.Y << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const RECT& coord)
{
    out << "(" << coord.left << ", " << coord.top
        << ", " << coord.right << ", " << coord.bottom << ")";
    return out;
}

int main()
{
    bool esc_pressed = false;
    
    while (!esc_pressed)
    {
        if (keyup::escape())
        {
            esc_pressed = true;
        }

        if (keyup::enter())
        {
            std::cout << Console.get_size_buffer() << std::endl;
        }
        if (keyup::lshift())
        {
            Console.write({
                "aaa",
                "bbbb",
                "cccccccc"
                });
        }

        if (keyup::arrow_right())
        {
            Console.set_size_rel(+1, 0);
        }
        if (keyup::arrow_left())
        {
            Console.set_size_rel(-1, 0);
        }
        if (keyup::arrow_up())
        {
            Console.set_size_rel(0, -1);
        }
        if (keyup::arrow_down())
        {
            Console.set_size_rel(0, +1);
        }
    }

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
