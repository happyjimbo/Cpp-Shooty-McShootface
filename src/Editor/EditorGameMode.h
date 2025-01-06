#pragma once

#include "IGameMode.h"
#include "GameSettings.h"
#include "Settings.h"

namespace GameMode
{
    class EditorGameMode final : public IGameMode
    {
    public:
        sf::VideoMode determineVideoMode(const GameSettingsData& settings) const override;
        void init(sf::RenderWindow& window, std::shared_ptr<GameSettings>& gameSettings) override;
        bool isWindowOpen(sf::RenderWindow& window) override;
        void processEvent(sf::Event& event) override;
        bool update(sf::RenderWindow& window, const sf::Time& elapsedTime) override;
        void render(sf::RenderWindow& window) override;
        void shutdown() override;
        void setWorld(World* world) override;
    private:
        bool mSuccess {false};
        std::unique_ptr<Settings> mSettingsPanel {};
        World* mWorld;
    };
}