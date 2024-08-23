#pragma once

#include "Entity/AircraftEntity.h"
#include <Resource/ResourceIdentifiers.h>
#include "EntitySystem.h"

class EnemyAircraftController final
{
public:
    explicit EnemyAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
        ProjectileController& projectileController,
        const TextureHolder& textures,
        AircraftEntity::Type type,
        sf::Vector2f position,
        sf::FloatRect worldBounds,
        float scrollSpeed
    ) noexcept;

    void tick(const sf::Time&);

private:
    float spawnInterval(float delta);
    void spawn(float spawnInterval);
    void accelerate(float speed) const;
    void checkBounds() const;

    ProjectileController& mProjectileController;
    const TextureHolder& mTexture;
    AircraftEntity::Type mAircraftType;
    EntitySystem<AircraftEntity>& mEntitySystem;

    float mTimeSinceLastSpawn {};
    float mScrollSpeed;

    sf::Vector2f mStartPosition;
    sf::FloatRect mWorldBounds;

    constexpr static float mEnemyProjectileSpawnSpeed = 3.f;
    constexpr static float mSpeedDivider = 100.f;

    constexpr static float mMaxSpawnInterval = 1.f;
    constexpr static float mMinSpawnInterval = 0.1f;
    constexpr static float mTotalDecreaseTime = 60.0f;
    float mElapsedTime = 0.0f;
};
