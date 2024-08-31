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
    explicit PlayerAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
        sf::Vector2f worldCenter,
        sf::Vector2f worldSize,
        float scrollSpeed
    ) noexcept;

    void create(const TextureHolder& textures, sf::Vector2f spawnPosition);

    void tick(sf::Time) const;

    AircraftEntity* getPlayerAircaft() const;

private:
    void enforceBoundaries() const;

    AircraftEntity* mPlayerAircraft;

    EntitySystem<AircraftEntity>& mEntitySystem;

    const sf::Vector2f mWorldCenter;
    const sf::Vector2f mWorldSize;

    sf::FloatRect mViewBounds;

    const float mScrollSpeed;

    constexpr static float mBorderDistance = 40.f;
};
