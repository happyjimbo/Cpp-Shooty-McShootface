#pragma once

#include <SFML/Graphics.hpp>
#include "World.h"
#include "Controls.h"

class Game final : private sf::NonCopyable
{
public:
    explicit
    Game();
    void run();

private:
    void processInputs();
    void render();
    void update(sf::Time);

private:
    static const sf::Time TimePerFrame;
    sf::RenderWindow mWindow;
    World mWorld;
    Controls mPlayer;
};