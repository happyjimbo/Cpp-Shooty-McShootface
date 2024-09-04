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
    ~StateHandler() noexcept = default;

    void startGame();
    void transitionScreen(const char* title, const char* buttonText);
    void update(sf::Time elapsedTime) const;
    void processWindowEvents(const sf::Event& event);
    void draw() const;

private:
    sf::RenderWindow& mWindow;

    std::unique_ptr<World> mWorld;
    std::unique_ptr<TransitionScreen> mTransitionScreen;

    const FontHolder& mFont;
};
