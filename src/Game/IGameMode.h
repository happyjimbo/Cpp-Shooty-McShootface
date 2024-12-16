#pragma once

namespace sf
{
    class RenderWindow;
    class Event;
    class Time;
    class VideoMode;
}

class IGameMode {
public:
    virtual ~IGameMode() = default;

    virtual sf::VideoMode determineVideoMode([[maybe_unused]] const GameSettingsData& settings) const = 0;
    virtual bool isWindowOpen(sf::RenderWindow& window) = 0;
    virtual void processEvent(sf::Event& event) = 0;
    virtual void update(sf::RenderWindow& window, const sf::Time& elapsedTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void shutdown() = 0;
};

class StanardGameMode : public IGameMode
{
public:
    sf::VideoMode determineVideoMode(const GameSettingsData& settings) const override
    {
        return sf::VideoMode(settings.width, settings.height);
    }

    bool isWindowOpen(sf::RenderWindow& window) override
    {
        return window.isOpen();
    }

    void processEvent(sf::Event&) override {}
    void update(sf::RenderWindow&, const sf::Time&) override {}
    void render(sf::RenderWindow&) override {}
    void shutdown() override {}
};

#ifdef EDITOR_MODE
#include <imgui-SFML.h>
#include "Performance.h"

class EditorGameMode : public IGameMode {
public:
    sf::VideoMode determineVideoMode([[maybe_unused]] const GameSettingsData& settings) const override
    {
        return sf::VideoMode::getDesktopMode();
    }

    bool isWindowOpen(sf::RenderWindow& window) override
    {
        const auto success = ImGui::SFML::Init(window);
        return success && window.isOpen();
    }

    void processEvent(sf::Event& event) override { ImGui::SFML::ProcessEvent(event); }
    void update(sf::RenderWindow& window, const sf::Time& elapsedTime) override
    {
        ImGui::SFML::Update(window, elapsedTime);
        Performance::update(elapsedTime.asSeconds());
    }
    void render(sf::RenderWindow& window) override { ImGui::SFML::Render(window); }
    void shutdown() override { ImGui::SFML::Shutdown(); }
};
#endif


inline std::unique_ptr<IGameMode> CreateGameMode()
{
#ifdef EDITOR_MODE
    return std::make_unique<EditorGameMode>();
#else
    return std::make_unique<StanardGameMode>();
#endif
}