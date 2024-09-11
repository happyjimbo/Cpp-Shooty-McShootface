#pragma once

#include "StateHandler.h"
#include "TransitionScreen.h"
#include "SFML/Graphics.hpp"
#include "World.h"

class StateHandler;

class Game final
{
public:
    explicit Game();
    ~Game() = default;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    void run();

private:
    void update(sf::Time) const;
    void processWindowEvents();
    void render();

    void startGame();
    void transitionScreen(const char* title, const char* buttonText);

    sf::RenderWindow mWindow;

    FontHolder mFont;
    std::unique_ptr<StateHandler> mStateHandler;
};
