#include "Game.h"

#include <imgui-SFML.h>

#include "MediaFiles.h"
#include "StateHandler.h"
#include "TransitionScreen.h"
#include "SFML/Graphics.hpp"
#include "GameSettingsData.h"
#include "GameSettings.h"

struct Game::Impl
{
    GameSettingsData settings;

    sf::RenderWindow window;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    FontHolder font;
    std::unique_ptr<StateHandler> stateHandler;

    const sf::Time TimePerFrame;

    const char* GamePanelName = "Game Panel";

    sf::VideoMode determineVideoMode() const {
        #ifdef EDITOR_MODE
            return sf::VideoMode::getDesktopMode();
        #else
            return sf::VideoMode(settings.width, settings.height);
        #endif
    }

    explicit Impl()
    : settings(GameSettings::getSettings())
    , window(determineVideoMode(), settings.title, sf::Style::Close)
    , TimePerFrame(sf::seconds(1 / static_cast<float>(settings.fps)))
    {
        renderTexture.create(settings.width, settings.height);
        renderSprite.setTexture(renderTexture.getTexture());

        font.load(Fonts::Main, MediaFiles::Font);
        stateHandler = std::make_unique<StateHandler>(window, renderTexture, font);
        window.setKeyRepeatEnabled(false);

        GameSettings::settingsUpdated([this]()
        {
            settingsUpdated();
        });
    }

    void update(const sf::Time elapsedTime) const
    {
        stateHandler->update(elapsedTime);
    }

    void processWindowEvents()
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            stateHandler->processWindowEvents(event);
        }
    }

    void settingsUpdated()
    {
        settings = GameSettings::getSettings();
        renderTexture.create(settings.width, settings.height);
        renderSprite.setTexture(renderTexture.getTexture(), true);
    }

    void renderGame()
    {
        renderTexture.display();
        window.draw(renderSprite);
    }

    void render()
    {
        window.clear(sf::Color::Black);

        stateHandler->draw();

        renderGame();

        ImGui::SFML::Render(window);

        window.setView(window.getDefaultView());
        window.display();
    }
};

Game::Game() noexcept : mImpl(std::make_unique<Impl>()) {}
Game::~Game() noexcept = default;

void Game::run() const
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mImpl->window.setFramerateLimit(144);

    const auto success = ImGui::SFML::Init(mImpl->window);

    while (success && mImpl->window.isOpen())
    {
        const sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > mImpl->TimePerFrame)
        {
            timeSinceLastUpdate -= mImpl->TimePerFrame;
            mImpl->processWindowEvents();
            mImpl->update(mImpl->TimePerFrame);
            mImpl->render();
        }
    }

    ImGui::SFML::Shutdown();
}
