#include "PlayerAircraftController.h"
#include "AircraftEntity.h"
#include "PlayerData.h"

PlayerAircraftController::PlayerAircraftController(
    EntitySystem<AircraftEntity>& entitySystem,
    const TextureHolder& textures,
    const PlayerData& playerData,
    const sf::Vector2f spawnPosition
) noexcept
{
    mPlayerAircraft = entitySystem.createObject(AircraftEntity::Eagle, textures, playerData.Health);
    mPlayerAircraft->setPosition(spawnPosition);
}

AircraftEntity* PlayerAircraftController::getPlayerAircaft() const
{
    return mPlayerAircraft;
}
