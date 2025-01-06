#include "EditorGameMode.h"

#include "Graph.h"
#include "Settings.h"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Graphics.hpp"

#include <imgui-SFML.h>

#include "EntitySystems.h"
#include "Memory.h"
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

    const auto delta = elapsedTime.asSeconds();
    Graph::renderPanelWithGraph<MaxSampleSize>("Frame Per Second", "fps %.2f", mFramesBuffer, 1.f / delta, GraphHeight);

    const float memoryMb = Memory::getProcessMemoryUsageMB();
    Graph::renderPanelWithGraph<MaxSampleSize>("Process memory", "%.2f MB", mMemoryBuffer, memoryMb, GraphHeight);

    if (mWorld != nullptr)
    {
        auto& projectiles = mWorld->getEntitySystems().projectileEntitySystem.getEntities();
        auto& playerAircrafts = mWorld->getEntitySystems().playerAircraftEntitySystem.getEntities();
        auto& enemies = mWorld->getEntitySystems().enemyAircraftEntitySystem.getEntities();
        auto& backgrounds = mWorld->getEntitySystems().backgroundEntitySystem.getEntities();
        auto& clouds = mWorld->getEntitySystems().cloudEntitySystem.getEntities();
        auto& explosions = mWorld->getEntitySystems().explosionEntitySystem.getEntities();
        auto& labels = mWorld->getEntitySystems().labelEntitySystem.getEntities();
        auto& stars = mWorld->getEntitySystems().starEntitySystem.getEntities();

        Graph::beginPanel("Entities");
        Graph::plotGraph<MaxSampleSize>("Projectiles %.2f", mProjectileBuffer, projectiles.size(), GraphHeight);
        Graph::plotGraph<MaxSampleSize>("Player Aircraft %.2f", mPlayerAircraftBuffer, playerAircrafts.size(), GraphHeight);
        Graph::plotGraph<MaxSampleSize>("Enemy Aircraft %.2f", mEnemyAircraftBuffer, enemies.size(), GraphHeight);
        Graph::plotGraph<MaxSampleSize>("Background %.2f", mBackgroundBuffer, backgrounds.size(), GraphHeight);
        Graph::plotGraph<MaxSampleSize>("Clouds %.2f", mCloudBuffer, clouds.size(), GraphHeight);
        Graph::plotGraph<MaxSampleSize>("Explosions %.2f", mExplosionBuffer, explosions.size(), GraphHeight);
        Graph::plotGraph<MaxSampleSize>("Labels %.2f", mLabelBuffer, labels.size(), GraphHeight);
        Graph::plotGraph<MaxSampleSize>("Stars %.2f", mStarBuffer, stars.size(), GraphHeight);
        Graph::endPanel();
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
