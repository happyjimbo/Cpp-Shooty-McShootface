#pragma once

#include "EntitySystem.h"
#include <Resource/ResourceIdentifiers.h>

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class ProjectileController;

namespace sf
{
    class Time;
}

class PlayerAircraftController final
{
public:
    explicit PlayerAircraftController(EntitySystem<AircraftEntity>& entitySystem,
                                      const TextureHolder& textures,
                                      sf::Vector2f spawnPosition) noexcept;
    ~PlayerAircraftController() = default;

    AircraftEntity* getPlayerAircaft() const;

private:

    friend class GuiController;

    AircraftEntity* mPlayerAircraft;

    constexpr static int sPlayerHealth = 10;
};
