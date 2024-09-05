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
    explicit PlayerAircraftController(EntitySystem<AircraftEntity>& entitySystem) noexcept;
    ~PlayerAircraftController() = default;

    void create(const TextureHolder& textures, sf::Vector2f spawnPosition);
    AircraftEntity* getPlayerAircaft() const;

private:

    friend class GuiController;

    AircraftEntity* mPlayerAircraft;
    EntitySystem<AircraftEntity>& mEntitySystem;

    constexpr static int sPlayerHealth = 10;
};
