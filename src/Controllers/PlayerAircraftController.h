#pragma once

#include "EntitySystem.h"
#include "ResourceIdentifiers.h"

class ProjectileController;
class CommandQueue;
class AircraftEntity;

namespace sf
{
    class Time;
}

class PlayerAircraftController final
{
public:
    explicit PlayerAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
        ProjectileController& projectileController,
        CommandQueue& commandQueue,
        sf::Vector2f worldCenter,
        sf::Vector2f worldSize,
        float scrollSpeed
    ) noexcept;

    ~PlayerAircraftController();

    void create(const TextureHolder& textures, sf::Vector2f spawnPosition);
    void tick(sf::Time) const;

private:
    void adaptPlayerVelocity() const;
    void adaptPlayerPosition() const;

    AircraftEntity* mPlayerAircraft;

    EntitySystem<AircraftEntity>& mEntitySystem;
    ProjectileController& mProjectileController;
    CommandQueue& mCommandQueue;

    const sf::Vector2f mWorldCenter;
    const sf::Vector2f mWorldSize;

    sf::FloatRect mViewBounds;

    const float mScrollSpeed;

    constexpr static float mBorderDistance = 40.f;
};
