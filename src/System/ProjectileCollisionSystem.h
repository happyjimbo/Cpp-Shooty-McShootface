#pragma once

#include "EntitySystem.h"
#include "AircraftEntity.h"

class ExplosionInitializer;

class GuiInitializer;
class ProjectileEntity;

class ProjectileCollisionSystem final
{
public:
    explicit ProjectileCollisionSystem(
        EntitySystem<ProjectileEntity>& projectileEntites,
        EntitySystem<Aircraft::AircraftEntity>& enemyAircraftEntities,
        Aircraft::AircraftEntity& player,
        ExplosionInitializer& explosionInitalizer,
        GuiInitializer& scoreInitalizer
    );

    explicit ProjectileCollisionSystem() = delete;
    ~ProjectileCollisionSystem() = default;

    ProjectileCollisionSystem(const ProjectileCollisionSystem&) = delete;
    ProjectileCollisionSystem& operator=(const ProjectileCollisionSystem&) = delete;

    ProjectileCollisionSystem(ProjectileCollisionSystem&&) = delete;
    ProjectileCollisionSystem& operator=(ProjectileCollisionSystem&&) = delete;

    void execute() const;

private:

    void enemyHit(ProjectileEntity* projectile, Aircraft::AircraftEntity* aircraft) const;
    void playerHit(ProjectileEntity* projectile) const;

    template<std::invocable CollisionHandler>
    static void checkCollision(const ProjectileEntity* projectile, const Aircraft::AircraftEntity* target, float collisionSqr, CollisionHandler onCollision);

    EntitySystem<ProjectileEntity>& mProjectileEntites;
    EntitySystem<Aircraft::AircraftEntity>& mEnemyAircraftEntities;
    Aircraft::AircraftEntity& mPlayer;
    ExplosionInitializer& mExplosionInitalizer;
    GuiInitializer& mScoreInitalizer;
};