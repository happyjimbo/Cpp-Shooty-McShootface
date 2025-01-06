#pragma once

#include <memory>

#include "ResourceIdentifiers.h"

class World;
struct GameSettingsData;
class GameSettings;

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
    explicit StateHandler(sf::RenderWindow& window, sf::RenderTexture& gameRenderTexture, const FontHolder& font, const std::function<void(World*)>& setWorld) noexcept;
    ~StateHandler() noexcept;

    explicit StateHandler(const StateHandler&) = delete;
    StateHandler& operator=(const StateHandler&) = delete;

    explicit StateHandler(StateHandler&&) = delete;
    StateHandler& operator=(StateHandler&&) = delete;

    void update(sf::Time elapsedTime) const;
    void processWindowEvents(const sf::Event& event) const;
    void draw() const;
    void settingsUpdated(const GameSettingsData& settings) const;

    World& getWorld() const;

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};
