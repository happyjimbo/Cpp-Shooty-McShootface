#pragma once

#include <map>
#include <SFML/Window/Keyboard.hpp>

namespace GUI { class Button; }
namespace Aircraft { class AircraftEntity; }

class PlayerControls final
{
public:
    explicit PlayerControls(Aircraft::AircraftEntity& player);
    ~PlayerControls() noexcept = default;

    void handleRealtimeInput() const;
private:
    std::unordered_map<sf::Keyboard::Key, std::function<void()>> mKeyBinding;
};
