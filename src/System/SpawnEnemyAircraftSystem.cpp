#include "SpawnEnemyAircraftSystem.h"

#include "AircraftEntity.h"
#include "EntitySystem.h"

SpawnEnemyAircraftSystem::SpawnEnemyAircraftSystem(
    EntitySystem<AircraftEntity>& entitySystem,
    const TextureHolder& textures,
    const float screenWidth
    ) noexcept
    : mEntitySystem(entitySystem)
    , mTexture(textures)
    , mPosition(screenWidth, sStartYPos)
{

}

void SpawnEnemyAircraftSystem::execute(const sf::Time delta)
{
    mTimeSinceLastSpawn += delta.asSeconds();

    const float interval = spawnInterval(delta.asSeconds());
    spawn(interval);
}

float SpawnEnemyAircraftSystem::spawnInterval(const float delta)
{
    mElapsedTime += delta;

    if (mElapsedTime > sTotalDecreaseTime)
    {
        mElapsedTime = sTotalDecreaseTime;
    }

    const float timeRatio = mElapsedTime / sTotalDecreaseTime;
    return sMinSpawnInterval + (sMaxSpawnInterval - sMinSpawnInterval) * (sMaxSpawnInterval - timeRatio);
}

void SpawnEnemyAircraftSystem::spawn(const float spawnInterval)
{
    if (mTimeSinceLastSpawn > spawnInterval)
    {
        mTimeSinceLastSpawn = 0;

        const int x = sAircraftLeftPadding + rand() % static_cast<int>(mPosition.x - sAircraftRightPadding);
        const auto startPosition = sf::Vector2f(x, mPosition.y);

        auto* aircraft = mEntitySystem.createObject(AircraftEntity::Type::Raptor, mTexture);
        aircraft->setPosition(startPosition);
    }
}