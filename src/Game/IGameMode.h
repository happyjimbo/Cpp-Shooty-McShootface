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

    virtual void setSettings(std::shared_ptr<GameSettings>& gameSettings) = 0;
    virtual sf::VideoMode determineVideoMode([[maybe_unused]] const GameSettingsData& settings) const = 0;
    virtual bool isWindowOpen(sf::RenderWindow& window) = 0;
    virtual void processEvent(sf::Event& event) = 0;
    virtual bool update(sf::RenderWindow& window, const sf::Time& elapsedTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void shutdown() = 0;
};

class StanardGameMode : public IGameMode
{
public:

    void setSettings([[maybe_unused]]std::shared_ptr<GameSettings>& gameSettings) override
    {

    }

    sf::VideoMode determineVideoMode(const GameSettingsData& settings) const override
    {
        return sf::VideoMode(settings.width, settings.height);
    }

    bool isWindowOpen(sf::RenderWindow& window) override
    {
        return window.isOpen();
    }

    void processEvent(sf::Event&) override
    {

    }

    bool update(sf::RenderWindow&, const sf::Time&) override
    {
        return true;
    }

    void render(sf::RenderWindow&) override
    {

    }

    void shutdown() override
    {

    }
};

#ifdef EDITOR_MODE
#include <imgui-SFML.h>
#include "Performance.h"
#include "Settings.h"

class EditorGameMode : public IGameMode {
public:

    std::unique_ptr<Settings> settingsPanel;

    void setSettings(std::shared_ptr<GameSettings>& gameSettings) override
    {
        settingsPanel = std::make_unique<Settings>(gameSettings);
    }

    sf::VideoMode determineVideoMode([[maybe_unused]] const GameSettingsData& settings) const override
    {
        return sf::VideoMode::getDesktopMode();
    }

    bool isWindowOpen(sf::RenderWindow& window) override
    {
        const auto success = ImGui::SFML::Init(window);
        return success && window.isOpen();
    }

    void processEvent(sf::Event& event) override
    {
        ImGui::SFML::ProcessEvent(event);
    }

    bool update(sf::RenderWindow& window, const sf::Time& elapsedTime) override
    {
        ImGui::SFML::Update(window, elapsedTime);
        Performance::update(elapsedTime.asSeconds());

        return !settingsPanel->isPaused();
    }

    void render(sf::RenderWindow& window) override
    {
        settingsPanel->draw();
        ImGui::SFML::Render(window);
    }

    void shutdown() override
    {
        ImGui::SFML::Shutdown();
    }
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