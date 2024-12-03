#include "StateHandler.h"
#include "TransitionScreen.h"
#include "World.h"
#include "Settings.h"

#include <imgui-SFML.h>

#include "Performance.h"

struct StateHandler::Impl
{
    std::unique_ptr<World> world;
    std::unique_ptr<TransitionScreen> transitionScreen;

    sf::RenderWindow& window;
    sf::RenderTexture& gameRenderTexture;
    const FontHolder& font;
    const CursorState& gameRenderTextureState;

    const Settings settings;

    Impl(sf::RenderWindow& window, sf::RenderTexture& gameRenderTexture, const FontHolder& font, const CursorState& gameRenderTextureState) noexcept
    : window(window)
    , gameRenderTexture(gameRenderTexture)
    , font(font)
    , gameRenderTextureState(gameRenderTextureState)
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
        transitionScreen = std::make_unique<TransitionScreen>(gameRenderTexture, font, title, buttonText);
    }

    void update(const sf::Time elapsedTime) const
    {
        ImGui::SFML::Update(window, elapsedTime);
        Performance::update(elapsedTime.asSeconds());

        if (world && !settings.isPaused())
        {
            world->update(elapsedTime);
        }
    }

    void processWindowEvents(const sf::Event& event)
    {
        if (transitionScreen)
        {
            transitionScreen->handleEvent(event, gameRenderTextureState, [this]()
            {
                startGame();
            });
        }
    }

    void draw() const
    {
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

StateHandler::StateHandler(sf::RenderWindow& window, sf::RenderTexture& gameRenderTexture, const FontHolder& font, const CursorState& gameRenderTextureState) noexcept
: mImpl(std::make_unique<Impl>(window, gameRenderTexture, font, gameRenderTextureState))
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