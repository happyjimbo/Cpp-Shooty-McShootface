#include "SpriteEntity.h"
#include "SFML/Graphics/RenderTarget.hpp"

SpriteEntity::SpriteEntity(const sf::Texture& texture)
: mSprite(texture)
{
}

SpriteEntity::SpriteEntity(const sf::Texture& texture, const sf::IntRect& rect)
: mSprite(texture, rect)
{
}

void SpriteEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}