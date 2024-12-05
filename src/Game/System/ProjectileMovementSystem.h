#pragma once
#include "EntitySystem.h"

class ProjectileEntity;

class ProjectileMovementSystem final
{
public:

    explicit ProjectileMovementSystem(EntitySystem<ProjectileEntity>& entitySystem) noexcept;
    ~ProjectileMovementSystem() = default;

    ProjectileMovementSystem(const ProjectileMovementSystem&) = delete;
    ProjectileMovementSystem& operator=(const ProjectileMovementSystem&) = delete;

    ProjectileMovementSystem(ProjectileMovementSystem&&) = delete;
    ProjectileMovementSystem& operator=(ProjectileMovementSystem&&) = delete;

    void execute(const sf::Time& delta) const;

private:
    EntitySystem<ProjectileEntity>& mEntitySystem;
};
