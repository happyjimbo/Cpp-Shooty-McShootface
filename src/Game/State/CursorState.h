#pragma once
#include <SFML/Graphics/Shape.hpp>

namespace CursorState
{
    static bool isMouseOverObject(const sf::Shape& shape, const sf::RenderWindow& window, const sf::RenderTexture& renderTexture)
    {
        const sf::Vector2i mousePosScreen = sf::Mouse::getPosition(window);
        const sf::Vector2f mousePosWorld = renderTexture.mapPixelToCoords(mousePosScreen);

        return shape.getGlobalBounds().contains(mousePosWorld);
    }
};