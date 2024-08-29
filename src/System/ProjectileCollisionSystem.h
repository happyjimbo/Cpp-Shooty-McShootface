#pragma once

#include "EnemyAircraftController.h"

class ScoreController;
class AircraftEntity;
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
    void tick(sf::Time delta) const;

private:
    void collided(ProjectileEntity* projectile, AircraftEntity* aircraft) const;
    static float getSquareMagnitude(sf::Vector2f pos1, sf::Vector2f pos2);

private:
    EntitySystem<ProjectileEntity>& mProjectileEntites;
    EntitySystem<AircraftEntity>& mEnemyAircraftEntities;
    EntitySystem<AircraftEntity>& mPlayerAircraftEntities;
    ScoreController& mScoreController;
};