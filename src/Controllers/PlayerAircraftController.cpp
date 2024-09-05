#include "PlayerAircraftController.h"
#include "AircraftEntity.h"

PlayerAircraftController::PlayerAircraftController(EntitySystem<AircraftEntity>& entitySystem) noexcept
: mEntitySystem(entitySystem)
{
}

void PlayerAircraftController::create(const TextureHolder& textures, const sf::Vector2f spawnPosition)
{
    mPlayerAircraft = mEntitySystem.createObject(AircraftEntity::Eagle, textures, sPlayerHealth);
    mPlayerAircraft->setPosition(spawnPosition);
}

AircraftEntity* PlayerAircraftController::getPlayerAircaft() const
{
    return mPlayerAircraft;
}
