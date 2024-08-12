#include "ProjectileCollisionController.h"
#include "Entity/AircraftEntity.h"

ProjectileCollisionController::ProjectileCollisionController(
    const std::shared_ptr<ProjectileController>& projectileController,
    const std::shared_ptr<EnemyAircraftController>& enemyAircraftController)
    : mProjectileController(projectileController)
    , mEnemyAircraftController(enemyAircraftController)
{

}

void ProjectileCollisionController::tick(sf::Time delta) const {

    const auto projectiles = mProjectileController->getProjectiles();
    const auto aircrafts = mEnemyAircraftController->getAircrafts();

    for(auto p : projectiles)
    {
        for(auto a : aircrafts)
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

float ProjectileCollisionController::getSquareMagnitude(const sf::Vector2f pos1, const sf::Vector2f pos2) {
    const float dx = pos1.x - pos2.x;
    const float dy = pos1.y - pos2.y;
    return (dx * dx) + (dy * dy);
}

void ProjectileCollisionController::collided(std::shared_ptr<ProjectileEntity>& projectile, std::shared_ptr<AircraftEntity>& aircraft) const {
    mProjectileController->destroy(projectile);
    mEnemyAircraftController->destroy(aircraft);
}