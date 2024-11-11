#include "TransitionScreen.h"
#include "Button.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace
{
    constexpr float ButtonWidth = 200.f;
    constexpr float ButtonHeight = 50.f;
    constexpr float FontSize = 50.f;
    constexpr float TitleYOffset = 50.0f;
    constexpr float ButtonYOffset = 50.0f;
}

TransitionScreen::TransitionScreen(sf::RenderWindow& window, const FontHolder& font, const char* title, const char* buttonText) noexcept
: mWindow(window)
, mWorldView(window.getDefaultView())
, mButton(ButtonWidth, ButtonHeight, buttonText)
{
    titleLabel.create(title, font, FontSize);
    centerTitle();
    centerButton();
}

void TransitionScreen::handleEvent(const sf::Event& event, const std::function<void()>& callback) const
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (mButton.isMouseOver(mWindow))
        {
            callback();
        }
    }
}

void TransitionScreen::draw() const
{
    mWindow.setView(mWorldView);
    mWindow.draw(titleLabel);
    mButton.draw(mWindow);
}

void TransitionScreen::centerTitle()
{
    const auto textBounds = titleLabel.getGlobalBounds();
    const float xPosition = (mWindow.getSize().x - textBounds.width) / 2.0f;
    const float yPosition = (mWindow.getSize().y - textBounds.height) / 2.0f;
    titleLabel.setPosition(xPosition, yPosition - TitleYOffset);
}

void TransitionScreen::centerButton()
{
    const float xPosition = (mWindow.getSize().x - mButton.getSize().x) / 2.0f;
    const float yPosition = (mWindow.getSize().y - mButton.getSize().y) / 2.0f;
    mButton.setPosition(xPosition, yPosition + ButtonYOffset);
}