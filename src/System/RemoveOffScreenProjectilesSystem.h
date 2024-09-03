#pragma once

#include "EntitySystem.h"

class ProjectileEntity;

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class RemoveOffScreenProjectilesSystem {

public:
    explicit RemoveOffScreenProjectilesSystem(EntitySystem<ProjectileEntity>& entities, float heightBoundary) noexcept;

    ~RemoveOffScreenProjectilesSystem() = default;

    // delete
    explicit RemoveOffScreenProjectilesSystem() = delete;

    RemoveOffScreenProjectilesSystem(const RemoveOffScreenProjectilesSystem&) = delete;
    RemoveOffScreenProjectilesSystem& operator=(const RemoveOffScreenProjectilesSystem&) = delete;

    RemoveOffScreenProjectilesSystem(RemoveOffScreenProjectilesSystem&&) = delete;
    RemoveOffScreenProjectilesSystem& operator=(RemoveOffScreenProjectilesSystem&&) = delete;

    void execute() const;

private:
    EntitySystem<ProjectileEntity>& mEntitySystem;
    float mHeightBoundary;
};
