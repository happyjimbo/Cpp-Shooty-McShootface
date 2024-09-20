#pragma once
#include <memory>

class Game final
{
public:
    explicit Game() noexcept;
    ~Game() noexcept;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    void run() const;

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};
