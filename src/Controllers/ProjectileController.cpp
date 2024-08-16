#include "ProjectileController.h"

ProjectileController::ProjectileController(EntitySystem<ProjectileEntity>& entitySystem, const TextureHolder& texture, const sf::FloatRect worldBounds)
: mEntitySystem(entitySystem)
, mTexture(texture)
, mWorldBounds(worldBounds)
, mTimeSinceLastSpawn()
{

}

void ProjectileController::spawn(ProjectileEntity::Type type, const sf::Vector2f spawnPosition) const
{
    auto* projectile = mEntitySystem.createObject(type, mTexture);
    projectile->setPosition(spawnPosition);

    const float speed = type == ProjectileEntity::Type::Player ? -mSpeed : mSpeed;
    projectile->setVelocity(0, speed);
}

void ProjectileController::tick(const sf::Time delta, const float speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(delta, speed);
    checkBounds();
}

void ProjectileController::accelerate(const sf::Time delta, const float speed) const {
    for (auto& projectile : mEntitySystem.getEntities()) {
        projectile->update(delta);
    }
}

void ProjectileController::checkBounds() const {
    for (auto& projectile : mEntitySystem.getEntities()) {
        if (projectile->getPosition().y > mWorldBounds.height ||
            projectile->getPosition().y < 0) {
            removeEntity(projectile);
        }
    }
}

const std::vector<ProjectileEntity*>& ProjectileController::getProjectiles() const {
    return mEntitySystem.getEntities();
}

void ProjectileController::removeEntity(ProjectileEntity* entity) const {
    mEntitySystem.removeObject(entity);
}
