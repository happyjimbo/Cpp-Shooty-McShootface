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

    sf::RenderWindow mWindow;
    FontHolder mFont;
    std::unique_ptr<StateHandler> mStateHandler;

    const sf::Time TimePerFrame;

    explicit Impl()
    : settings(GameSettings::getSettings())
    , mWindow(sf::VideoMode(settings.width, settings.height), settings.title, sf::Style::Close)
    , TimePerFrame(sf::seconds(1 / static_cast<float>(settings.fps)))
    {
        mFont.load(Fonts::Main, MediaFiles::Font);
        mStateHandler = std::make_unique<StateHandler>(mWindow, mFont);
        mWindow.setKeyRepeatEnabled(false);
    }

    void update(const sf::Time elapsedTime) const
    {
        mStateHandler->update(elapsedTime);
    }

    void processWindowEvents()
    {
        sf::Event event;
        while(mWindow.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
            }

            mStateHandler->processWindowEvents(event);
        }
    }

    void render()
    {
        mWindow.clear();

        mStateHandler->draw();

        ImGui::SFML::Render(mWindow);

        mWindow.setView(mWindow.getDefaultView());
        mWindow.display();
    }
};

Game::Game() noexcept : mImpl(std::make_unique<Impl>()) {}
Game::~Game() noexcept = default;

void Game::run() const
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mImpl->mWindow.setFramerateLimit(144);

    const auto success = ImGui::SFML::Init(mImpl->mWindow);

    while (success && mImpl->mWindow.isOpen())
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
