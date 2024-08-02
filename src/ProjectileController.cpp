#include "ProjectileController.h"
#include "Category.h"

ProjectileController::ProjectileController(const TextureHolder& texture)
: mProjectiles()
, mTimeSinceLastSpawn()
, mTexture(texture)
, mPosition(Left)
, mSpawnPosition()
{

}

void ProjectileController::spawn(Projectile::Type type) {
    if (mTimeSinceLastSpawn > 0.1f) {
        mTimeSinceLastSpawn = 0;

        std::shared_ptr<Projectile> bullet = std::make_shared<Projectile>(type, mTexture);

        mProjectiles.push_back(bullet.get());

        mPosition = mPosition == Left ? Right : Left;

        float xOffset = mPosition == Left ? -mXOffsetAmount : mXOffsetAmount;

        mSpawnPosition = sf::Vector2f(mSpawnPosition.x - xOffset, mSpawnPosition.y - mYOffsetAmount);

        bullet->setPosition(mSpawnPosition);
        attachChild(std::move(bullet));
    }
}

void ProjectileController::accelerate(float speed) const {
    for (Projectile* projectile : mProjectiles) {
        projectile->accelerate(0.f, speed);
    }
}


void ProjectileController::tick(sf::Time delta, sf::Vector2f position, float speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    mSpawnPosition = position;
    accelerate(speed);
}

unsigned int ProjectileController::getCategory() const {
    return Category::PlayerProjectile;
}

std::vector<Projectile*> ProjectileController::getProjectiles() const {
    return mProjectiles;
}