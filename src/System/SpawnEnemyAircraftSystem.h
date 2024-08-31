#pragma once
#include "EntitySystem.h"
#include "ResourceIdentifiers.h"

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class SpawnEnemyAircraftSystem final
{
public:
    explicit SpawnEnemyAircraftSystem(
        EntitySystem<AircraftEntity>& entitySystem,
        const TextureHolder& textures,
        sf::Vector2f position
        ) noexcept;

    void execute(sf::Time delta);

private:
    float spawnInterval(float delta);
    void spawn(float spawnInterval);

    const TextureHolder& mTexture;
    const sf::Vector2f mPosition;

    constexpr static float mMaxSpawnInterval = 1.f;
    constexpr static float mMinSpawnInterval = 0.1f;
    constexpr static float mTotalDecreaseTime = 60.0f;

    constexpr static float mAircraftLeftPadding = 30.0f;
    constexpr static float mAircraftRightPadding = mAircraftLeftPadding * 2;

    EntitySystem<AircraftEntity>& mEntitySystem;

    float mTimeSinceLastSpawn {};
    float mElapsedTime = 0.0f;
};
