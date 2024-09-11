#include "PlayerAircraftController.h"
#include "AircraftEntity.h"

PlayerAircraftController::PlayerAircraftController(EntitySystem<AircraftEntity>& entitySystem,
    const TextureHolder& textures,
    const sf::Vector2f spawnPosition) noexcept
: mPlayerAircraft(entitySystem.createObject(AircraftEntity::Eagle, textures, sPlayerHealth))
{
    mPlayerAircraft->setPosition(spawnPosition);
}

AircraftEntity* PlayerAircraftController::getPlayerAircaft() const
{
    return mPlayerAircraft;
}
