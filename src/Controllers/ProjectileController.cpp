#include "ProjectileController.h"

ProjectileController::ProjectileController(EntitySystem<ProjectileEntity>& entitySystem, const TextureHolder& texture, const sf::FloatRect worldBounds)
: mEntitySystem(entitySystem)
, mTexture(texture)
, mWorldBounds(worldBounds)
{
    mEntitySystem.prePool(20);
}

void ProjectileController::spawn(ProjectileEntity::Type type, const sf::Vector2f spawnPosition) const
{
    auto* projectile = mEntitySystem.createObject(type, mTexture);
    projectile->setPosition(spawnPosition);

    const float speed = type == ProjectileEntity::Type::Player ? -sSpeed : sSpeed;
    projectile->setVelocity(0, speed);
}

void ProjectileController::tick(const sf::Time delta) const {
    for (auto& projectile : mEntitySystem.getEntities()) {
        projectile->update(delta);
    }
}