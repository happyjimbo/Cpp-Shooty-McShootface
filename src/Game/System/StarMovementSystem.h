#pragma once
#include "StarEntity.h"

namespace Aircraft { class AircraftEntity; }

class StarMovementSystem final
{
public:
    explicit StarMovementSystem(
        StarEntity& starEntity,
        Aircraft::AircraftEntity& playerAircraft
    ) noexcept;

    ~StarMovementSystem() noexcept = default;

    StarMovementSystem(const StarMovementSystem&) = delete;
    StarMovementSystem& operator=(const StarMovementSystem&) = delete;

    StarMovementSystem(StarMovementSystem&&) = delete;
    StarMovementSystem& operator=(StarMovementSystem&&) = delete;

    void execute();
private:
    StarEntity& mStarEntity;
    Aircraft::AircraftEntity& mPlayerAircraft;

    float mAngle;
    float mRadius;
};
