#include "ProjectileSpawnSystem.h"
#include "ProjectileInitializer.h"

using Aircraft::AircraftEntity;

ProjectileSpawnSystem::ProjectileSpawnSystem(EntitySystem<AircraftEntity>& entiySystem, ProjectileInitializer& projectileInitalizer) noexcept
        : mEntiySystem(entiySystem), mProjectileInitalizer(projectileInitalizer)
{
}

void ProjectileSpawnSystem::execute(const sf::Time& delta) const
{
    for (auto* aircraft : mEntiySystem.getEntities())
    {
        auto& firingData = aircraft->getProjectileFiringData();

        firingData.updateTimeSinceLastProjectileSpawn(delta.asSeconds());
        if (firingData.canFire())
        {
            const auto& pos = aircraft->getPosition();
            mProjectileInitalizer.spawn(firingData.projectileType, firingData.getSpawnPos(pos));
            firingData.reset();
        }
    }
}
