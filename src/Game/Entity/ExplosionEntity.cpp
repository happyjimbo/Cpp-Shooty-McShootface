#include "ExplosionEntity.h"

#include <SFML/Graphics/RenderTarget.hpp>


void ExplosionEntity::create(const sf::Texture& texture, const sf::IntRect& rect)
{
    if (mSprite.getTexture() != &texture)
    {
        mSprite.setTexture(texture);
    }
    mSprite.setTextureRect(rect);

    mExplosionData.reset();
}

void ExplosionEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}

void ExplosionEntity::setTextureRect(const sf::IntRect rect)
{
    mSprite.setTextureRect(rect);
}