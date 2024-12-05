#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

class EnemyAircraftInitializer final
{
public:
    explicit EnemyAircraftInitializer(EntitySystem<Aircraft::AircraftEntity>& entitySystem) noexcept;
};
