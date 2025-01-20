#include "GameRuntimeSetup.h"

struct GameContext
{
    std::unique_ptr<GameRuntimeSetup> runtime;
};