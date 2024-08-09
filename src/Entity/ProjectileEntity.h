#ifndef CMAKESFMLPROJECT_PROJECTILE_H
#define CMAKESFMLPROJECT_PROJECTILE_H

#include "EntityObject.h"
#include "../ResourceIdentifiers.h"

#include "../../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/Sprite.hpp"

class ProjectileEntity final : public EntityObject
{
    public:
        enum Type {
            Player
        };

    public:
                            ProjectileEntity(Type type, const TextureHolder& textures);
        void                update(sf::Time delta) override;
    private:
        void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Sprite          mSprite;
};

#endif // CMAKESFMLPROJECT_PROJECTILE_H