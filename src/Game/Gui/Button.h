#pragma once
#include <SFML/Graphics.hpp>

#include "Label.h"
#include "ResourceHolder.h"

struct CursorState;
struct ImVec2;

namespace GUI
{
    class Button {
    public:
        explicit Button() = delete;
        explicit Button(float width, float height, const char* textString);
        ~Button() = default;

        void draw(sf::RenderTexture& gameRenderTexture) const;

        bool isMouseOver(const sf::RenderTexture& renderTexture, const CursorState& cursorState) const;
        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;
        void setPosition(float x, float y);

    private:
        sf::RectangleShape buttonRect;

        FontHolder mFonts;
        Label mLabel {};
    };
}