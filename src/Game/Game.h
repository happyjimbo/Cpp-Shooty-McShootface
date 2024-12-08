#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

class Game final
{
public:
    explicit Game() noexcept;
    ~Game() noexcept;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    void run();

private:
    sf::Clock mClock;

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};
