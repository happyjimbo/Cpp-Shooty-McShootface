#include "PlayerAircraftController.h"
#include "AircraftEntity.h"

PlayerAircraftController::PlayerAircraftController(
    EntitySystem<AircraftEntity>& entitySystem,
    const sf::Vector2f worldCenter,
    const sf::Vector2f worldSize,
    const float scrollSpeed
    ) noexcept
        : mEntitySystem(entitySystem)
        , mWorldCenter(worldCenter)
        , mWorldSize(worldSize)
        , mScrollSpeed(scrollSpeed)
{
    mViewBounds = sf::FloatRect(mWorldCenter - mWorldSize / 2.f, mWorldSize);
}

void PlayerAircraftController::create(const TextureHolder& textures, const sf::Vector2f spawnPosition)
{
    mPlayerAircraft = mEntitySystem.createObject(AircraftEntity::Eagle, textures);
    mPlayerAircraft->setPosition(spawnPosition);
}

void PlayerAircraftController::tick() const
{
    mPlayerAircraft->setVelocity(0.f, 0.f);
    enforceBoundaries();
    mPlayerAircraft->accelerate(0.f, mScrollSpeed/2);
}

void PlayerAircraftController::enforceBoundaries() const
{
    auto position = mPlayerAircraft->getPosition();
    position.x = std::max(position.x, mViewBounds.left + sBorderDistance);
    position.x = std::min(position.x, mViewBounds.left + mViewBounds.width - sBorderDistance);
    position.y = std::max(position.y, mViewBounds.top + sBorderDistance);
    position.y = std::min(position.y, mViewBounds.top + mViewBounds.height - sBorderDistance);
    mPlayerAircraft->setPosition(position);
}

AircraftEntity* PlayerAircraftController::getPlayerAircaft() const
{
    return mPlayerAircraft;
}
