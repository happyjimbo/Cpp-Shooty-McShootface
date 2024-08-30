#pragma once

#include "EntitySystem.h"
#include <Resource/ResourceIdentifiers.h>

namespace Aircraft
{
    class AircraftEntity;
}
using Aircraft::AircraftEntity;

class ProjectileController;

class CommandQueue;

namespace sf
{
    class Time;
}

class PlayerAircraftController final
{
public:
    explicit PlayerAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
        CommandQueue& commandQueue,
        sf::Vector2f worldCenter,
        sf::Vector2f worldSize,
        float scrollSpeed
    ) noexcept;

    void create(const TextureHolder& textures, sf::Vector2f spawnPosition);
    void tick(sf::Time) const;

private:
    void adaptPlayerVelocity() const;

    AircraftEntity* mPlayerAircraft;

    EntitySystem<AircraftEntity>& mEntitySystem;
    CommandQueue& mCommandQueue;

    const sf::Vector2f mWorldCenter;
    const sf::Vector2f mWorldSize;

    sf::FloatRect mViewBounds;

    const float mScrollSpeed;

    constexpr static float mBorderDistance = 40.f;
};
