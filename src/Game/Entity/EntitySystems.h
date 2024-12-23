#pragma once
#include "EntitySystem.h"

namespace GUI { class Label; }
namespace Aircraft { class AircraftEntity; }
class StarEntity;
class ExplosionEntity;
class CloudEntity;
class BackgroundEntity;
class ProjectileEntity;

struct EntitySystems
{
    EntitySystem<ProjectileEntity> projectileEntitySystem;
    EntitySystem<Aircraft::AircraftEntity> playerAircraftEntitySystem;
    EntitySystem<Aircraft::AircraftEntity> enemyAircraftEntitySystem;
    EntitySystem<BackgroundEntity> backgroundEntitySystem;
    EntitySystem<CloudEntity> cloudEntitySystem;
    EntitySystem<ExplosionEntity> explosionEntitySystem;
    EntitySystem<GUI::Label> labelEntitySystem;
    EntitySystem<StarEntity> starEntitySystem;
};
