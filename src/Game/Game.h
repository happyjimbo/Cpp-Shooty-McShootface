#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

class IGameMode;
class GameSettings;

class Game final
{
public:
    explicit Game(const std::string& configPath, std::unique_ptr<IGameMode> gameMode) noexcept;
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
