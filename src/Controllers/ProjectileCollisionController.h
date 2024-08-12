#ifndef CMAKESFMLPROJECT_PROJECTILE_COLLISION_CONTROLLER_H
#define CMAKESFMLPROJECT_PROJECTILE_COLLISION_CONTROLLER_H

#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "ProjectileController.h"
#include "EnemyAircraftController.h"

class AircraftEntity;
class ProjectileEntity;


class ProjectileCollisionController {

    public:
                            ProjectileCollisionController(
                                const std::shared_ptr<ProjectileController>&,
                                const std::shared_ptr<EnemyAircraftController>&);
        void                tick(sf::Time delta) const;

    private:
        void                collided(std::shared_ptr<ProjectileEntity>& projectile, std::shared_ptr<AircraftEntity>& aircraft) const;
        static float        getSquareMagnitude(sf::Vector2f pos1, sf::Vector2f pos2);

    private:
        const std::shared_ptr<ProjectileController> mProjectileController;
        const std::shared_ptr<EnemyAircraftController> mEnemyAircraftController;
};

#endif //CMAKESFMLPROJECT_PROJECTILE_COLLISION_CONTROLLER_H