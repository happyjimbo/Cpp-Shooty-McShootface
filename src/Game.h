#pragma once

#include "SFML/Graphics.hpp"
#include "World.h"

class Game final : private sf::NonCopyable
{
public:
    explicit Game();
    void run();

private:
    void update(sf::Time);
    void processWindowEvents();
    void render();

    static const sf::Time TimePerFrame;
    sf::RenderWindow mWindow;
    World mWorld;

    static constexpr const auto* mTitle = "Shooty McShootface";
    static constexpr int mScreenWidth {640};
    static constexpr int mScreenHeight {480};
    static constexpr float mSeconds {1.f / 60.f};
};