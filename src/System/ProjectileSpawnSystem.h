#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

using Aircraft::AircraftEntity;

class ProjectileController;

class ProjectileSpawnSystem {
public:
    ProjectileSpawnSystem(EntitySystem<AircraftEntity>& entiySystem, ProjectileController& projectileController) noexcept
        : mEntiySystem(entiySystem), mProjectileController(projectileController) {}

    void execute(sf::Time delta) const;

private:
    EntitySystem<AircraftEntity>& mEntiySystem;
    ProjectileController& mProjectileController;
};