#include "EnemyAircraftMovementSystem.h"
#include "ProjectileEntity.h"
#include "AircraftEntity.h"

EnemyAircraftMovementSystem::EnemyAircraftMovementSystem(EntitySystem<AircraftEntity>& entitySystem, const AircraftEntity& player, const float scrollSpeed) noexcept
: mEntitySystem(entitySystem)
, mPlayer(player)
, mScrollSpeed(scrollSpeed)
{

}

void EnemyAircraftMovementSystem::execute(const sf::Time& delta)
{
    mTimeSinceLastSpawn += delta.asSeconds();
    const float speed = mScrollSpeed / sSpeedDivider;

    for (const auto& aircraft : mEntitySystem.getEntities())
    {
        const float x = aircraft->getPosition().x > mPlayer.getPosition().x ?  -sSpeedX : sSpeedX;

        aircraft->accelerate(x, -speed);
        aircraft->triggerProjectile(ProjectileEntity::Enemy, sEnemyProjectileSpawnSpeed);
    }
}