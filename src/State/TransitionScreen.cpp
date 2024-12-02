#include "TransitionScreen.h"
#include "Button.h"
#include <SFML/Window/Event.hpp>

namespace
{
    constexpr float ButtonWidth = 200.f;
    constexpr float ButtonHeight = 50.f;
    constexpr float FontSize = 50.f;
    constexpr float TitleYOffset = 50.0f;
    constexpr float ButtonYOffset = 50.0f;
}

TransitionScreen::TransitionScreen(sf::RenderTexture& gameRenderTexture, const FontHolder& font, const char* title, const char* buttonText) noexcept
: mGameRenderTexture(gameRenderTexture)
, mWorldView(gameRenderTexture.getDefaultView())
, mButton(ButtonWidth, ButtonHeight, buttonText)
, mBackground(sf::Vector2f(mGameRenderTexture.getSize().x, mGameRenderTexture.getSize().y))
{
    mBackground.setFillColor(sf::Color::Black);

    titleLabel.create(title, font, FontSize);
    centerTitle();
    centerButton();
}

void TransitionScreen::handleEvent(const sf::Event& event, const GameRenderTextureState& gameRenderTextureState, const std::function<void()>& callback) const
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (mButton.isMouseOver(mGameRenderTexture, gameRenderTextureState))
        {
            callback();
        }
    }
}

void TransitionScreen::draw() const
{
    mGameRenderTexture.draw(mBackground);

    mGameRenderTexture.setView(mWorldView);
    mGameRenderTexture.draw(titleLabel);
    mButton.draw(mGameRenderTexture);
}

void TransitionScreen::centerTitle()
{
    const auto textBounds = titleLabel.getGlobalBounds();
    const float xPosition = (mGameRenderTexture.getSize().x - textBounds.width) / 2.0f;
    const float yPosition = (mGameRenderTexture.getSize().y - textBounds.height) / 2.0f;
    titleLabel.setPosition(xPosition, yPosition - TitleYOffset);
}

void TransitionScreen::centerButton()
{
    const float xPosition = (mGameRenderTexture.getSize().x - mButton.getSize().x) / 2.0f;
    const float yPosition = (mGameRenderTexture.getSize().y - mButton.getSize().y) / 2.0f;
    mButton.setPosition(xPosition, yPosition + ButtonYOffset);
}