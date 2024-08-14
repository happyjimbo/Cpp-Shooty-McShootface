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
                                ProjectileController&,
                                EnemyAircraftController&);
        void                tick(sf::Time delta) const;

    private:
        void                collided(ProjectileEntity* projectile, AircraftEntity* aircraft) const;
        static float        getSquareMagnitude(sf::Vector2f pos1, sf::Vector2f pos2);

    private:
        ProjectileController& mProjectileController;
        EnemyAircraftController& mEnemyAircraftController;
};

#endif //CMAKESFMLPROJECT_PROJECTILE_COLLISION_CONTROLLER_H