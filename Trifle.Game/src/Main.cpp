#include <iostream>
#include "Game.h"

int main(int argc, const char** argv)
{

    std::cout << "Start" << std::endl;

    Game game;

    game.Init();

    return game.Run();
}