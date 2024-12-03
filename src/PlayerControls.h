#pragma once

#include <map>
#include <SFML/Window/Keyboard.hpp>

struct CursorState;

namespace GUI
{
    class Button;
}

namespace Aircraft { class AircraftEntity; }

class PlayerControls final
{
public:
    explicit PlayerControls(Aircraft::AircraftEntity& player);
    ~PlayerControls() noexcept = default;

    void handleRealtimeInput() const;

    static bool isMouseOverButton(const GUI::Button& button, const CursorState& renderTextureState);

private:


    std::unordered_map<sf::Keyboard::Key, std::function<void()>> mKeyBinding;

    constexpr static float playerSpeed = 400.f;
    constexpr static float horizontalSpeed = playerSpeed * 1.4f;
    constexpr static float sPlayerProjectileSpawnSpeed = 0.1f;
};
