#include "Button.h"
#include "MediaFiles.h"

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

    bool Button::isMouseOver(const sf::Event& event, const sf::RenderTexture& renderTexture) const
    {
        const sf::Vector2i mousePosScreen = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
        const sf::Vector2f mousePosWorld = renderTexture.mapPixelToCoords(mousePosScreen);
        return buttonRect.getGlobalBounds().contains(mousePosWorld);
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
