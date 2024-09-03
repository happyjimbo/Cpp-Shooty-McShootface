#include "EnemyAircraftController.h"

EnemyAircraftController::EnemyAircraftController (
    EntitySystem<AircraftEntity>& entitySystem,
    const AircraftEntity& player,
    const float scrollSpeed
    ) noexcept
      : mEntitySystem(entitySystem)
      , mPlayer(player)
      , mScrollSpeed(scrollSpeed)
{
    mEntitySystem.prePool(20);
}

void EnemyAircraftController::tick(const sf::Time& delta)
{
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(mScrollSpeed / sSpeedDivider);

    for (const auto& aircraft : mEntitySystem.getEntities())
    {
        aircraft->triggerProjectile(ProjectileEntity::Enemy, sEnemyProjectileSpawnSpeed);
    }
}

void EnemyAircraftController::accelerate(float const speed) const
{
    for (const auto& aircraft : mEntitySystem.getEntities())
    {
        const float x = aircraft->getPosition().x > mPlayer.getPosition().x ?  -sSpeedX : sSpeedX;
        aircraft->accelerate(x, -speed);
    }
}