#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

class GameSettings;

class Game final
{
public:
    explicit Game(const std::string& configPath) noexcept;
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
