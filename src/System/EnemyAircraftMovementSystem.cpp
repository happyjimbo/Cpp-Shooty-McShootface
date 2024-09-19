#include "EnemyAircraftMovementSystem.h"
#include "ProjectileEntity.h"
#include "AircraftEntity.h"

namespace
{
    constexpr float SpeedDivider = 100.f;
    constexpr float EnemyProjectileSpawnSpeed = 1.f;
    constexpr float SpeedX = 0.05f;
}

EnemyAircraftMovementSystem::EnemyAircraftMovementSystem(EntitySystem<AircraftEntity>& entitySystem, const AircraftEntity& player, const float scrollSpeed) noexcept
: mEntitySystem(entitySystem)
, mPlayer(player)
, mScrollSpeed(scrollSpeed)
{

}

void EnemyAircraftMovementSystem::execute(const sf::Time& delta)
{
    mTimeSinceLastSpawn += delta.asSeconds();
    const float speed = mScrollSpeed / SpeedDivider;

    for (const auto& aircraft : mEntitySystem.getEntities())
    {
        const float x = aircraft->getPosition().x > mPlayer.getPosition().x ?  -SpeedX : SpeedX;

        aircraft->accelerate(x, -speed);
        aircraft->triggerProjectile(ProjectileEntity::Enemy, EnemyProjectileSpawnSpeed);
    }
}