#pragma once

#include <map>
#include <unordered_set>
#include <SFML/Window/Keyboard.hpp>

namespace sf { class Event; }
namespace GUI { class Button; }
namespace Aircraft { class AircraftEntity; }

class PlayerControls final
{
public:
    explicit PlayerControls(Aircraft::AircraftEntity& player);
    ~PlayerControls() noexcept = default;

    void handleEvent(const sf::Event& event);
    void update() const;
private:
    std::unordered_set<sf::Keyboard::Key> mActiveKeys;
    std::unordered_map<sf::Keyboard::Key, std::function<void()>> mKeyBinding;
};
