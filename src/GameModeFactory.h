#pragma once

#ifdef EDITOR_MODE
#include "EditorGameMode.h"
inline std::unique_ptr<IGameMode> CreateGameMode()
{
    return std::make_unique<EditorGameMode>();
}
#else
#include "Game/StandardGameMode.h"
inline std::unique_ptr<IGameMode> CreateGameMode()
{
    return std::make_unique<StandardGameMode>();
}
#endif