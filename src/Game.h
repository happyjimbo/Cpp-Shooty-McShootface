#pragma once

#include "SFML/Graphics.hpp"
#include "World.h"
#include "Controls.h"

class Game final : private sf::NonCopyable
{
public:
    explicit Game();
    void run();

private:
    void processInputs();
    void render();
    void update(sf::Time);

    static const sf::Time TimePerFrame;
    sf::RenderWindow mWindow;
    World mWorld;
    Controls mControls;

    static constexpr const auto* mTitle = "Shooty McShootface";
    static constexpr int mScreenWidth {640};
    static constexpr int mScreenHeight {480};
    static constexpr float mSeconds {1.f / 60.f};
};