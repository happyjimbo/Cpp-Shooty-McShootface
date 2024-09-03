#include "StateHandler.h"

#include "TransitionScreen.h"
#include "World.h"

StateHandler::StateHandler(sf::RenderWindow& window, const FontHolder& font) noexcept
: mWindow(window)
, mFont(font)
{
    transitionScreen("Shooty Mcshootface", "Play now!");
}

void StateHandler::startGame()
{
    delete mTransitionScreen;
    mTransitionScreen = nullptr;

    //mWorld = std::make_unique<World>(mWindow, mFont, [this]() { endGame(); });
    mWorld = new World(mWindow, mFont, [this]() { transitionScreen("YOU DIED", "Play again!"); });

}

void StateHandler::transitionScreen(const char* title, const char* buttonText)
{
    delete mWorld;
    mWorld = nullptr;

    mTransitionScreen = new TransitionScreen(mWindow, mFont, title, buttonText);

}

void StateHandler::update(const sf::Time elapsedTime) const
{
    if (mWorld)
    {
        mWorld->update(elapsedTime);
    }
}

void StateHandler::processWindowEvents(const sf::Event& event)
{
    if (mTransitionScreen)
    {
        mTransitionScreen->handleEvent(event, [this]()
        {
            startGame();
        });
    }
}

void StateHandler::draw() const
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

StateHandler::~StateHandler() noexcept
{
    delete mWorld;
    delete mTransitionScreen;
}
