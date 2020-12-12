#include <iostream>
#include <string>
#include "Nano.h"

int main(int argc, char* argv[])
{
    std::string file_path = argc > 1 ? argv[1] : "abc.txt";

    Nano nano = Nano(file_path);
    nano.run();

    return 0;
}

