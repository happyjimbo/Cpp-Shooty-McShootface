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
    accelerate(mScrollSpeed / mSpeedDivider);

    for (const auto& aircraft : mEntitySystem.getEntities())
    {
        aircraft->update(delta);
        aircraft->triggerProjectile(ProjectileEntity::Enemy, mEnemyProjectileSpawnSpeed);
    }
}

void EnemyAircraftController::accelerate(float const speed) const
{
    for (const auto& aircraft : mEntitySystem.getEntities())
    {
        const float x = aircraft->getPosition().x > mPlayer.getPosition().x ?  -xSpeed : xSpeed;
        aircraft->accelerate(x, -speed);
    }
}