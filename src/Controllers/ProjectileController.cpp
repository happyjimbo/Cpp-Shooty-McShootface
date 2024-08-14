#include "ProjectileController.h"

ProjectileController::ProjectileController(EntitySystem<ProjectileEntity>& entitySystem, const TextureHolder& texture, const sf::FloatRect worldBounds)
: mEntitySystem(entitySystem)
, mTexture(texture)
, mWorldBounds(worldBounds)
, mTimeSinceLastSpawn()
, mPosition(Left)
{

}

void ProjectileController::spawn(ProjectileEntity::Type type, const sf::Vector2f spawnPosition)
{
    if (mTimeSinceLastSpawn > 0.1f)
    {
        mTimeSinceLastSpawn = 0;

        auto* projectile = mEntitySystem.createObject(type, mTexture);

        mPosition = mPosition == Left ? Right : Left;
        const float xOffset = mPosition == Left ? -mXOffsetAmount : mXOffsetAmount;
        const auto spawnPos = sf::Vector2f(spawnPosition.x - xOffset, spawnPosition.y - mYOffsetAmount);
        projectile->setPosition(spawnPos);
        projectile->setVelocity(0, -1000.f); // remove hardcode -100
    }
}

void ProjectileController::tick(const sf::Time delta, const float speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(delta, speed);
    checkBounds();
}

void ProjectileController::accelerate(const sf::Time delta, const float speed) const {
    for (auto& projectile : mEntities) {
        projectile->accelerate(0.f, speed);
        projectile->update(delta);
    }
}

void ProjectileController::checkBounds() const {
    for (auto* projectile : mEntities) {
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
