#include "SpawnEnemyAircraftSystem.h"

#include "AircraftEntity.h"
#include "EntitySystem.h"

namespace
{
    constexpr float MaxSpawnInterval = 0.6f;
    constexpr float MinSpawnInterval = 0.3f;
    constexpr float TotalDecreaseTime = 60.0f;

    constexpr float AircraftLeftPadding = 30.0f;
    constexpr float AircraftRightPadding = AircraftLeftPadding * 2;

    constexpr float StartYPos = -100;
    constexpr int EnemyHealth = 1;
}

SpawnEnemyAircraftSystem::SpawnEnemyAircraftSystem(
    EntitySystem<AircraftEntity>& entitySystem,
    const TextureHolder& textures,
    const float screenWidth
    ) noexcept
    : mEntitySystem(entitySystem)
    , mTexture(textures)
    , mPosition(screenWidth, StartYPos)
{

}

void SpawnEnemyAircraftSystem::execute(const sf::Time& delta)
{
    mTimeSinceLastSpawn += delta.asSeconds();

    const float interval = spawnInterval(delta.asSeconds());
    spawn(interval);
}

float SpawnEnemyAircraftSystem::spawnInterval(const float delta)
{
    mElapsedTime += delta;

    if (mElapsedTime > TotalDecreaseTime)
    {
        mElapsedTime = TotalDecreaseTime;
    }

    const float timeRatio = mElapsedTime / TotalDecreaseTime;
    return MinSpawnInterval + (MaxSpawnInterval - MinSpawnInterval) * (MaxSpawnInterval - timeRatio);
}

void SpawnEnemyAircraftSystem::spawn(const float spawnInterval)
{
    if (mTimeSinceLastSpawn > spawnInterval)
    {
        mTimeSinceLastSpawn = 0;

        const int x = AircraftLeftPadding + rand() % static_cast<int>(mPosition.x - AircraftRightPadding);
        const auto startPosition = sf::Vector2f(x, mPosition.y);

        auto* aircraft = mEntitySystem.createObject(AircraftEntity::Type::Raptor, mTexture, EnemyHealth);
        aircraft->setPosition(startPosition);
    }
}