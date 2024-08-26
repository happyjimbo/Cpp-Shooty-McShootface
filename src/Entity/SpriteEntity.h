#pragma once

#include <EntityObject.h>
#include "SFML/Graphics/Sprite.hpp"

namespace sf {
    class RenderTarget;
    class RenderStates;
}

class SpriteEntity final : public EntityObject
{
public:
    explicit SpriteEntity(const sf::Texture&);
    SpriteEntity(const sf::Texture&, const sf::IntRect&);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite mSprite;
};