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

    StarMovementSystem(const StarMovementSystem&&) = delete;
    StarMovementSystem& operator=(const StarMovementSystem&&) = delete;

    void execute();
private:
    float mXPos {50};
    float mYPos {50};

    StarEntity& mStarEntity;
    Aircraft::AircraftEntity& mPlayerAircraft;
};
