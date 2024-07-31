#import "ProjectileController.h"
#include "Category.h"
#include "Logger.h"

ProjectileController::ProjectileController(const TextureHolder& texture)
: mProjectiles()
, mTexture(texture)
, mPosition(ProjectileController::Position::Left)
{

}

void ProjectileController::spawn(Projectile::Type type) {
    if (mTimeSinceLastSpawn > 0.1f) {
        mTimeSinceLastSpawn = 0;

        std::unique_ptr<Projectile> bullet = std::make_unique<Projectile>(type, mTexture);

        mProjectiles.push_back(bullet.get());

        mPosition = mPosition == ProjectileController::Position::Left ?
                    ProjectileController::Position::Right :
                    ProjectileController::Position::Left;

        float xOffset = mPosition == ProjectileController::Position::Left ? -mXOffsetAmount : mXOffsetAmount;

        mSpawnPosition = sf::Vector2f(mSpawnPosition.x - xOffset, mSpawnPosition.y - mYOffsetAmount);

        bullet->setPosition(mSpawnPosition);
        attachChild(std::move(bullet));
    }
}

void ProjectileController::accelerate(float speed) {
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