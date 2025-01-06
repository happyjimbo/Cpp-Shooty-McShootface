#pragma once
#include "../IGameMode.h"

#include "GameSettingsData.h"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace GameMode
{
    class StandardGameMode final : public IGameMode
    {
    public:

        sf::VideoMode determineVideoMode(const GameSettingsData& settings) const override
        {
            return sf::VideoMode(settings.width, settings.height);
        }

        void init(sf::RenderWindow&, std::shared_ptr<GameSettings>&) override { }

        bool isWindowOpen(sf::RenderWindow& window) override
        {
            return window.isOpen();
        }

        void processEvent(sf::Event&) override { }

        bool update(sf::RenderWindow&, const sf::Time&) override
        {
            return true;
        }

        void render(sf::RenderWindow&) override { }
        void shutdown() override { }

        void setWorld(World* world) override {}
    };
}