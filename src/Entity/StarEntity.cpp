#include "StarEntity.h"

#include <iostream>
#include <SFML/System/Clock.hpp>

#include "SFML/Graphics/RenderTarget.hpp"

void StarEntity::create(const sf::Texture& texture)
{
    mSprite.setTexture(texture);

    const sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void StarEntity::draw(sf::RenderTarget &target, const sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void StarEntity::update(const sf::Time delta)
{
    EntityObject::update(delta);
}

