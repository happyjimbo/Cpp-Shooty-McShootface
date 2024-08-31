#pragma once

#include "EntitySystem.h"
#include "AircraftEntity.h"

using Aircraft::AircraftEntity;

class ScoreController;
class ProjectileEntity;

class ProjectileCollisionSystem final
{
public:
    explicit ProjectileCollisionSystem(
        EntitySystem<ProjectileEntity>& projectileEntites,
        EntitySystem<AircraftEntity>& enemyAircraftEntities,
        EntitySystem<AircraftEntity>& playerAircraftEntities,
        ScoreController& scoreController
    );
    void execute() const;

private:
    void collided(ProjectileEntity* projectile, AircraftEntity* aircraft) const;
    static float getSquareMagnitude(sf::Vector2f pos1, sf::Vector2f pos2);

    EntitySystem<ProjectileEntity>& mProjectileEntites;
    EntitySystem<AircraftEntity>& mEnemyAircraftEntities;
    EntitySystem<AircraftEntity>& mPlayerAircraftEntities;
    ScoreController& mScoreController;
};