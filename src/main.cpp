#include <iostream>
#include <tracy/Tracy.hpp>

#include "Game.h"
#include "GameSettings.h"


void* operator new (std::size_t size)
{
    void* ptr = malloc(size);
    TracyAlloc(ptr, size);
    return ptr;
}

void operator delete(void* ptr) noexcept
{
    TracyFree(ptr);
    free(ptr);
}

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

        GameSettings::setConfigPath(configPath);

        Game game;
        game.run();
    }
    catch (std::exception& exception)
    {
        std::cout << "Exception\n" << exception.what() << std::endl;
    }
}