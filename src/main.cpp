#include <iostream>
#include "TracyOperators.h"
#include "Game.h"
#include "GameSettings.h"
#include "GameModeFactory.h"

int main(const int argc, char* argv[])
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

        std::unique_ptr<IGameMode> gameMode = CreateGameMode();

        Game game {configPath, std::move(gameMode)};
        game.run();
    }
    catch (std::exception& exception)
    {
        std::cout << "Exception\n" << exception.what() << std::endl;
    }
}
