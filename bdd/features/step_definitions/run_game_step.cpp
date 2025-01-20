#include <cucumber-cpp/generic.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include "Game.h"
#include "GameSettings.h"
#include "GameModeFactory.h"
#include "util/GameRuntimeSetup.h"
#include "util/GameContext.h"

namespace
{
    GIVEN("^Game is initalized$")
    {
        cucumber::ScenarioScope<GameContext> context;

        std::unique_ptr<IGameMode> gameMode = GameMode::CreateGameMode();
        const char* configPath = "./Media/Data/settings.csv";
        context->runtime = std::make_unique<GameRuntimeSetup>(configPath, std::move(gameMode));
    }

    WHEN("^Run for (\\d+) seconds$")
    {
        REGEX_PARAM(int, duration);

        cucumber::ScenarioScope<GameContext> context;

        auto customLogic = [duration](Game&)
        {
            std::cout << "Custom logic running..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(duration));
            std::cout << "Custom logic finished, stopping game." << std::endl;
        };

        context->runtime->start(customLogic);

        std::cout << "Game is running for the specified duration..." << std::endl;
    }

    THEN("^The game should exit successfully$")
    {
        cucumber::ScenarioScope<GameContext> context;
        ASSERT_TRUE(context->runtime->isGameStopped()) << "Game did not stop as expected!";
        std::cout << "Game stopped successfully." << std::endl;
    }
}
