#ifndef CMAKESFMLPROJECT_SPRITENODE_H
#define CMAKESFMLPROJECT_SPRITENODE_H

#include <EntityObject.h>

#include "../../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/Sprite.hpp"

class SpriteEntity final : public EntityObject
{
public:
    explicit            SpriteEntity(const sf::Texture&);
                        SpriteEntity(const sf::Texture&, const sf::IntRect&);

private:
    void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite          mSprite;
};

#endif //CMAKESFMLPROJECT_SPRITENODE_H