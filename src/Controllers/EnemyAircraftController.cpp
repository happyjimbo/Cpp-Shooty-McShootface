#include "EnemyAircraftController.h"

EnemyAircraftController::EnemyAircraftController (
    EntitySystem<AircraftEntity>& entitySystem,
    ProjectileController& projectileController,
    const TextureHolder& textures,
    const AircraftEntity::Type type,
    const sf::Vector2f position,
    const sf::FloatRect worldBounds,
    const float scrollSpeed
    ) noexcept
      : mEntitySystem(entitySystem)
      , mProjectileController(projectileController)
      , mTexture(textures)
      , mAircraftType(type)
      , mStartPosition(position)
      , mWorldBounds(worldBounds)
      , mScrollSpeed(scrollSpeed)
{

}

void EnemyAircraftController::tick(const sf::Time& delta)
{
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(mScrollSpeed / mSpeedDivider);

    const float interval = spawnInterval(delta.asSeconds());
    spawn(interval);

    checkBounds();

    for (const auto& aircraft : mEntitySystem.getEntities())
    {
        aircraft->update(delta);
        aircraft->triggerProjectile(ProjectileEntity::Enemy, mEnemyProjectileSpawnSpeed);
    }
}

float EnemyAircraftController::spawnInterval(const float delta)
{
    mElapsedTime += delta;

    if (mElapsedTime > mTotalDecreaseTime)
    {
        mElapsedTime = mTotalDecreaseTime;
    }

    const float timeRatio = mElapsedTime / mTotalDecreaseTime;
    return mMinSpawnInterval + (mMaxSpawnInterval - mMinSpawnInterval) * (mMaxSpawnInterval - timeRatio);
}

void EnemyAircraftController::spawn(const float spawnInterval)
{
    if (mTimeSinceLastSpawn > spawnInterval)
    {
        mTimeSinceLastSpawn = 0;

        auto* aircraft = mEntitySystem.createObject(mProjectileController, mAircraftType, mTexture);

        const int x = rand() % static_cast<int>(mStartPosition.x);

        const auto startPosition = sf::Vector2f(x, mStartPosition.y);
        aircraft->setPosition(startPosition);
        aircraft->setRotation(180);
    }
}

void EnemyAircraftController::checkBounds() const
{
    for (auto* aircraft : mEntitySystem.getEntities())
    {
        if (aircraft->getPosition().y > mWorldBounds.height)
        {
            mEntitySystem.removeObject(aircraft);
        }
    }
}

void EnemyAircraftController::accelerate(float const speed) const
{
    for (const auto& aircraft : mEntitySystem.getEntities())
    {
        aircraft->accelerate(0.f, -speed);
    }
}