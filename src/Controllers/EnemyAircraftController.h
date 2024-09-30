#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

class EnemyAircraftController final
{
public:
    explicit EnemyAircraftController(EntitySystem<Aircraft::AircraftEntity>& entitySystem) noexcept;
};
