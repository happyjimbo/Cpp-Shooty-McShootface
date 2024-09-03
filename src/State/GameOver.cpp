#include "GameOver.h"
#include "MediaFiles.h"

#include <SFML/Graphics/RenderWindow.hpp>

GameOver::GameOver(sf::RenderWindow& window) noexcept
: mWindow(window)
, mWorldView(window.getDefaultView())
{
    mFonts.load(Fonts::Main, MediaFiles::Font);

    mGameOverLabel.create("YOU DIED", mFonts, 100);
    mGameOverLabel.setPosition(80, 150); // drive via screen and label rect
}

void GameOver::draw() const
{
    mWindow.setView(mWorldView);
    mWindow.draw(mGameOverLabel);
}