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
    mTransitionScreen.reset();

    mWorld = std::make_unique<World>(mWindow, mFont, [this]()
    {
        transitionScreen("YOU DIED", "Play again!");
    });
}

void StateHandler::transitionScreen(const char* title, const char* buttonText)
{
    mWorld.reset();
    mTransitionScreen = std::make_unique<TransitionScreen>(mWindow, mFont, title, buttonText);

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