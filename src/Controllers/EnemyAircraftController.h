#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

using Aircraft::AircraftEntity;

class EnemyAircraftController final
{
public:
    explicit EnemyAircraftController(EntitySystem<AircraftEntity>& entitySystem) noexcept;
};
