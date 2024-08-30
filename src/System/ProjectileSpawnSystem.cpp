#include "ProjectileSpawnSystem.h"

using Aircraft::AircraftEntity;

void ProjectileSpawnSystem::update(const sf::Time delta) const
{
    for (auto* aircraft : mAircraftSystem.getEntities())
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
