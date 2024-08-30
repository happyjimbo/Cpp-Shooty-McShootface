#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"
#include "ProjectileController.h"
#include "ProjectileFiringData.h"

using Aircraft::AircraftEntity;

class ProjectileSpawnSystem {
public:
    ProjectileSpawnSystem(EntitySystem<AircraftEntity>& aircraftSystem, ProjectileController& projectileController)
        : mAircraftSystem(aircraftSystem), mProjectileController(projectileController) {}

    void update(sf::Time delta) const;

private:
    EntitySystem<AircraftEntity>& mAircraftSystem;
    ProjectileController& mProjectileController;
};
