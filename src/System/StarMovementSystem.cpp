#include "AircraftEntity.h"
#include "StarEntity.h"
#include "StarMovementSystem.h"

#include <iostream>

namespace
{
    constexpr float speed = 0.1f;
}

StarMovementSystem::StarMovementSystem(
    StarEntity& starEntity,
    Aircraft::AircraftEntity& playerAircraft
) noexcept
: mStarEntity(starEntity)
, mPlayerAircraft(playerAircraft)
{
    mStarEntity.setPosition(mPlayerAircraft.getPosition());
}

void StarMovementSystem::execute()
{
    const float x = (cos(speed) * mXPos) + (-sin(speed) * mYPos);
    const float y = (sin(speed) * mXPos) + (cos(speed) * mYPos);

    mXPos = x;
    mYPos = y;

    mStarEntity.setPosition(mPlayerAircraft.getPosition().x + x, mPlayerAircraft.getPosition().y + y);

    // std::cout << "player position " << mPlayerAircraft.getPosition().x << "," << mPlayerAircraft.getPosition().y << std::endl;
    // std::cout << "star position " << mStarEntity.getPosition().x << "," << mStarEntity.getPosition().y << std::endl;
}
