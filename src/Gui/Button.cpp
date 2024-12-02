#include "Button.h"
#include "MediaFiles.h"
#include <imgui.h>

#include "GameRenderTextureState.h"

namespace GUI
{
    Button::Button(const float width, const float height, const char* textString)
    {
        buttonRect.setSize(sf::Vector2f(width, height));
        buttonRect.setFillColor(sf::Color::Blue);

        mFonts.load(Fonts::Main, MediaFiles::Font);
        mLabel.create(textString, mFonts, 24);
    }

    void Button::draw(sf::RenderTexture& gameRenderTexture) const
    {
        gameRenderTexture.draw(buttonRect);
        gameRenderTexture.draw(mLabel);
    }

    bool Button::isMouseOver(const sf::RenderTexture& renderTexture, const GameRenderTextureState& gameRenderTextureState) const
    {
        const ImVec2 mousePos = ImGui::GetMousePos();

        if (mousePos.x < gameRenderTextureState.position.x ||
            mousePos.x > gameRenderTextureState.position.x + gameRenderTextureState.size.x ||
            mousePos.y < gameRenderTextureState.position.y ||
            mousePos.y > gameRenderTextureState.position.y + gameRenderTextureState.size.y) {
            return false;
        }

        const float relativeX = (mousePos.x - gameRenderTextureState.position.x) / gameRenderTextureState.size.x * renderTexture.getSize().x;
        const float relativeY = (mousePos.y - gameRenderTextureState.position.y) / gameRenderTextureState.size.y * renderTexture.getSize().y;

        const sf::Vector2f renderTexturePos(relativeX, relativeY);

        return buttonRect.getGlobalBounds().contains(renderTexturePos);
    }

    sf::Vector2f Button::getSize() const
    {
        return buttonRect.getSize();
    }

    sf::Vector2f Button::getPosition() const
    {
        return buttonRect.getPosition();
    }

    void Button::setPosition(const float x, const float y) {
        static constexpr float LabelYOffset = 7.0f;

        buttonRect.setPosition(x, y);
        mLabel.setPosition(
           x + (buttonRect.getSize().x / 2.f) - (mLabel.getLocalBounds().width / 2.f),
           y + (buttonRect.getSize().y / 2.f) - (mLabel.getLocalBounds().height / 2.f) - LabelYOffset
       );
    }
}
