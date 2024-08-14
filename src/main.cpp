#include <iostream>
#include "Game.h"

int main()
{
    try
    {
        Game game;
        game.run();
    }
    // catch by reference, so we're not making a copy and keep values from inheritance chain
    catch (std::exception& exception)
    {
        std::cout << "Exception\n" << exception.what() << std::endl;
    }
}
