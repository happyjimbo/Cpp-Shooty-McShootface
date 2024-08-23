#include "ProjectileCollisionController.h"
#include "ScoreController.h"
#include "Entity/AircraftEntity.h"

ProjectileCollisionController::ProjectileCollisionController(
    EntitySystem<ProjectileEntity>& projectileEntites,
    EntitySystem<AircraftEntity>& enemyAircraftEntities,
    EntitySystem<AircraftEntity>& playerAircraftEntities,
    ScoreController& scoreController)
: mProjectileEntites(projectileEntites)
, mEnemyAircraftEntities(enemyAircraftEntities)
, mPlayerAircraftEntities(playerAircraftEntities)
, mScoreController(scoreController)
{

}

void ProjectileCollisionController::tick(sf::Time delta) const
{
    const auto& projectiles = mProjectileEntites.getEntities();
    const auto& enemyAircraft = mEnemyAircraftEntities.getEntities();

    for(const auto p : projectiles)
    {
        for(const auto a : enemyAircraft)
        {
            const auto projectilePos = p->getPosition();
            const auto aircraftPos = a->getPosition();

            if (p->getType() == ProjectileEntity::Player)
            {
                const float distanceSqrt = getSquareMagnitude(projectilePos, aircraftPos);
                constexpr float collisionThreshold = 30.f;
                constexpr float collisionSqr = collisionThreshold * collisionThreshold; // Adjust the threshold as necessary

                if (distanceSqrt < collisionSqr) {
                    collided(p, a);
                }
            }
        }
    }
}

float ProjectileCollisionController::getSquareMagnitude(const sf::Vector2f pos1, const sf::Vector2f pos2)
{
    const float dx = pos1.x - pos2.x;
    const float dy = pos1.y - pos2.y;
    return (dx * dx) + (dy * dy);
}

void ProjectileCollisionController::collided(ProjectileEntity* projectile, AircraftEntity* aircraft) const
{
    mProjectileEntites.removeObject(projectile);
    mEnemyAircraftEntities.removeObject(aircraft);

    mScoreController.increaseScore();
}