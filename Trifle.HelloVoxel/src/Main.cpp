#include <iostream>
#include "Program.h"

int main(int argc, const char** argv)
{
    std::cout << "Start" << std::endl;

    Program program;

    program.Init();

    return program.Run();
}