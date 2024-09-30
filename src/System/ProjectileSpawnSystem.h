#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

class ProjectileController;

class ProjectileSpawnSystem {
public:
    explicit ProjectileSpawnSystem(EntitySystem<Aircraft::AircraftEntity>& entiySystem, ProjectileController& projectileController) noexcept;

    explicit ProjectileSpawnSystem() = delete;
    ~ProjectileSpawnSystem() = default;

    ProjectileSpawnSystem(const ProjectileSpawnSystem&) = delete;
    ProjectileSpawnSystem& operator=(const ProjectileSpawnSystem&) = delete;

    ProjectileSpawnSystem(ProjectileSpawnSystem&&) = delete;
    ProjectileSpawnSystem& operator=(ProjectileSpawnSystem&&) = delete;

    void execute(const sf::Time& delta) const;

private:
    EntitySystem<Aircraft::AircraftEntity>& mEntiySystem;
    ProjectileController& mProjectileController;
};