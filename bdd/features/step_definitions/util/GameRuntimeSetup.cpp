#include "GameRuntimeSetup.h"

GameRuntimeSetup::GameRuntimeSetup(const char* configPath, std::unique_ptr<IGameMode> gameMode)
: game(std::make_unique<Game>(configPath, std::move(gameMode)))
, isRunning(false)
, stopRequested(false)
{
}

GameRuntimeSetup::~GameRuntimeSetup()
{
    stop();
}

void GameRuntimeSetup::start(const std::function<void(Game&)>& customLogic)
{
    customLogicThread = std::thread([this, customLogic]()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        customLogic(*game);
        requestStop();
    });

    isRunning.store(true);
    game->run();
    isRunning.store(false);


    if (customLogicThread.joinable())
    {
        customLogicThread.join();
    }
}

void GameRuntimeSetup::requestStop()
{
    if (!stopRequested.exchange(true))
    {
        game->stop();
    }
}


void GameRuntimeSetup::stop()
{
    if (isRunning.load() && !stopRequested.exchange(true))
    {
        game->stop();
    }

    if (customLogicThread.joinable())
    {
        customLogicThread.join();
    }
}

[[nodiscard]] bool GameRuntimeSetup::isGameStopped() const
{
    return !isRunning.load();
}

[[nodiscard]] Game& GameRuntimeSetup::getGame() const
{
    return *game;
}