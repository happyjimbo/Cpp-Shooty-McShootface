#include "PlayerAircraftMovementSystem.h"
#include "AircraftEntity.h"

PlayerAircraftMovementSystem::PlayerAircraftMovementSystem(
    AircraftEntity& playerAircraft,
    const sf::Vector2f worldCenter,
    const sf::Vector2f worldSize,
    const float scrollSpeed) noexcept
: mPlayerAircraft(playerAircraft)
, mScrollSpeed(scrollSpeed)
, mWorldCenter(worldCenter)
, mWorldSize(worldSize)
{
    mViewBounds = sf::FloatRect(mWorldCenter - mWorldSize / 2.f, mWorldSize);
}

void PlayerAircraftMovementSystem::execute() const
{
    mPlayerAircraft.setVelocity(0.f, 0.f);
    enforceBoundaries();
    mPlayerAircraft.accelerate(0.f, mScrollSpeed/2);
}

void PlayerAircraftMovementSystem::enforceBoundaries() const
{
    auto position = mPlayerAircraft.getPosition();
    position.x = std::max(position.x, mViewBounds.left + sBorderDistance);
    position.x = std::min(position.x, mViewBounds.left + mViewBounds.width - sBorderDistance);
    position.y = std::max(position.y, mViewBounds.top + sBorderDistance);
    position.y = std::min(position.y, mViewBounds.top + mViewBounds.height - sBorderDistance);
    mPlayerAircraft.setPosition(position);
}