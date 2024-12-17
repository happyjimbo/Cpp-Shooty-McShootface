#include "EditorGameMode.h"

#include "Performance.h"
#include "Settings.h"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Graphics.hpp"

#include <imgui-SFML.h>

sf::VideoMode EditorGameMode::determineVideoMode([[maybe_unused]] const GameSettingsData& settings) const
{
    return sf::VideoMode::getDesktopMode();
}

void EditorGameMode::init(sf::RenderWindow& window, [[maybe_unused]]std::shared_ptr<GameSettings>& gameSettings)
{
    success = ImGui::SFML::Init(window);
    settingsPanel = std::make_unique<Settings>(gameSettings);
}

bool EditorGameMode::isWindowOpen(sf::RenderWindow& window)
{
    return success && window.isOpen();
}

void EditorGameMode::processEvent(sf::Event& event)
{
    ImGui::SFML::ProcessEvent(event);
}

bool EditorGameMode::update(sf::RenderWindow& window, const sf::Time& elapsedTime)
{
    ImGui::SFML::Update(window, elapsedTime);
    Performance::update(elapsedTime.asSeconds());

    return !settingsPanel->isPaused();
}

void EditorGameMode::render(sf::RenderWindow& window)
{
    settingsPanel->draw();
    ImGui::SFML::Render(window);
}

void EditorGameMode::shutdown()
{
    ImGui::SFML::Shutdown();
}