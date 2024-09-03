#pragma once
#include "Label.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/View.hpp"

namespace sf { class RenderWindow; }

using GUI::Label;

class GameOver final
{
public:
    explicit GameOver(sf::RenderWindow& window) noexcept;
    ~GameOver() noexcept = default;

    void draw() const;

private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;

    FontHolder mFonts;
    Label mGameOverLabel {};
};