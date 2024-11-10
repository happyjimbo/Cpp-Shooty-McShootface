#pragma once

#include "AircraftEntity.h"
#include "EntitySystem.h"

class ProjectileInitializer;

class ProjectileSpawnSystem {
public:
    explicit ProjectileSpawnSystem(EntitySystem<Aircraft::AircraftEntity>& entiySystem, ProjectileInitializer& projectileController) noexcept;

    explicit ProjectileSpawnSystem() = delete;
    ~ProjectileSpawnSystem() = default;

    ProjectileSpawnSystem(const ProjectileSpawnSystem&) = delete;
    ProjectileSpawnSystem& operator=(const ProjectileSpawnSystem&) = delete;

    ProjectileSpawnSystem(ProjectileSpawnSystem&&) = delete;
    ProjectileSpawnSystem& operator=(ProjectileSpawnSystem&&) = delete;

    void execute(const sf::Time& delta) const;

private:
    EntitySystem<Aircraft::AircraftEntity>& mEntiySystem;
    ProjectileInitializer& mProjectileController;
};