#pragma once
#include <Button.h>

#include "Label.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/View.hpp"

namespace sf { class RenderWindow; }

class Button;

using GUI::Label;

class TransitionScreen final
{
public:
    explicit TransitionScreen(sf::RenderWindow& window, const FontHolder& font, const char* title, const char* buttonText) noexcept;
    ~TransitionScreen() noexcept = default;

    void draw() const;
    void handleEvent(const sf::Event& event, const std::function<void()>& callback) const;

private:

    void centerTitle();
    void centerButton();

    sf::RenderWindow& mWindow;
    sf::View mWorldView;

    Button mButton;

    Label titleLabel {};
};