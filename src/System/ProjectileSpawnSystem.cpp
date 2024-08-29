#include "ProjectileSpawnSystem.h"

void ProjectileSpawnSystem::update() const
{
    for (auto& aircraft : mAircraftSystem.getEntities())
    {
        if (aircraft->needsToFireProjectile()) {
            const auto& spawnPosition = aircraft->getPosition();
            const auto mPosition = aircraft->getProjectilePosition() == AircraftEntity::Left ? AircraftEntity::Right : AircraftEntity::Left;
            const float xOffset = mPosition == AircraftEntity::Left ? -AircraftEntity::XOffsetAmount : AircraftEntity::XOffsetAmount;
            const auto spawnPos = sf::Vector2f(spawnPosition.x - xOffset, spawnPosition.y - AircraftEntity::YOffsetAmount);

            mProjectileController.spawn(aircraft->getProjectileType(), spawnPos);

            aircraft->resetFireProjectile();
        }
    }
}
