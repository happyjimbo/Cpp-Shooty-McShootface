#include "BackgroundEntity.h"
#include <SFML/Graphics/RenderTarget.hpp>

void BackgroundEntity::create(const sf::Texture& texture, const sf::Vector2u bounds, const float scrollSpeed)
{
    const auto rect = sf::IntRect(0, 0, bounds.x, bounds.y);
    mSprite.setTextureRect(rect);

    if (mSprite.getTexture() != &texture)
    {
        mSprite.setTexture(texture);
    }

    mBackgrounData.bounds = bounds;
    mBackgrounData.scrollSpeed = scrollSpeed * 0.5f;
}

void BackgroundEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}