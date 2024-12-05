#include "ProjectileMovementSystem.h"
#include "ProjectileEntity.h"

ProjectileMovementSystem::ProjectileMovementSystem(EntitySystem<ProjectileEntity>& entitySystem) noexcept
: mEntitySystem(entitySystem)
{

}

void ProjectileMovementSystem::execute(const sf::Time &delta) const
{
    for (const auto& projectile : mEntitySystem.getEntities())
    {
        projectile->update(delta);
    }
}
