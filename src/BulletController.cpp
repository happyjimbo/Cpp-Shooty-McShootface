#import "BulletController.h"
#include "Category.h"
#include "Logger.h"

BulletController::BulletController(const TextureHolder& textures)
: mBullets()
, mTextures(textures)
, spawnPosition(BulletController::Position::Left)
{

}

void BulletController::spawnBullet(Bullet::Type type) {
    if (mTimeSinceLastSpawn > 0.1f) {
        mTimeSinceLastSpawn = 0;

        std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(type, mTextures);

        mBullets.push_back(bullet.get());

        spawnPosition = spawnPosition == BulletController::Position::Left ?
                BulletController::Position::Right :
                BulletController::Position::Left;

        float xOffset = spawnPosition == BulletController::Position::Left ? -15.f : 15.f;

        mSpawnPosition = sf::Vector2f(mSpawnPosition.x - xOffset, mSpawnPosition.y - 5.f);

        bullet->setPosition(mSpawnPosition);
        attachChild(std::move(bullet));
    }
}

void BulletController::accelerateBullets(float speed) {
    for (Bullet* bullet : mBullets)
    {
        bullet->accelerate(0.f, speed);
    }
}


void BulletController::tick(sf::Time delta, sf::Vector2f position, float speed)
{
    mTimeSinceLastSpawn += delta.asSeconds();
    mSpawnPosition = position;
    accelerateBullets(speed);
}

unsigned int BulletController::getCategory() const
{
    return Category::PlayerBullet;
}