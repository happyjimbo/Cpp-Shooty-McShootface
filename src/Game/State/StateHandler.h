#pragma once

#include <memory>

#include "ResourceIdentifiers.h"

namespace sf
{
    class RenderTexture;
    class Event;
    class Time;
    class RenderWindow;
}

class StateHandler final
{
public:
    explicit StateHandler(sf::RenderWindow& window, sf::RenderTexture& gameRenderTexture, const FontHolder& font) noexcept;
    ~StateHandler() noexcept;

    explicit StateHandler(const StateHandler&) = delete;
    StateHandler& operator=(const StateHandler&) = delete;

    explicit StateHandler(StateHandler&&) = delete;
    StateHandler& operator=(StateHandler&&) = delete;

    void update(sf::Time elapsedTime) const;
    void processWindowEvents(const sf::Event& event) const;
    void draw() const;

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};
