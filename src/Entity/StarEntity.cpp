#include "StarEntity.h"

#include "SFML/Graphics/RenderTarget.hpp"

void StarEntity::create(const sf::Texture& texture)
{
    mSprite.setTexture(texture);

    mSprite.setScale(0.2f, 0.2f);

    const sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void StarEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
