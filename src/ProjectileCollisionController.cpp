#include "ProjectileCollisionController.h"
#include "Aircraft.h"

ProjectileCollisionController::ProjectileCollisionController(
    const std::shared_ptr<ProjectileController>& projectileController,
    const std::shared_ptr<EnemyAircraftController>& enemyAircraftController)
    : mProjectileController(projectileController)
      , mEnemyAircraftController(enemyAircraftController)
{

}

void ProjectileCollisionController::tick(sf::Time delta) const {

    auto projectiles = mProjectileController->getProjectiles();
    auto aircrafts = mEnemyAircraftController->getAircrafts();

    for(const auto p : projectiles)
    {
        for(const auto a : aircrafts)
        {
            const auto projectilePos = p->getPosition();
            const auto aircraftPos = a->getPosition();

            const float distanceSqrt = getSquareMagnitude(projectilePos, aircraftPos);
            constexpr float collisionThreshold = 30.f * 30.f; // Adjust the threshold as necessary

            if (distanceSqrt < collisionThreshold) {
                collided(*p, *a);
            }
        }
    }
}

float ProjectileCollisionController::getSquareMagnitude(sf::Vector2f pos1, sf::Vector2f pos2) {
    const float dx = pos1.x - pos2.x;
    const float dy = pos1.y - pos2.y;
    return (dx * dx) + (dy * dy);
}

void ProjectileCollisionController::collided(const Projectile &projectile, const Aircraft &aircraft) const {
    mProjectileController->destroy(projectile);
    mEnemyAircraftController->destroy(aircraft);
}