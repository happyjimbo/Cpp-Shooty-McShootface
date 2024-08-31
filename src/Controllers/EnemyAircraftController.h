#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

using Aircraft::AircraftEntity;

class EnemyAircraftController final
{
public:
    explicit EnemyAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
        float scrollSpeed
    ) noexcept;

    void tick(const sf::Time&);

private:
    float spawnInterval(float delta);
    void spawn(float spawnInterval);
    void accelerate(float speed) const;

    constexpr static float mSpeedDivider = 100.f;
    constexpr static float mEnemyProjectileSpawnSpeed = 3.f;

    EntitySystem<AircraftEntity>& mEntitySystem;

    float mTimeSinceLastSpawn {};
    float mScrollSpeed;
};
