#pragma once
#include <functional>
#include <thread>

#include "IGameMode.h"
#include "Game.h"

class GameRuntimeSetup final
{
public:

    explicit GameRuntimeSetup(const char* configPath, std::unique_ptr<IGameMode> gameMode);
    ~GameRuntimeSetup();

    void start(const std::function<void(Game&)>& customLogic);
    void requestStop();
    void stop();
    bool isGameStopped() const;

    Game& getGame() const;

private:
    std::unique_ptr<Game> game;
    std::thread customLogicThread;
    std::atomic<bool> isRunning;
    std::atomic<bool> stopRequested;
};
