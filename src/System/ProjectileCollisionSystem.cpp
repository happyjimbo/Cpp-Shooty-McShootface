#include "ProjectileCollisionSystem.h"

#include <iostream>

#include "ExplosionController.h"
#include "GuiController.h"

ProjectileCollisionSystem::ProjectileCollisionSystem(
    EntitySystem<ProjectileEntity>& projectileEntites,
    EntitySystem<AircraftEntity>& enemyAircraftEntities,
    AircraftEntity& player,
    ExplosionController& explosionController,
    GuiController& scoreController)
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

    constexpr float collisionSqr = sCollisionThreshold * sCollisionThreshold;

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

float ProjectileCollisionSystem::getSquareMagnitude(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
    const float dx = pos1.x - pos2.x;
    const float dy = pos1.y - pos2.y;
    return (dx * dx) + (dy * dy);
}

void ProjectileCollisionSystem::playerHit(ProjectileEntity* projectile) const
{
    mPlayer.hit();
    mScoreController.playerHit();

    mProjectileEntites.removeObject(projectile);
    mExplosionController.spawn(mPlayer.getPosition(), Textures::PlayerExplosion);
}

void ProjectileCollisionSystem::enemyHit(ProjectileEntity* projectile, AircraftEntity* aircraft) const
{
    aircraft->hit();
    mExplosionController.spawn(aircraft->getPosition(), Textures::Explosion);

    if (aircraft->destroyed())
    {
        mProjectileEntites.removeObject(projectile);
        mEnemyAircraftEntities.removeObject(aircraft);

        mScoreController.increaseScore();
    }
}