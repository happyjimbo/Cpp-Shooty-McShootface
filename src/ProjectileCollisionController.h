#ifndef CMAKESFMLPROJECT_PROJECTILE_COLLISION_CONTROLLER_H
#define CMAKESFMLPROJECT_PROJECTILE_COLLISION_CONTROLLER_H

#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "ProjectileController.h"
#include "EnemyAircraftController.h"

class Aircraft;
class Projectile;


class ProjectileCollisionController {

    public:
                            ProjectileCollisionController(
                                const std::shared_ptr<ProjectileController>&,
                                const std::shared_ptr<EnemyAircraftController>&);
        void                tick(sf::Time delta) const;

    private:
        void                collided(std::shared_ptr<Projectile>& projectile, std::shared_ptr<Aircraft>& aircraft) const;
        static float        getSquareMagnitude(sf::Vector2f projectilePos, sf::Vector2f aircraftPos);

    private:
        const std::shared_ptr<ProjectileController> mProjectileController;
        const std::shared_ptr<EnemyAircraftController> mEnemyAircraftController;
};

#endif //CMAKESFMLPROJECT_PROJECTILE_COLLISION_CONTROLLER_H