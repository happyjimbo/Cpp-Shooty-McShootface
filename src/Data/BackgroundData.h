#pragma once

#include <SFML/Graphics/Rect.hpp>

struct BackgroundData
{
    sf::IntRect rect;
    sf::Vector2u bounds;
    float scrollSpeed;
};
