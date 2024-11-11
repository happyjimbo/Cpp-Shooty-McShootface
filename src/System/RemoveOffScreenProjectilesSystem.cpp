#include "RemoveOffScreenProjectilesSystem.h"
#include "AircraftEntity.h"

RemoveOffScreenProjectilesSystem::RemoveOffScreenProjectilesSystem(EntitySystem<ProjectileEntity>& entities, const float heightBoundary) noexcept
    : mEntitySystem(entities)
    , mHeightBoundary(heightBoundary)
{
}

void RemoveOffScreenProjectilesSystem::execute() const
{
    for (auto* entity : mEntitySystem.getEntities())
    {
        if (entity->getPosition().y > mHeightBoundary ||
            entity->getPosition().y < 0)
        {
            mEntitySystem.removeObject(entity);
        }
    }
}