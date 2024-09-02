#pragma once

#include "EntitySystem.h"
#include "AircraftEntity.h"
#include <concepts>

class ExplosionController;
using Aircraft::AircraftEntity;

class ScoreController;
class ProjectileEntity;

class ProjectileCollisionSystem final
{
public:
    explicit ProjectileCollisionSystem(
        EntitySystem<ProjectileEntity>& projectileEntites,
        EntitySystem<AircraftEntity>& enemyAircraftEntities,
        EntitySystem<AircraftEntity>& playerAircraftEntities,
        const AircraftEntity& player,
        ExplosionController& explosionController,
        ScoreController& scoreController
    );
    void execute() const;

private:

    void collided(ProjectileEntity* projectile, AircraftEntity* aircraft) const;

    template<std::invocable CollisionHandler>
    static void checkCollision(const ProjectileEntity* projectile, const AircraftEntity* target, float collisionSqr, CollisionHandler onCollision);

    static float getSquareMagnitude(const sf::Vector2f& pos1, const sf::Vector2f& pos2);

    EntitySystem<ProjectileEntity>& mProjectileEntites;
    EntitySystem<AircraftEntity>& mEnemyAircraftEntities;
    EntitySystem<AircraftEntity>& mPlayerAircraftEntities;
    const AircraftEntity& mPlayer;
    ExplosionController& mExplosionController;
    ScoreController& mScoreController;

    constexpr static float sCollisionThreshold = 30.f;
};