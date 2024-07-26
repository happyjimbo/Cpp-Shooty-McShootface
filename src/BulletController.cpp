#import "BulletController.h"
#include "Category.h"

BulletController::BulletController(const TextureHolder& textures)
: mBullets()
, mTextures(textures)
{

}

void BulletController::spawnBullet(Bullet::Type type) {
    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(type, mTextures);

    mBullets.push_back(bullet.get());

    bullet->setPosition(mSpawnPosition);
    attachChild(std::move(bullet));
}

void BulletController::accelerateBullets(float speed) {
    for (Bullet* bullet : mBullets)
    {
        bullet->accelerate(0.f, speed);
    }
}


void BulletController::tick(sf::Vector2f position, float speed)
{
    mSpawnPosition = position;
    accelerateBullets(speed);
}

unsigned int BulletController::getCategory() const
{
    return Category::PlayerBullet;
}