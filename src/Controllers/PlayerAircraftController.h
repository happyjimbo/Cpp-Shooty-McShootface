#pragma once

#include "EntitySystem.h"
#include <Resource/ResourceIdentifiers.h>

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

struct PlayerData;

class PlayerAircraftController final
{
public:
    explicit PlayerAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
        const TextureHolder& textures,
        const PlayerData& playerData,
        sf::Vector2f spawnPosition) noexcept;

    ~PlayerAircraftController() noexcept = default;

    explicit PlayerAircraftController(PlayerAircraftController&) = delete;
    PlayerAircraftController& operator=(PlayerAircraftController&) = delete;

    explicit PlayerAircraftController(PlayerAircraftController&&) = delete;
    PlayerAircraftController& operator=(PlayerAircraftController&&) = delete;

    AircraftEntity* getPlayerAircaft() const;

private:
    friend class GuiController;
    AircraftEntity* mPlayerAircraft;
};
