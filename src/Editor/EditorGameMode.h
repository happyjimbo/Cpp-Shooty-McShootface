#pragma once

#include "IGameMode.h"
#include "GameSettings.h"
#include "Settings.h"

struct GameSettingsData;

namespace GameMode
{
    class EditorGameMode : public IGameMode
    {
    public:
        sf::VideoMode determineVideoMode([[maybe_unused]] const GameSettingsData& settings) const override;
        void init(sf::RenderWindow& window, [[maybe_unused]]std::shared_ptr<GameSettings>& gameSettings) override;
        bool isWindowOpen(sf::RenderWindow& window) override;
        void processEvent(sf::Event& event) override;
        bool update(sf::RenderWindow& window, const sf::Time& elapsedTime) override;
        void render(sf::RenderWindow& window) override;
        void shutdown() override;
    private:
        bool success {false};
        std::unique_ptr<Settings> settingsPanel {};
    };
}