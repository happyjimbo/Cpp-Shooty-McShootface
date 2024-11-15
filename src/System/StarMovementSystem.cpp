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
, mAngle(0)
, mRadius(50.f)
{
    mStarEntity.setPosition(mPlayerAircraft.getPosition());
}

void StarMovementSystem::execute()
{
    mAngle += speed;
    const float x = cos(mAngle) * mRadius;
    const float y = sin(mAngle) * mRadius;

    mStarEntity.setPosition(mPlayerAircraft.getPosition().x + x, mPlayerAircraft.getPosition().y + y);

    // std::cout << "player position " << mPlayerAircraft.getPosition().x << "," << mPlayerAircraft.getPosition().y << std::endl;
    // std::cout << "star position " << mStarEntity.getPosition().x << "," << mStarEntity.getPosition().y << std::endl;
}
