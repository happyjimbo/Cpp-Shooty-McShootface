#include <iostream>
#include "Game.h"
#include "GameSettings.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Please provide the configuration file path." << std::endl;
        return 1;
    }

    try
    {
        const std::string configPath = argv[1];
        std::cout << "Using config file: " << configPath << std::endl;

        GameSettings::setConfigPath(configPath);

        const Game game;
        game.run();
    }
    // catch by reference, so we're not making a copy and keep values from inheritance chain
    catch (std::exception& exception)
    {
        std::cout << "Exception\n" << exception.what() << std::endl;
    }
}
