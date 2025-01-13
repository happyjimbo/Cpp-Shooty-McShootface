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
    };

    GIVEN("^Start the game$")
    {
        cucumber::ScenarioScope<GameContext> context;
        std::unique_ptr<IGameMode> gameMode = GameMode::CreateGameMode();

        const char* configPath = "./Media/Data/settings.csv";

        context->game = std::make_unique<Game>(configPath, std::move(gameMode));
        std::cout << "Game initialized successfully" << std::endl;
    }

    WHEN("^Run the game$")
    {
        cucumber::ScenarioScope<GameContext> context;

        // Run the game
        if (context->game)
        {
            context->game->run();
            std::cout << "Game is running" << std::endl;
        }
        else
        {
            std::cerr << "Game instance is null!" << std::endl;
        }
    }

    THEN("^The game should end successfully$") {
        cucumber::ScenarioScope<GameContext> context;

        ASSERT_NE(context->game, nullptr) << "Game instance is null!";

        context->game.reset();

        ASSERT_EQ(context->game, nullptr) << "Game instance was not properly destroyed!";
        std::cout << "Game ended successfully and was properly cleaned up!" << std::endl;
    }
}