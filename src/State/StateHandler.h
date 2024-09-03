#pragma once

#include "ResourceIdentifiers.h"
#include <SFML/Graphics/RenderWindow.hpp>

class World;
class TransitionScreen;

namespace sf { class RenderWindow; }

class StateHandler final
{
public:
    explicit StateHandler(sf::RenderWindow& window, const FontHolder& font) noexcept;
    ~StateHandler() noexcept;

    void startGame();
    void transitionScreen(const char* title, const char* buttonText);
    void update(sf::Time elapsedTime) const;
    void processWindowEvents(const sf::Event& event);
    void draw() const;

private:
    sf::RenderWindow& mWindow;

    World* mWorld {nullptr};
    TransitionScreen* mTransitionScreen {nullptr};

    const FontHolder& mFont;
};
