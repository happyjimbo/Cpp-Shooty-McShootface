#pragma once
#include "EntitySystem.h"
#include "ResourceIdentifiers.h"

namespace Aircraft { class AircraftEntity; }

class SpawnEnemyAircraftSystem final
{
public:
    explicit SpawnEnemyAircraftSystem(
        EntitySystem<Aircraft::AircraftEntity>& entitySystem,
        const TextureHolder& textures,
        ShaderHolder& shaders,
        float screenWidth
        ) noexcept;

    ~SpawnEnemyAircraftSystem() = default;
    explicit SpawnEnemyAircraftSystem() = delete;

    SpawnEnemyAircraftSystem(const SpawnEnemyAircraftSystem&) = delete;
    SpawnEnemyAircraftSystem& operator=(const SpawnEnemyAircraftSystem&) = delete;

    SpawnEnemyAircraftSystem(SpawnEnemyAircraftSystem&&) = delete;
    SpawnEnemyAircraftSystem& operator=(SpawnEnemyAircraftSystem&&) = delete;

    void execute(const sf::Time& delta);

private:
    float spawnInterval(float delta);
    void spawn(float spawnInterval);

    EntitySystem<Aircraft::AircraftEntity>& mEntitySystem;

    const TextureHolder& mTextures;
    ShaderHolder& mShaders;
    const sf::Vector2f mPosition;

    float mTimeSinceLastSpawn {};
    float mElapsedTime = 0.0f;
};
