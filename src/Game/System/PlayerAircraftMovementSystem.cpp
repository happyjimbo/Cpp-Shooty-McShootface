#include "PlayerAircraftMovementSystem.h"
#include "AircraftEntity.h"

namespace
{
    constexpr float borderDistance = 40.f;
}

PlayerAircraftMovementSystem::PlayerAircraftMovementSystem(
    Aircraft::AircraftEntity& playerAircraft,
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
    position.x = std::max(position.x, mViewBounds.left + borderDistance);
    position.x = std::min(position.x, mViewBounds.left + mViewBounds.width - borderDistance);
    position.y = std::max(position.y, mViewBounds.top + borderDistance);
    position.y = std::min(position.y, mViewBounds.top + mViewBounds.height - borderDistance);
    mPlayerAircraft.setPosition(position);
}