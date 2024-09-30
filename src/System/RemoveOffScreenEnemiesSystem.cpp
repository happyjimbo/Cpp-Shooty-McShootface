#include "RemoveOffScreenEnemiesSystem.h"
#include "AircraftEntity.h"

RemoveOffScreenEnemiesSystem::RemoveOffScreenEnemiesSystem(EntitySystem<Aircraft::AircraftEntity>& entities, const float heightBoundary) noexcept
    : mEntitySystem(entities)
    , mHeightBoundary(heightBoundary)
{
}

void RemoveOffScreenEnemiesSystem::execute() const
{
    for (auto* entity : mEntitySystem.getEntities())
    {
        if (entity->getPosition().y > mHeightBoundary)
        {
            //std::cout << "release entity to the pool" << std::endl;
            mEntitySystem.removeObject(entity);
        }
    }
}