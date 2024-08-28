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
    SpriteEntity() = default;
    SpriteEntity(const sf::Texture&, const sf::IntRect&) = delete;

    void create(const sf::Texture&, const sf::IntRect&);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite mSprite;
};