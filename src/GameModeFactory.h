#pragma once


#ifdef EDITOR_MODE
#include "EditorGameMode.h"
namespace GameMode
{
    inline std::unique_ptr<IGameMode> CreateGameMode()
    {
        return std::make_unique<EditorGameMode>();
    }
}
#else
#include "StandardGameMode.h"
namespace GameMode
{
    inline std::unique_ptr<IGameMode> CreateGameMode()
    {
        return std::make_unique<StandardGameMode>();
    }
}
#endif