#pragma once
#include <SFML/System/Vector2.hpp>

inline float getSquareMagnitude(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
    const float dx = pos1.x - pos2.x;
    const float dy = pos1.y - pos2.y;
    return (dx * dx) + (dy * dy);
}