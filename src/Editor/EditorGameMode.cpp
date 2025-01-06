#include "EditorGameMode.h"

#include "Performance.h"
#include "Settings.h"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Graphics.hpp"

#include <imgui-SFML.h>

#include "EntitySystems.h"
#include "World.h"

using GameMode::EditorGameMode;

sf::VideoMode EditorGameMode::determineVideoMode(const GameSettingsData&) const
{
    return sf::VideoMode::getDesktopMode();
}

void EditorGameMode::init(sf::RenderWindow& window, std::shared_ptr<GameSettings>& gameSettings)
{
    mSuccess = ImGui::SFML::Init(window);
    mSettingsPanel = std::make_unique<Settings>(gameSettings);
}

bool EditorGameMode::isWindowOpen(sf::RenderWindow& window)
{
    return mSuccess && window.isOpen();
}

void EditorGameMode::processEvent(sf::Event& event)
{
    ImGui::SFML::ProcessEvent(event);
}

bool EditorGameMode::update(sf::RenderWindow& window, const sf::Time& elapsedTime)
{
    ImGui::SFML::Update(window, elapsedTime);
    Performance::update(elapsedTime.asSeconds());

    if (mWorld != nullptr)
    {
        auto& projectiles = mWorld->getEntitySystems().projectileEntitySystem.getEntities();
        std::cout << projectiles.size() << std::endl;
    }

    return !mSettingsPanel->isPaused();
}

void EditorGameMode::render(sf::RenderWindow& window)
{
    mSettingsPanel->draw();
    ImGui::SFML::Render(window);
}

void EditorGameMode::shutdown()
{
    ImGui::SFML::Shutdown();
}

void EditorGameMode::setWorld(World* world)
{
    mWorld = world;
}
