#pragma once
#include "SFML/Graphics/Rect.hpp"

namespace Aircraft { class AircraftEntity; }

class PlayerAircraftMovementSystem final
{
public:

    explicit PlayerAircraftMovementSystem(
        Aircraft::AircraftEntity& playerAircraft,
        sf::Vector2f worldCenter,
        sf::Vector2f worldSize,
        float scrollSpeed) noexcept;
    ~PlayerAircraftMovementSystem() noexcept = default;

    PlayerAircraftMovementSystem(const PlayerAircraftMovementSystem&) = delete;
    PlayerAircraftMovementSystem& operator=(const PlayerAircraftMovementSystem&) = delete;

    PlayerAircraftMovementSystem(const PlayerAircraftMovementSystem&&) = delete;
    PlayerAircraftMovementSystem& operator=(const PlayerAircraftMovementSystem&&) = delete;

    void execute() const;

private:

    void enforceBoundaries() const;
    Aircraft::AircraftEntity& mPlayerAircraft;

    float mScrollSpeed;
    sf::FloatRect mViewBounds;

    const sf::Vector2f mWorldCenter;
    const sf::Vector2f mWorldSize;
};
