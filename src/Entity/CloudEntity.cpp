#include "CloudEntity.h"
#include <SFML/Graphics/RenderTarget.hpp>

void CloudEntity::create(const sf::Texture& texture, const sf::IntRect& rect, const float scrollSpeed)
{
    mSprite.setTexture(texture);
    mSprite.setTextureRect(rect);
    mSprite.setScale(sScaleX, sScaleY);

    mCloudData.cloudRect = rect;
    mCloudData.scrollSpeed = scrollSpeed * 2.f;
}

void CloudEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}