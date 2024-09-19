#pragma once
#include <SFML/Graphics.hpp>

#include "Label.h"
#include "ResourceHolder.h"

namespace GUI
{
    class Button {
    public:
        explicit Button() = delete;
        explicit Button(float width, float height, const char* textString);
        ~Button() = default;

        void draw(sf::RenderWindow& window) const;

        bool isMouseOver(const sf::RenderWindow& window) const;
        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;
        void setPosition(float x, float y);

    private:
        sf::RectangleShape buttonRect;

        FontHolder mFonts;
        Label mLabel {};
    };
}