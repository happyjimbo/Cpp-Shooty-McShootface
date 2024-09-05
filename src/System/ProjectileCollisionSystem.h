#pragma once

#include "EntitySystem.h"
#include "AircraftEntity.h"

class ExplosionController;
using Aircraft::AircraftEntity;

class GuiController;
class ProjectileEntity;

class ProjectileCollisionSystem final
{
public:
    explicit ProjectileCollisionSystem(
        EntitySystem<ProjectileEntity>& projectileEntites,
        EntitySystem<AircraftEntity>& enemyAircraftEntities,
        AircraftEntity& player,
        ExplosionController& explosionController,
        GuiController& scoreController
    );

    explicit ProjectileCollisionSystem() = delete;
    ~ProjectileCollisionSystem() = default;

    ProjectileCollisionSystem(const ProjectileCollisionSystem&) = delete;
    ProjectileCollisionSystem& operator=(const ProjectileCollisionSystem&) = delete;

    ProjectileCollisionSystem(ProjectileCollisionSystem&&) = delete;
    ProjectileCollisionSystem& operator=(ProjectileCollisionSystem&&) = delete;

    void execute() const;

private:

    void enemyHit(ProjectileEntity* projectile, AircraftEntity* aircraft) const;
    void playerHit(ProjectileEntity* projectile) const;

    template<std::invocable CollisionHandler>
    static void checkCollision(const ProjectileEntity* projectile, const AircraftEntity* target, float collisionSqr, CollisionHandler onCollision);

    EntitySystem<ProjectileEntity>& mProjectileEntites;
    EntitySystem<AircraftEntity>& mEnemyAircraftEntities;
    AircraftEntity& mPlayer;
    ExplosionController& mExplosionController;
    GuiController& mScoreController;

    constexpr static float sCollisionThreshold = 30.f;
};