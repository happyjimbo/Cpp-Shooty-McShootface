#include "PlayerKilledSystem.h"
#include "AircraftEntity.h"

PlayerKilledSystem::PlayerKilledSystem(Aircraft::AircraftEntity& PlayerAircraft, const std::function<void()>& callback) noexcept
: mPlayerAircraft(PlayerAircraft)
, mCallback(callback)
{

}

void PlayerKilledSystem::execute() const
{
    if (mPlayerAircraft.getAircraftData().destroyed())
    {
        mCallback();
    }
}
