#ifndef CMAKESFMLPROJECT_BULLET_H
#define CMAKESFMLPROJECT_BULLET_H

#include "Entity.h"
#include "ResourceIdentifiers.h"

#include "SFML/Graphics/Sprite.hpp"

class Bullet : public Entity
{
    public:
        enum Type {
            Player
        };

    public:
                            Bullet(Type type, const TextureHolder& textures);

    private:
        virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite          mSprite;
};

#endif // CMAKESFMLPROJECT_BULLET_H