#include "ProjectileCollisionController.h"
#include "Aircraft.h"

#include "Logger.h"

ProjectileCollisionController::ProjectileCollisionController(
    const std::shared_ptr<ProjectileController>& projectileController,
    const std::shared_ptr<EnemyAircraftController>& enemyAircraftController)
    : mProjectileController(projectileController)
      , mEnemyAircraftController(enemyAircraftController)
{

}

void ProjectileCollisionController::tick(sf::Time delta) {

    auto projectiles = mProjectileController->getProjectiles();
    auto aircrafts = mEnemyAircraftController->getAircrafts();

    for(const auto p : projectiles)
    {
        for(const auto a : aircrafts)
        {
            const auto projectilePos = p->getPosition();
            const auto aircraftPos = a->getPosition();

            const float projectileSqrt = getSquareMagnitude(projectilePos);
            const float aircraftSqrt = getSquareMagnitude(aircraftPos);

            if (projectileSqrt - aircraftSqrt < 1) {
                collided(*p, *a);
            }
        }
    }
}

float ProjectileCollisionController::getSquareMagnitude(sf::Vector2f position) {
    return (position.x * position.x) + (position.y * position.y);
}

void ProjectileCollisionController::collided(Projectile &projectile, Aircraft &aircraft) {
    Log("collide!");
    aircraft.hit();
}