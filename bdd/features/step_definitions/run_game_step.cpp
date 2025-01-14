#include <cucumber-cpp/generic.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include "Game.h"
#include "GameSettings.h"
#include "GameModeFactory.h"


namespace
{
    struct GameContext
    {
        std::unique_ptr<Game> game;
        std::thread orchestratorThread;

        // incase the test exists unexpectedly
        ~GameContext()
        {
            if (orchestratorThread.joinable())
            {
                orchestratorThread.join();
            }
        }
    };

    GIVEN("^Run the game for (\\d+) seconds")
    {
        REGEX_PARAM(int, duration);

        cucumber::ScenarioScope<GameContext> context;
        std::unique_ptr<IGameMode> gameMode = GameMode::CreateGameMode();

        const char* configPath = "./Media/Data/settings.csv";

        context->game = std::make_unique<Game>(configPath, std::move(gameMode));

        context->orchestratorThread = std::thread([&context, duration]()
        {
            std::this_thread::sleep_for(std::chrono::seconds(duration));
            std::cout << "Destroying the game after 2 seconds." << std::endl;
            context->game->stop();
        });

        context->game->run();
        std::cout << "Game initialized successfully" << std::endl;
    }

    WHEN("^Waiting to exit")
    {
        std::cout << "Game is running for the specified duration..." << std::endl;
    }

    THEN("^The game should exit successfully$") {
        cucumber::ScenarioScope<GameContext> context;
        if (context->orchestratorThread.joinable())
        {
            context->orchestratorThread.join();
        }

        context->game.reset();

        ASSERT_EQ(context->game, nullptr) << "Game instance was not properly destroyed!";
        std::cout << "Game ended successfully and was properly cleaned up!" << std::endl;
    }
}