#include "SpriteEntity.h"
#include "SFML/Graphics/RenderTarget.hpp"

void SpriteEntity::create(const sf::Texture& texture, const sf::IntRect& rect)
{
    mSprite.setTexture(texture);
    mSprite.setTextureRect(rect);
}

void SpriteEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}