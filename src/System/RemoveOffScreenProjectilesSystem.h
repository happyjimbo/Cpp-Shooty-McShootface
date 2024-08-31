#pragma once

#include "EntitySystem.h"

class ProjectileEntity;

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class RemoveOffScreenProjectilesSystem {

public:
    explicit RemoveOffScreenProjectilesSystem(EntitySystem<ProjectileEntity>& entities, float heightBoundary) noexcept;
    void execute() const;

private:
    EntitySystem<ProjectileEntity>& mEntitySystem;
    float mHeightBoundary;
};
