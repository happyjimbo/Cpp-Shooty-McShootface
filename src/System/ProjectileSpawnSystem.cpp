#include "ProjectileSpawnSystem.h"

using Aircraft::AircraftEntity;
using Aircraft::ProjectileFiringData;

void ProjectileSpawnSystem::update(const sf::Time delta) const
{
    for (auto& aircraft : mAircraftSystem.getEntities())
    {
        auto& firingData = aircraft->getProjectileFiringData();

        firingData.mTimeSinceLastProjectileSpawn += delta.asSeconds();
        if (firingData.needsToFireProjectile &&
            firingData.mTimeSinceLastProjectileSpawn > firingData.speed)
        {
            const auto& spawnPosition = aircraft->getPosition();
            const auto position = firingData.position == ProjectileFiringData::Left ? ProjectileFiringData::Right : ProjectileFiringData::Left;
            const float xOffset = position == ProjectileFiringData::Left ? -firingData.XOffsetAmount : firingData.XOffsetAmount;
            const auto spawnPos = sf::Vector2f(spawnPosition.x - xOffset, spawnPosition.y - firingData.YOffsetAmount);

            mProjectileController.spawn(firingData.projectileType, spawnPos);

            firingData.reset();
        }
    }
}
