#include "EnemyAircraftInitializer.h"

EnemyAircraftInitializer::EnemyAircraftInitializer (
    EntitySystem<Aircraft::AircraftEntity>& entitySystem
    ) noexcept
{
    entitySystem.prePool(20);
}
