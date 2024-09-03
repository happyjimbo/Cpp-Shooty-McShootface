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
    ~Game() noexcept;

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

    static const sf::Time TimePerFrame;
    sf::RenderWindow mWindow;
    // std::unique_ptr<World> mWorld;

    FontHolder mFont;
    StateHandler* mStateHandler;

    static constexpr const auto* sTitle = "Shooty McShootface";
    static constexpr int sScreenWidth {640};
    static constexpr int sScreenHeight {480};
    static constexpr float sSeconds {1.f / 60.f};
};
