#pragma once

#include "ProjectileEntity.h"
#include "SFML/System/Vector2.hpp"

struct ProjectileFiringData {

    float speed {};
    float timeSinceLastProjectileSpawn {};
    bool needsToFireProjectile {};

    ProjectileEntity::Type projectileType {};
    enum Position { Left, Right } position = Left;
    static constexpr float XOffsetAmount = 15.f;
    static constexpr float YOffsetAmount = 5.f;

    void updateTimeSinceLastProjectileSpawn(const float deltaTime) noexcept {
        timeSinceLastProjectileSpawn += deltaTime;
    }

    sf::Vector2f getSpawnPos(const sf::Vector2f& spawnPosition) const
    {
        const auto pos = position == Left ? Right : Left;
        const float xOffset = pos == Left ? -XOffsetAmount : XOffsetAmount;
        const auto spawnPos = sf::Vector2f(spawnPosition.x - xOffset, spawnPosition.y - YOffsetAmount);
        return spawnPos;
    }

    bool canFire() const noexcept
    {
        return needsToFireProjectile && timeSinceLastProjectileSpawn > speed;
    }

    void reset() noexcept
    {
        timeSinceLastProjectileSpawn = 0;
        needsToFireProjectile = false;
    }
};
