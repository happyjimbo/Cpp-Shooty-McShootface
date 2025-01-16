#include <cucumber-cpp/generic.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include "Game.h"
#include "GameSettings.h"
#include "StateHandler.h"
#include "GameRuntimeSetup.h"
#include "GameContext.h"


namespace
{
    WHEN("^Click x:(\\d+) and y:(\\d+) to start the game")
    {
        REGEX_PARAM(int, xpos);
        REGEX_PARAM(int, ypos);
        constexpr int duration = 2;

        cucumber::ScenarioScope<GameContext> context;

        auto customLogic = [&context, duration, xpos, ypos](Game&)
        {
            std::this_thread::sleep_for(std::chrono::seconds(duration));
            std::cout << "Clicking the button after 2 seconds." << std::endl;

            sf::Event mockClick;
            mockClick.type = sf::Event::MouseButtonPressed;
            mockClick.mouseButton.x = xpos;
            mockClick.mouseButton.y = ypos;

            const auto* stateHandler = context->runtime->getGame().getStateHandler();
            stateHandler->processWindowEvents(mockClick);

            std::this_thread::sleep_for(std::chrono::seconds(duration));
;        };

        context->runtime->start(customLogic);
        std::cout << "Game initialized successfully" << std::endl;
    }

}
