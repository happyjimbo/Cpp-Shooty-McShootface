#pragma once

#include "EntitySystem.h"
#include <Resource/ResourceIdentifiers.h>

namespace Aircraft { class AircraftEntity; }

struct PlayerData;

class PlayerAircraftController final
{
public:
    explicit PlayerAircraftController(
        EntitySystem<Aircraft::AircraftEntity>& entitySystem,
        const TextureHolder& textures,
        ShaderHolder& shaders,
        const PlayerData& playerData,
        sf::Vector2f spawnPosition) noexcept;

    ~PlayerAircraftController() noexcept = default;

    explicit PlayerAircraftController(PlayerAircraftController&) = delete;
    PlayerAircraftController& operator=(PlayerAircraftController&) = delete;

    explicit PlayerAircraftController(PlayerAircraftController&&) = delete;
    PlayerAircraftController& operator=(PlayerAircraftController&&) = delete;

    Aircraft::AircraftEntity* getPlayerAircaft() const;

private:
    friend class GuiController;
    Aircraft::AircraftEntity* mPlayerAircraft;
};
