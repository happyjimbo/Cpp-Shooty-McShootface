#pragma once

#include "EntitySystem.h"

namespace Aircraft { class AircraftEntity; }

namespace sf { class Time; }

class EnemyAircraftMovementSystem final
{
public:
    explicit EnemyAircraftMovementSystem(EntitySystem<Aircraft::AircraftEntity>& entitySystem, const Aircraft::AircraftEntity& player, float scrollSpeed) noexcept;
    ~EnemyAircraftMovementSystem() noexcept = default;

    EnemyAircraftMovementSystem(const EnemyAircraftMovementSystem&) = delete;
    EnemyAircraftMovementSystem& operator=(const EnemyAircraftMovementSystem&) = delete;

    EnemyAircraftMovementSystem(const EnemyAircraftMovementSystem&&) = delete;
    EnemyAircraftMovementSystem& operator=(const EnemyAircraftMovementSystem&&) = delete;

    void execute(const sf::Time& delta);

private:
    EntitySystem<Aircraft::AircraftEntity>& mEntitySystem;
    const Aircraft::AircraftEntity& mPlayer;

    float mTimeSinceLastSpawn {};
    float mScrollSpeed {};
};