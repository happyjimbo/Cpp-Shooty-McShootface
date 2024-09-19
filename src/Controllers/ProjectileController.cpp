#include "ProjectileController.h"

namespace
{
    constexpr float Speed = 500.f;
    constexpr int PrePoolAmount = 20;
}

ProjectileController::ProjectileController(EntitySystem<ProjectileEntity>& entitySystem, const TextureHolder& texture, const sf::FloatRect worldBounds)
: mEntitySystem(entitySystem)
, mTexture(texture)
, mWorldBounds(worldBounds)
{
    mEntitySystem.prePool(PrePoolAmount);
}

void ProjectileController::spawn(ProjectileEntity::Type type, const sf::Vector2f spawnPosition) const
{
    auto* projectile = mEntitySystem.createObject(type, mTexture);
    projectile->setPosition(spawnPosition);

    const float speed = type == ProjectileEntity::Type::Player ? -Speed : Speed;
    projectile->setVelocity(0, speed);
}