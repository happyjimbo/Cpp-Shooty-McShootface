#pragma once

#include <map>
#include <SFML/Window/Keyboard.hpp>

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class PlayerControls final
{
public:
    explicit PlayerControls() noexcept = default;
    ~PlayerControls() noexcept = default;

    void initializeActions(AircraftEntity& player);
    void handleRealtimeInput() const;

private:


    std::unordered_map<sf::Keyboard::Key, std::function<void()>> mKeyBinding;

    constexpr static float playerSpeed = 400.f;
    constexpr static float horizontalSpeed = playerSpeed * 1.4f;
    constexpr static float sPlayerProjectileSpawnSpeed = 0.1f;
};
