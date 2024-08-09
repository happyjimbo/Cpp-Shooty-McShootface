#ifndef CMAKESFMLPROJECT_AIRCRAFT_H
#define CMAKESFMLPROJECT_AIRCRAFT_H

#include "ResourceIdentifiers.h"
#include <SFML/Graphics/Sprite.hpp>

#include "EntityObject.h"
#include "Projectile.h"

class ProjectileController;

class Aircraft final : public EntityObject
{
    public:
        enum Type {
            Eagle,
            Raptor
        };

    public:
                            Aircraft(ProjectileController& projectileController, Type type, const TextureHolder& textures);
    unsigned int	        getCategory() const override;
    void                    update(sf::Time delta) override;
    void                    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void                    triggerProjectile(Projectile::Type type) const;
    void                    hit();

    private:
        Type                        mType;
        sf::Sprite                  mSprite;
        ProjectileController&       mprojectileController;

};

#endif //CMAKESFMLPROJECT_AIRCRAFT_H