#pragma once

#include "SFML/Graphics.hpp"
#include "World.h"

class Game final : private sf::NonCopyable
{
public:
    explicit Game();
    void run();

private:
    void update(sf::Time) const;
    void processWindowEvents();
    void render();

    void endGame();

    static const sf::Time TimePerFrame;
    sf::RenderWindow mWindow;
    // std::unique_ptr<World> mWorld;
    World* mWorld;

    static constexpr const auto* sTitle = "Shooty McShootface";
    static constexpr int sScreenWidth {640};
    static constexpr int sScreenHeight {480};
    static constexpr float sSeconds {1.f / 60.f};
};