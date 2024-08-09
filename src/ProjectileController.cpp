#include "ProjectileController.h"
#include "EntitySystem.h"

ProjectileController::ProjectileController(EntitySystem& entitySystem, const TextureHolder& texture, const sf::FloatRect worldBounds)
: mProjectiles()
, mEntitySystem(entitySystem)
, mTexture(texture)
, mWorldBounds(worldBounds)
, mTimeSinceLastSpawn()
, mPosition(Left)
{

}

void ProjectileController::spawn(Projectile::Type type, const sf::Vector2f spawnPosition) {
    if (mTimeSinceLastSpawn > 0.1f) {
        mTimeSinceLastSpawn = 0;

        const auto projectile = std::make_shared<Projectile>(type, mTexture);

        mPosition = mPosition == Left ? Right : Left;
        const float xOffset = mPosition == Left ? -mXOffsetAmount : mXOffsetAmount;
        const auto spawnPos = sf::Vector2f(spawnPosition.x - xOffset, spawnPosition.y - mYOffsetAmount);
        projectile->setPosition(spawnPos);

        mProjectiles.push_back(projectile);

        mEntitySystem.addObject(projectile);
    }
}

void ProjectileController::tick(const sf::Time delta, const float speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(speed);
    checkBounds();
}

void ProjectileController::accelerate(float speed) const {
    for (auto& projectile : mProjectiles) {
        projectile->accelerate(0.f, speed);
    }
}

void ProjectileController::checkBounds() {

    std::vector<std::shared_ptr<Projectile>> toDelete;

    for (const auto& projectile : mProjectiles) {
        if (projectile->getPosition().y > mWorldBounds.height ||
            projectile->getPosition().y < 0) {
            toDelete.push_back(projectile);
        }
    }

    for (auto& projectile : toDelete) {
        destroy(projectile);
    }
}


std::vector<std::shared_ptr<Projectile>>& ProjectileController::getProjectiles() {
    return mProjectiles;
}

void ProjectileController::destroy(std::shared_ptr<Projectile>& projectile) {
    auto found = std::find_if(mProjectiles.begin(), mProjectiles.end(),
        [&](const std::shared_ptr<Projectile>& p) {
           return p.get() == projectile.get();
        });
    if (found != mProjectiles.end()) {
        mProjectiles.erase(found);
        mEntitySystem.removeObject(projectile);
    }
}
