#pragma once
#include <functional>

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class PlayerKilledSystem final
{
public:

    explicit PlayerKilledSystem() noexcept = delete;
    explicit PlayerKilledSystem(AircraftEntity& PlayerAircraft, const std::function<void()>& callback) noexcept;

    ~PlayerKilledSystem() noexcept = default;

    void execute() const;

private:
    std::function<void()> mCallback;
    const AircraftEntity& mPlayerAircraft;
};