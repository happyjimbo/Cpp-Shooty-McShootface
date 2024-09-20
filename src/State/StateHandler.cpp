#include "StateHandler.h"
#include "TransitionScreen.h"
#include "World.h"

struct StateHandler::Impl
{
    std::unique_ptr<World> mWorld;
    std::unique_ptr<TransitionScreen> mTransitionScreen;

    sf::RenderWindow& mWindow;
    const FontHolder& mFont;

    Impl(sf::RenderWindow& window, const FontHolder& font) noexcept
    : mWindow(window)
    , mFont(font)
    {
        transitionScreen("Shooty Mcshootface", "Play now!");
    }

    void startGame()
    {
        mTransitionScreen.reset();
        mTransitionScreen = nullptr;

        mWorld = std::make_unique<World>(mWindow, mFont, [this]()
        {
            transitionScreen("YOU DIED", "Play again!");
        });
    }

    void transitionScreen(const char* title, const char* buttonText)
    {
        mWorld.reset();
        mWorld = nullptr;
        mTransitionScreen = std::make_unique<TransitionScreen>(mWindow, mFont, title, buttonText);
    }

    void update(const sf::Time elapsedTime) const
    {
        if (mWorld)
        {
            mWorld->update(elapsedTime);
        }
    }

    void processWindowEvents(const sf::Event& event)
    {
        if (mTransitionScreen)
        {
            mTransitionScreen->handleEvent(event, [this]()
            {
                startGame();
            });
        }
    }

    void draw() const
    {
        if (mWorld)
        {
            mWorld->draw();
        }

        if (mTransitionScreen)
        {
            mTransitionScreen->draw();
        }
    }
};

StateHandler::StateHandler(sf::RenderWindow& window, const FontHolder& font) noexcept
: mImpl(std::make_unique<Impl>(window, font))
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