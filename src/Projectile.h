#ifndef CMAKESFMLPROJECT_PROJECTILE_H
#define CMAKESFMLPROJECT_PROJECTILE_H

#include "Entity.h"
#include "ResourceIdentifiers.h"

#include "SFML/Graphics/Sprite.hpp"

class Projectile final : public Entity
{
    public:
        enum Type {
            Player
        };

    public:
                            Projectile(Type type, const TextureHolder& textures);
    private:
        virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite          mSprite;
};

#endif // CMAKESFMLPROJECT_PROJECTILE_H