#include "Game.h"

#ifdef EDITOR_MODE
#include <imgui-SFML.h>
#endif

#include <tracy/Tracy.hpp>

#include "MediaFiles.h"
#include "StateHandler.h"
#include "TransitionScreen.h"
#include "SFML/Graphics.hpp"
#include "GameSettingsData.h"
#include "GameSettings.h"

struct Game::Impl
{
    std::shared_ptr<GameSettings> gameSettings;
    GameSettingsData settings;

    sf::RenderWindow window;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    FontHolder font;
    std::unique_ptr<StateHandler> stateHandler;

    sf::Event event;

    const sf::Time TimePerFrame;

    const char* GamePanelName = "Game Panel";

    sf::VideoMode determineVideoMode() const {
        #ifdef EDITOR_MODE
            return sf::VideoMode::getDesktopMode();
        #else
            return sf::VideoMode(settings.width, settings.height);
        #endif
    }

    explicit Impl(const std::string& configPath)
    : gameSettings(std::make_shared<GameSettings>(
        std::make_unique<CsvSerializerImpl<GameSettingsData>>(),
        configPath,
        [this]() { settingsUpdated(); }
    ))
    , settings(gameSettings->getGameSettingsData())
    , window(determineVideoMode(), settings.title, sf::Style::Close)
    , TimePerFrame(sf::seconds(1 / static_cast<float>(settings.fps)))
    {
        renderTexture.create(settings.width, settings.height);
        renderSprite.setTexture(renderTexture.getTexture());

        font.load(Fonts::Main, MediaFiles::Font);
        stateHandler = std::make_unique<StateHandler>(window, renderTexture, font, gameSettings);
        window.setKeyRepeatEnabled(false);
    }

    void update(const sf::Time elapsedTime) const
    {
        stateHandler->update(elapsedTime);
    }

    void processWindowEvents()
    {
        while(window.pollEvent(event))
        {
#ifdef EDITOR_MODE
            ImGui::SFML::ProcessEvent(event);
#endif

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            stateHandler->processWindowEvents(event);
        }
    }

    void settingsUpdated()
    {
        ZoneScopedN("Game Settings updated");
        settings = gameSettings->getGameSettingsData();
        renderTexture.create(settings.width, settings.height);
        renderSprite.setTexture(renderTexture.getTexture(), true);
    }

    void renderGame()
    {
        ZoneScopedN("Game renderGame");
        renderTexture.display();
        window.draw(renderSprite);
    }

    void render()
    {
        ZoneScopedN("Game render");

        window.clear();

        stateHandler->draw();
        renderGame();
#ifdef EDITOR_MODE
        ImGui::SFML::Render(window);
#endif
        window.setView(window.getDefaultView());
        window.display();
    }
};

Game::Game(const std::string& configPath) noexcept : mImpl(std::make_unique<Impl>(configPath)) {}
Game::~Game() noexcept = default;

void Game::run()
{
    ZoneScopedN("Game Run");

    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mImpl->window.setFramerateLimit(144);

#ifdef EDITOR_MODE
    const auto success = ImGui::SFML::Init(mImpl->window);
    while (success && mImpl->window.isOpen())
#else
    while(mImpl->window.isOpen())
#endif
    {
        timeSinceLastUpdate += mClock.restart();

        while (timeSinceLastUpdate > mImpl->TimePerFrame)
        {
            timeSinceLastUpdate -= mImpl->TimePerFrame;
            mImpl->processWindowEvents();
            mImpl->update(mImpl->TimePerFrame);
            mImpl->render();
        }
    }
#ifdef EDITOR_MODE
    ImGui::SFML::Shutdown();
#endif

}
