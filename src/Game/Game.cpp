#include "Game.h"

#include <tracy/Tracy.hpp>

#include "MediaFiles.h"
#include "StateHandler.h"
#include "TransitionScreen.h"
#include "SFML/Graphics.hpp"
#include "GameSettingsData.h"
#include "GameSettings.h"
#include "IGameMode.h"

struct Game::Impl
{
    std::shared_ptr<GameSettings> gameSettings;
    GameSettingsData settings;
    std::unique_ptr<IGameMode> gameMode;

    sf::RenderWindow window;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    FontHolder font;
    std::unique_ptr<StateHandler> stateHandler;

    sf::Event event;

    const sf::Time TimePerFrame;

    const char* GamePanelName = "Game Panel";

    explicit Impl(const std::string& configPath, std::unique_ptr<IGameMode> gMode)
    : gameSettings(std::make_shared<GameSettings>(
        std::make_unique<CsvSerializer<GameSettingsData>>(),
        configPath,
        [this]() { settingsUpdated(); }
    ))
    , settings(gameSettings->getGameSettingsData())
    , gameMode(std::move(gMode))
    , window(gameMode->determineVideoMode(settings), settings.title, sf::Style::Close)
    , TimePerFrame(sf::seconds(1 / static_cast<float>(settings.fps)))
    {
        renderTexture.create(settings.width, settings.height);
        renderSprite.setTexture(renderTexture.getTexture());

        font.load(Fonts::Main, MediaFiles::Font);
        stateHandler = std::make_unique<StateHandler>(window, renderTexture, font);
        window.setKeyRepeatEnabled(false);

        gameMode->setSettings(gameSettings);
    }

    void update(const sf::Time elapsedTime)
    {
        if (gameMode->update(window, elapsedTime))
        {
            stateHandler->update(elapsedTime);
        }
    }

    void processWindowEvents()
    {
        while(window.pollEvent(event))
        {
            gameMode->processEvent(event);
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
        stateHandler->settingsUpdated(settings);
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
        gameMode->render(window);
        window.setView(window.getDefaultView());
        window.display();
    }

    bool isWindowOpen()
    {
        return gameMode->isWindowOpen(window);
    }

    void shutDown() const
    {
        gameMode->shutdown();
    }

};

Game::Game(const std::string& configPath, std::unique_ptr<IGameMode> gameMode) noexcept
: mImpl(std::make_unique<Impl>(configPath, std::move(gameMode)))
{
}

Game::~Game() noexcept = default;

void Game::run()
{
    ZoneScopedN("Game Run");

    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mImpl->window.setFramerateLimit(144);

    while(mImpl->isWindowOpen())
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
    mImpl->shutDown();
}
