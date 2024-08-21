#pragma once

#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "EnemyAircraftController.h"

class AircraftEntity;
class ProjectileEntity;

class ProjectileCollisionController
{
public:
    ProjectileCollisionController(
        EntitySystem<ProjectileEntity>& projectileEntites,
        EntitySystem<AircraftEntity>& enemyAircraftEntities,
        EntitySystem<AircraftEntity>& playerAircraftEntities
    );
    void tick(sf::Time delta) const;

private:
    void collided(ProjectileEntity* projectile, AircraftEntity* aircraft) const;
    static float getSquareMagnitude(sf::Vector2f pos1, sf::Vector2f pos2);

private:
    EntitySystem<ProjectileEntity>& mProjectileEntites;
    EntitySystem<AircraftEntity>& mEnemyAircraftEntities;
    EntitySystem<AircraftEntity>& mPlayerAircraftEntities;
};