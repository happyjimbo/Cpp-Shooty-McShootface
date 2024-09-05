#include "ProjectileSpawnSystem.h"
#include "ProjectileController.h"

using Aircraft::AircraftEntity;

void ProjectileSpawnSystem::execute(const sf::Time& delta) const
{
    for (auto* aircraft : mEntiySystem.getEntities())
    {
        auto& firingData = aircraft->getProjectileFiringData();

        firingData.updateTimeSinceLastProjectileSpawn(delta.asSeconds());
        if (firingData.canFire())
        {
            const auto& pos = aircraft->getPosition();
            mProjectileController.spawn(firingData.projectileType, firingData.getSpawnPos(pos));
            firingData.reset();
        }
    }
}
