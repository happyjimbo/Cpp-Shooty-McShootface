#pragma once

#include "EntitySystem.h"
#include <Resource/ResourceIdentifiers.h>

namespace Aircraft { class AircraftEntity; }

struct PlayerData;

class PlayerAircraftInitializer final
{
public:
    explicit PlayerAircraftInitializer(
        EntitySystem<Aircraft::AircraftEntity>& entitySystem,
        const TextureHolder& textures,
        ShaderHolder& shaders,
        const PlayerData& playerData,
        sf::Vector2f spawnPosition) noexcept;

    ~PlayerAircraftInitializer() noexcept = default;

    explicit PlayerAircraftInitializer(PlayerAircraftInitializer&) = delete;
    PlayerAircraftInitializer& operator=(PlayerAircraftInitializer&) = delete;

    explicit PlayerAircraftInitializer(PlayerAircraftInitializer&&) = delete;
    PlayerAircraftInitializer& operator=(PlayerAircraftInitializer&&) = delete;

    Aircraft::AircraftEntity* getPlayerAircaft() const;

private:
    friend class GuiInitializer;
    Aircraft::AircraftEntity* mPlayerAircraft;
};
