#include <gtest/gtest.h>
#include "ProjectileEntity.h"
#include "ProjectileFiringData.h"
#include "SFML/System/Vector2.hpp"

class ProjectileFiringDataTest : public ::testing::Test {
protected:
    ProjectileFiringData data;
};

// Test that updateTimeSinceLastProjectileSpawn works correctly
TEST_F(ProjectileFiringDataTest, UpdateTimeSinceLastProjectileSpawn) {
    data.timeSinceLastProjectileSpawn = 0.0f;
    data.updateTimeSinceLastProjectileSpawn(0.1f);
    EXPECT_FLOAT_EQ(data.timeSinceLastProjectileSpawn, 0.1f);

    data.updateTimeSinceLastProjectileSpawn(0.5f);
    EXPECT_FLOAT_EQ(data.timeSinceLastProjectileSpawn, 0.6f);
}

// Test that getSpawnPos returns the correct offset based on position
TEST_F(ProjectileFiringDataTest, GetSpawnPosLeftPosition) {
    const sf::Vector2f spawnPosition(50.f, 50.f);
    data.position = ProjectileFiringData::Left;

    const sf::Vector2f spawnPos = data.getSpawnPos(spawnPosition);

    EXPECT_FLOAT_EQ(spawnPos.x, 50.f - ProjectileFiringData::XOffsetAmount);
    EXPECT_FLOAT_EQ(spawnPos.y, 50.f - ProjectileFiringData::YOffsetAmount);
}

TEST_F(ProjectileFiringDataTest, GetSpawnPosRightPosition) {
    const sf::Vector2f spawnPosition(50.f, 50.f);
    data.position = ProjectileFiringData::Right;

    const sf::Vector2f spawnPos = data.getSpawnPos(spawnPosition);

    EXPECT_FLOAT_EQ(spawnPos.x, 50.f + ProjectileFiringData::XOffsetAmount);
    EXPECT_FLOAT_EQ(spawnPos.y, 50.f - ProjectileFiringData::YOffsetAmount);
}

// Test that canFire returns true only if the firing conditions are met
TEST_F(ProjectileFiringDataTest, CanFireConditions) {
    data.needsToFireProjectile = true;
    data.timeSinceLastProjectileSpawn = 0.0f;
    data.speed = 1.0f;

    // Can't fire yet since time is less than speed
    EXPECT_FALSE(data.canFire());

    // Simulate time passing
    data.timeSinceLastProjectileSpawn = 1.1f;
    EXPECT_TRUE(data.canFire());
}

// Test that reset sets timeSinceLastProjectileSpawn and needsToFireProjectile correctly
TEST_F(ProjectileFiringDataTest, Reset) {
    data.timeSinceLastProjectileSpawn = 1.5f;
    data.needsToFireProjectile = true;

    data.reset();

    EXPECT_FLOAT_EQ(data.timeSinceLastProjectileSpawn, 0.0f);
    EXPECT_FALSE(data.needsToFireProjectile);
}