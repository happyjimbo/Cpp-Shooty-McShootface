#pragma once

#include "EntitySystem.h"

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

namespace sf { class Time; }

class EnemyAircraftMovementSystem final
{
public:
    explicit EnemyAircraftMovementSystem(EntitySystem<AircraftEntity>& entitySystem, const AircraftEntity& player, float scrollSpeed) noexcept;
    void execute(const sf::Time& delta);

private:
    EntitySystem<AircraftEntity>& mEntitySystem;
    const AircraftEntity& mPlayer;

    float mTimeSinceLastSpawn {};
    float mScrollSpeed {};

    constexpr static float sSpeedDivider = 100.f;
    constexpr static float sEnemyProjectileSpawnSpeed = 1.f;
    constexpr static float sSpeedX = 0.05f;
};