#pragma once
#include <memory>

namespace sf
{
    class RenderWindow;
    class Event;
    class Time;
    class VideoMode;
}

class GameSettings;
struct GameSettingsData;

class IGameMode {
public:
    virtual ~IGameMode() = default;

    virtual void init(sf::RenderWindow& window, [[maybe_unused]]std::shared_ptr<GameSettings>& gameSettings) = 0;
    virtual sf::VideoMode determineVideoMode([[maybe_unused]] const GameSettingsData& settings) const = 0;
    virtual bool isWindowOpen(sf::RenderWindow& window) = 0;
    virtual void processEvent(sf::Event& event) = 0;
    virtual bool update(sf::RenderWindow& window, const sf::Time& elapsedTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void shutdown() = 0;
};