#include <cucumber-cpp/generic.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include "Game.h"
#include "GameSettings.h"
#include "GameModeFactory.h"
#include "StateHandler.h"


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

    GIVEN("^Click x:(\\d+) and y:(\\d+) to start the game")
    {
        REGEX_PARAM(int, xpos);
        REGEX_PARAM(int, ypos);
        constexpr int duration = 2;

        cucumber::ScenarioScope<GameContext> context;
        std::unique_ptr<IGameMode> gameMode = GameMode::CreateGameMode();

        const char* configPath = "./Media/Data/settings.csv";

        context->game = std::make_unique<Game>(configPath, std::move(gameMode));

        context->orchestratorThread = std::thread([&context, duration, xpos, ypos]()
        {
            std::this_thread::sleep_for(std::chrono::seconds(duration));
            std::cout << "Clicking the button after 2 seconds." << std::endl;

            sf::Event mockClick;
            mockClick.type = sf::Event::MouseButtonPressed;
            mockClick.mouseButton.x = xpos;
            mockClick.mouseButton.y = ypos;


            auto* stateHandler = context->game->getStateHandler();
            stateHandler->processWindowEvents(mockClick);

            std::this_thread::sleep_for(std::chrono::seconds(duration));
            std::cout << "Destroying the game after 2 seconds." << std::endl;
            context->game->stop();
;        });

        context->game->run();
        std::cout << "Game initialized successfully" << std::endl;
    }

}
