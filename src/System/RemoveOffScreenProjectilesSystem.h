#pragma once

#include "EntitySystem.h"

class ProjectileEntity;

class RemoveOffScreenProjectilesSystem {

public:
    explicit RemoveOffScreenProjectilesSystem(EntitySystem<ProjectileEntity>& entities, float heightBoundary) noexcept;

    explicit RemoveOffScreenProjectilesSystem() = delete;
    ~RemoveOffScreenProjectilesSystem() = default;

    RemoveOffScreenProjectilesSystem(const RemoveOffScreenProjectilesSystem&) = delete;
    RemoveOffScreenProjectilesSystem& operator=(const RemoveOffScreenProjectilesSystem&) = delete;

    RemoveOffScreenProjectilesSystem(RemoveOffScreenProjectilesSystem&&) = delete;
    RemoveOffScreenProjectilesSystem& operator=(RemoveOffScreenProjectilesSystem&&) = delete;

    void execute() const;

private:
    EntitySystem<ProjectileEntity>& mEntitySystem;
    float mHeightBoundary;
};
