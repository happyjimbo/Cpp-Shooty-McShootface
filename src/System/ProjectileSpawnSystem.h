#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

using Aircraft::AircraftEntity;

class ProjectileController;

class ProjectileSpawnSystem {
public:
    explicit ProjectileSpawnSystem(EntitySystem<AircraftEntity>& entiySystem, ProjectileController& projectileController) noexcept;

    explicit ProjectileSpawnSystem() = delete;
    ~ProjectileSpawnSystem() = default;

    ProjectileSpawnSystem(const ProjectileSpawnSystem&) = delete;
    ProjectileSpawnSystem& operator=(const ProjectileSpawnSystem&) = delete;

    ProjectileSpawnSystem(ProjectileSpawnSystem&&) = delete;
    ProjectileSpawnSystem& operator=(ProjectileSpawnSystem&&) = delete;

    void execute(const sf::Time& delta) const;

private:
    EntitySystem<AircraftEntity>& mEntiySystem;
    ProjectileController& mProjectileController;
};