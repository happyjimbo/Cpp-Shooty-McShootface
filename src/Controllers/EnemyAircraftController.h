#pragma once

#include "AircraftEntity.h"
#include "ResourceIdentifiers.h"
#include "EntitySystem.h"

using Aircraft::AircraftEntity;

class EnemyAircraftController final
{
public:
    explicit EnemyAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
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

    constexpr static float mAircraftLeftPadding = 30.0f;
    constexpr static float mAircraftRightPadding = mAircraftLeftPadding * 2;

    float mElapsedTime = 0.0f;
};
