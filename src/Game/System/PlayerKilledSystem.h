#pragma once
#include <functional>

namespace Aircraft { class AircraftEntity; }

class PlayerKilledSystem final
{
public:

    explicit PlayerKilledSystem(Aircraft::AircraftEntity& PlayerAircraft, const std::function<void()>& callback) noexcept;

    explicit PlayerKilledSystem() noexcept = delete;
    ~PlayerKilledSystem() noexcept = default;

    PlayerKilledSystem(const PlayerKilledSystem&) = delete;
    PlayerKilledSystem& operator=(const PlayerKilledSystem&) = delete;

    PlayerKilledSystem(PlayerKilledSystem&&) = delete;
    PlayerKilledSystem& operator=(PlayerKilledSystem&&) = delete;

    void execute() const;

private:
    const Aircraft::AircraftEntity& mPlayerAircraft;
    std::function<void()> mCallback;
};
