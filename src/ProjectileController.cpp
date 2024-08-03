#include "ProjectileController.h"
#include "Category.h"
#include "Logger.h"

ProjectileController::ProjectileController(const TextureHolder& texture, const sf::FloatRect worldBounds)
: mProjectiles()
, mTexture(texture)
, mWorldBounds(worldBounds)
, mSpawnPosition()
, mTimeSinceLastSpawn()
, mPosition(Left)
{

}

void ProjectileController::spawn(Projectile::Type type) {
    if (mTimeSinceLastSpawn > 0.1f) {
        mTimeSinceLastSpawn = 0;

        auto bullet = std::make_shared<Projectile>(type, mTexture);

        mProjectiles.push_back(bullet.get());

        mPosition = mPosition == Left ? Right : Left;

        float xOffset = mPosition == Left ? -mXOffsetAmount : mXOffsetAmount;

        mSpawnPosition = sf::Vector2f(mSpawnPosition.x - xOffset, mSpawnPosition.y - mYOffsetAmount);

        bullet->setPosition(mSpawnPosition);
        attachChild(bullet);
    }
}

void ProjectileController::tick(const sf::Time delta, const sf::Vector2f position, const float speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    mSpawnPosition = position;
    accelerate(speed);
    checkBounds();
}

void ProjectileController::accelerate(float speed) const {
    for (Projectile* projectile : mProjectiles) {
        projectile->accelerate(0.f, speed);
    }
}

void ProjectileController::checkBounds() {
    for (const Projectile* projectile : mProjectiles) {
        if (projectile->getPosition().y > mWorldBounds.height ||
            projectile->getPosition().y < 0) {
            destroy(*projectile);
        }
    }
}


unsigned int ProjectileController::getCategory() const {
    return Category::PlayerProjectile;
}

std::vector<Projectile*> ProjectileController::getProjectiles() const {
    return mProjectiles;
}

void ProjectileController::destroy(const Projectile& projectile) {
    auto it = std::find(mProjectiles.begin(), mProjectiles.end(), &projectile);
    if (it != mProjectiles.end()) {
        mProjectiles.erase(it);
        detachChild(projectile);
    }
}
