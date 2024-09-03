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
        float screenWidth
        ) noexcept;

    void execute(sf::Time delta);

private:
    float spawnInterval(float delta);
    void spawn(float spawnInterval);

    EntitySystem<AircraftEntity>& mEntitySystem;

    const TextureHolder& mTexture;
    const sf::Vector2f mPosition;

    constexpr static float sMaxSpawnInterval = 1.f;
    constexpr static float sMinSpawnInterval = 0.1f;
    constexpr static float sTotalDecreaseTime = 60.0f;

    constexpr static float sAircraftLeftPadding = 30.0f;
    constexpr static float sAircraftRightPadding = sAircraftLeftPadding * 2;

    constexpr static float sStartYPos = -100;
    constexpr static int sEnemyHealth = 1;

    float mTimeSinceLastSpawn {};
    float mElapsedTime = 0.0f;
};
