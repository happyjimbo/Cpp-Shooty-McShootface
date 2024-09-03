#pragma once
#include <functional>

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class PlayerKilledSystem final
{
public:

    explicit PlayerKilledSystem(AircraftEntity& PlayerAircraft, const std::function<void()>& callback) noexcept;
    ~PlayerKilledSystem() noexcept = default;

    // delete
    explicit PlayerKilledSystem() noexcept = delete;

    PlayerKilledSystem(const PlayerKilledSystem&) = delete;
    PlayerKilledSystem& operator=(const PlayerKilledSystem&) = delete;

    PlayerKilledSystem(PlayerKilledSystem&&) = delete;
    PlayerKilledSystem& operator=(PlayerKilledSystem&&) = delete;


    void execute() const;

private:
    const AircraftEntity& mPlayerAircraft;
    std::function<void()> mCallback;
};
