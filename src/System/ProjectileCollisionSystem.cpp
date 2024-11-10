#include "ProjectileCollisionSystem.h"
#include "ExplosionInitializer.h"
#include "GuiInitializer.h"
#include "SquareMagnitude.h"

using Aircraft::AircraftEntity;

namespace
{
    constexpr float CollisionThreshold = 30.f;
}

ProjectileCollisionSystem::ProjectileCollisionSystem(
    EntitySystem<ProjectileEntity>& projectileEntites,
    EntitySystem<AircraftEntity>& enemyAircraftEntities,
    AircraftEntity& player,
    ExplosionInitializer& explosionController,
    GuiInitializer& scoreController)
: mProjectileEntites(projectileEntites)
, mEnemyAircraftEntities(enemyAircraftEntities)
, mPlayer(player)
, mExplosionController(explosionController)
, mScoreController(scoreController)
{

}

void ProjectileCollisionSystem::execute() const
{
    const auto& projectiles = mProjectileEntites.getEntities();
    const auto& enemyAircraft = mEnemyAircraftEntities.getEntities();

    constexpr float collisionSqr = CollisionThreshold * CollisionThreshold;

    for(const auto& projectile : projectiles)
    {
        if (projectile->getType() == ProjectileEntity::Enemy)
        {
            checkCollision(projectile, &mPlayer, collisionSqr, [this, &projectile]() -> void {
                playerHit(projectile);
            });
        }

        if (projectile->getType() == ProjectileEntity::Player)
        {
            for (const auto& enemy : enemyAircraft)
            {
                checkCollision(projectile, enemy, collisionSqr, [this, &projectile, &enemy]() -> void {
                    enemyHit(projectile, enemy);
                });
            }
        }
    }
}

template<std::invocable CollisionHandler>
void ProjectileCollisionSystem::checkCollision(const ProjectileEntity* projectile, const AircraftEntity* target, const float collisionSqr, const CollisionHandler onCollision)
{
    const auto projectilePos = projectile->getPosition();
    const auto targetPos = target->getPosition();
    const float distanceSqrt = getSquareMagnitude(projectilePos, targetPos);

    if (distanceSqrt < collisionSqr) {
        onCollision();
    }
}

void ProjectileCollisionSystem::playerHit(ProjectileEntity* projectile) const
{
    mPlayer.getAircraftData().hit();
    mScoreController.playerHit();

    mProjectileEntites.removeObject(projectile);
    mExplosionController.spawn(mPlayer.getPosition(), Textures::PlayerExplosion, Sounds::Explosion1);
}

void ProjectileCollisionSystem::enemyHit(ProjectileEntity* projectile, AircraftEntity* aircraft) const
{
    aircraft->getAircraftData().hit();
    mExplosionController.spawn(aircraft->getPosition(), Textures::Explosion, Sounds::Explosion2);

    if (aircraft->getAircraftData().destroyed())
    {
        mProjectileEntites.removeObject(projectile);
        mEnemyAircraftEntities.removeObject(aircraft);

        mScoreController.increaseScore();
    }
}