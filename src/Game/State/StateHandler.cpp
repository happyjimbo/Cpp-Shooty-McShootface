#include "StateHandler.h"

#include <tracy/Tracy.hpp>

#include "GameSettingsData.h"
#include "TransitionScreen.h"
#include "World.h"
#include "SoundSettings.h"

struct StateHandler::Impl
{
    std::unique_ptr<World> world;
    std::unique_ptr<TransitionScreen> transitionScreen;

    sf::RenderWindow& window;
    sf::RenderTexture& gameRenderTexture;
    const FontHolder& font;

    SoundSettings soundSettings;

    Impl(sf::RenderWindow& window, sf::RenderTexture& gameRenderTexture, const FontHolder& font) noexcept
    : window(window)
    , gameRenderTexture(gameRenderTexture)
    , font(font)
    {
        showTransitionScreen("Shooty Mcshootface", "Play now!");
    }

    void startGame()
    {
        transitionScreen.reset();
        transitionScreen = nullptr;

        world = std::make_unique<World>(gameRenderTexture, font, soundSettings, [this]()
        {
            showTransitionScreen("YOU DIED", "Play again!");
        });
    }

    void showTransitionScreen(const char* title, const char* buttonText)
    {
        world.reset();
        world = nullptr;
        transitionScreen = std::make_unique<TransitionScreen>(window, gameRenderTexture, font, title, buttonText);
    }

    void update(const sf::Time elapsedTime) const
    {
        ZoneScopedN("StateHandler update");

        if (world)
        {
            world->update(elapsedTime);
        }
    }

    void processWindowEvents(const sf::Event& event)
    {
        ZoneScopedN("StateHandler processWindowEvents");

        if (transitionScreen)
        {
            transitionScreen->handleEvent(event, [this]()
            {
                startGame();
            });
        }
    }

    void draw() const
    {
        ZoneScopedN("StateHandler draw");

        if (world)
        {
            world->draw();
        }

        if (transitionScreen)
        {
            transitionScreen->draw();
        }
    }

    void settingsUpdated(const GameSettingsData& settings)
    {
        soundSettings.isMuted = settings.mute;
    }
};

StateHandler::StateHandler(sf::RenderWindow& window, sf::RenderTexture& gameRenderTexture, const FontHolder& font) noexcept
: mImpl(std::make_unique<Impl>(window, gameRenderTexture, font))
{
}

StateHandler::~StateHandler() noexcept = default;

void StateHandler::update(const sf::Time elapsedTime) const
{
    mImpl->update(elapsedTime);
}

void StateHandler::processWindowEvents(const sf::Event& event) const
{
    mImpl->processWindowEvents(event);
}

void StateHandler::draw() const
{
    mImpl->draw();
}

void StateHandler::settingsUpdated(const GameSettingsData& settings) const
{
    mImpl->settingsUpdated(settings);
}