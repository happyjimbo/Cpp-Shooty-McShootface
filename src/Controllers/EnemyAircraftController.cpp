#include "EnemyAircraftController.h"

EnemyAircraftController::EnemyAircraftController (
    EntitySystem<AircraftEntity>& entitySystem
    ) noexcept
{
    entitySystem.prePool(20);
}
