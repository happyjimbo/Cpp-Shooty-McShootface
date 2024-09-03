#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

using Aircraft::AircraftEntity;

class ProjectileController;

class ProjectileSpawnSystem {
public:
    explicit ProjectileSpawnSystem(EntitySystem<AircraftEntity>& entiySystem, ProjectileController& projectileController) noexcept
        : mEntiySystem(entiySystem), mProjectileController(projectileController) {}

    ~ProjectileSpawnSystem() = default;

    // delete
    explicit ProjectileSpawnSystem() = delete;

    ProjectileSpawnSystem(const ProjectileSpawnSystem&) = delete;
    ProjectileSpawnSystem& operator=(const ProjectileSpawnSystem&) = delete;

    ProjectileSpawnSystem(ProjectileSpawnSystem&&) = delete;
    ProjectileSpawnSystem& operator=(ProjectileSpawnSystem&&) = delete;

    void execute(sf::Time delta) const;

private:
    EntitySystem<AircraftEntity>& mEntiySystem;
    ProjectileController& mProjectileController;
};