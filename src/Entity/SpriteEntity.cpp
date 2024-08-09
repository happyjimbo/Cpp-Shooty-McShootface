#include "SpriteEntity.h"

SpriteEntity::SpriteEntity(const sf::Texture& texture)
: mSprite(texture)
{
}

SpriteEntity::SpriteEntity(const sf::Texture& texture, const sf::IntRect& rect)
: mSprite(texture, rect)
{
}

void SpriteEntity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
    target.draw(mSprite, states);
}