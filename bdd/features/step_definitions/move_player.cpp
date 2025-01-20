#include <thread>
#include <cucumber-cpp/generic.hpp>
#include <gtest/gtest.h>

#include "util/GameContext.h"
#include "StateHandler.h"

namespace
{
    sf::Event keyboardPress(const sf::Keyboard::Key key, const sf::Event::EventType type)
    {
        sf::Event keyboardPressRight {};
        keyboardPressRight.type = type;
        keyboardPressRight.key.code = key;
        return keyboardPressRight;
    }

    std::array keys = {
        sf::Keyboard::Key::Space,
        sf::Keyboard::Key::Down,
        sf::Keyboard::Key::Right,
        sf::Keyboard::Key::Left,
        sf::Keyboard::Key::Up,
    };

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

            for (auto key : keys)
            {
                sf::Event keyPressed = keyboardPress(key, sf::Event::KeyPressed);
                sf::Clock clock {};

                while (clock.getElapsedTime().asSeconds() < 1.0f)
                {
                    stateHandler->processWindowEvents(keyPressed);
                }

                sf::Event keyReleased = keyboardPress(key, sf::Event::KeyReleased);
                stateHandler->processWindowEvents(keyReleased);

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        };

        context->runtime->start(customLogic);
        std::cout << "Game initialized successfully" << std::endl;
    }

}
