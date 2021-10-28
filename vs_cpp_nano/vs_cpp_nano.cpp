
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

std::ostream& operator<<(std::ostream& out, const SMALL_RECT& coord)
{
    out << "(" << coord.Left <<
        ", " << coord.Top <<
        ", " << coord.Right <<
        ", " << coord.Bottom << ")";
    return out;
}

int main()
{
    bool esc_pressed = false;
    COORD size = Console.get_buffer_size();

    while (!esc_pressed)
    {
        if (keyup::escape())
        {
            esc_pressed = true;
        }

        if (keyup::arrow_up())
        {
            size.X++;
            size.Y++;
        }
        if (keyup::arrow_down())
        {
            size.X--;
            size.Y--;
        }

        if (keyup::enter())
        {
            Console.set_buffer_size(size);
            std::cout << "size=" << size;
            std::cout << " console=" << Console.get_buffer_size() << std::endl;
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
