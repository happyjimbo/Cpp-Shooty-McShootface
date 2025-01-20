#include <thread>
#include <cucumber-cpp/generic.hpp>
#include <gtest/gtest.h>

#include "util/GameContext.h"
#include "StateHandler.h"

namespace
{
    WHEN("^Move player")
    {
        int xpos = 527; // this is bad yo
        int ypos = 435;
        constexpr int duration = 2;

        cucumber::ScenarioScope<GameContext> context;

        auto customLogic = [&context, duration, xpos, ypos](Game&)
        {
            std::this_thread::sleep_for(std::chrono::seconds(duration));
            std::cout << "Clicking the button after 2 seconds." << std::endl;

            sf::Event mockClick {};
            mockClick.type = sf::Event::MouseButtonPressed;
            mockClick.mouseButton.x = xpos;
            mockClick.mouseButton.y = ypos;

            const auto* stateHandler = context->runtime->getGame().getStateHandler();
            stateHandler->processWindowEvents(mockClick);

            std::this_thread::sleep_for(std::chrono::seconds(duration));

            sf::Event keyboardPress {};
            keyboardPress.type = sf::Event::KeyPressed;
            keyboardPress.key.code = sf::Keyboard::Key::D;

            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < duration)
            {
                stateHandler->processWindowEvents(keyboardPress);

                // You can adjust the interval to simulate repeated key presses
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        };

        context->runtime->start(customLogic);
        std::cout << "Game initialized successfully" << std::endl;
    }
}
