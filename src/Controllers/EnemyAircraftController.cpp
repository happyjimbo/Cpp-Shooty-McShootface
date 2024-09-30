#include "EnemyAircraftController.h"

EnemyAircraftController::EnemyAircraftController (
    EntitySystem<Aircraft::AircraftEntity>& entitySystem
    ) noexcept
{
    entitySystem.prePool(20);
}
