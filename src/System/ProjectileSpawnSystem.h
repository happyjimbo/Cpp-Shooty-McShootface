#pragma once

#include "AircraftEntity.h"
#include "ProjectileController.h"

class ProjectileSpawnSystem {
public:
    ProjectileSpawnSystem(EntitySystem<AircraftEntity>& aircraftSystem, ProjectileController& projectileController)
        : mAircraftSystem(aircraftSystem), mProjectileController(projectileController) {}

    void update() const;

private:
    EntitySystem<AircraftEntity>& mAircraftSystem;
    ProjectileController& mProjectileController;
};
