#include "StateHandler.h"

#include <tracy/Tracy.hpp>

#include "TransitionScreen.h"
#include "World.h"
#include "Settings.h"
#ifdef EDITOR_MODE
#include "Performance.h"
#include <imgui-SFML.h>
#endif


struct StateHandler::Impl
{
    std::unique_ptr<World> world;
    std::unique_ptr<TransitionScreen> transitionScreen;

    sf::RenderWindow& window;
    sf::RenderTexture& gameRenderTexture;
    const FontHolder& font;

    const Settings settings;

    Impl(sf::RenderWindow& window, sf::RenderTexture& gameRenderTexture, const FontHolder& font, std::shared_ptr<GameSettings> gameSettings) noexcept
    : window(window)
    , gameRenderTexture(gameRenderTexture)
    , font(font)
    , settings(std::move(gameSettings))
    {
        showTransitionScreen("Shooty Mcshootface", "Play now!");
    }

    void startGame()
    {
        transitionScreen.reset();
        transitionScreen = nullptr;

        world = std::make_unique<World>(gameRenderTexture, font, settings, [this]()
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

#ifdef EDITOR_MODE
        ImGui::SFML::Update(window, elapsedTime);
        Performance::update(elapsedTime.asSeconds());
#endif

        if (world && !settings.isPaused())
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

        settings.draw();

        if (world)
        {
            world->draw();
        }

        if (transitionScreen)
        {
            transitionScreen->draw();
        }
    }
};

StateHandler::StateHandler(sf::RenderWindow& window, sf::RenderTexture& gameRenderTexture, const FontHolder& font, std::shared_ptr<GameSettings> gameSettings) noexcept
: mImpl(std::make_unique<Impl>(window, gameRenderTexture, font, std::move(gameSettings)))
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