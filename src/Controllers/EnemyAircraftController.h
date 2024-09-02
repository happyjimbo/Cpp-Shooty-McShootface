#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

using Aircraft::AircraftEntity;

class EnemyAircraftController final
{
public:
    explicit EnemyAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
        const AircraftEntity& player,
        float scrollSpeed
    ) noexcept;

    void tick(const sf::Time&);

private:
    float spawnInterval(float delta);
    void spawn(float spawnInterval);
    void accelerate(float speed) const;

    constexpr static float sSpeedDivider = 100.f;
    constexpr static float sEnemyProjectileSpawnSpeed = 3.f;
    constexpr static float sSpeedX = 0.05f;

    EntitySystem<AircraftEntity>& mEntitySystem;

    float mTimeSinceLastSpawn {};
    float mScrollSpeed;

    const AircraftEntity& mPlayer;
};
