#include "Game.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

#include "GameRenderTextureState.h"
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
    FontHolder font;
    std::unique_ptr<StateHandler> stateHandler;

    GameRenderTextureState gameRenderTextureState;

    const sf::Time TimePerFrame;
    bool isFullscreen = false;

    const char* GamePanelName = "Game Panel";

    explicit Impl()
    : settings(GameSettings::getSettings())
    , window(sf::VideoMode::getDesktopMode(), settings.title, sf::Style::Close)
    , TimePerFrame(sf::seconds(1 / static_cast<float>(settings.fps)))
    {
        renderTexture.create(settings.width, settings.height);

        font.load(Fonts::Main, MediaFiles::Font);
        stateHandler = std::make_unique<StateHandler>(window, renderTexture, font, gameRenderTextureState);
        window.setKeyRepeatEnabled(false);
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

    void render()
    {
        window.clear();

        stateHandler->draw();

        ImGui::Begin(GamePanelName);
        gameRenderTextureState.position = ImGui::GetCursorScreenPos();
        gameRenderTextureState.size = ImGui::GetContentRegionAvail();
        ImGui::Image(renderTexture, sf::Vector2f(settings.width, settings.height));
        ImGui::End();

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
