#ifndef CMAKESFMLPROJECT_AIRCRAFT_H
#define CMAKESFMLPROJECT_AIRCRAFT_H

#include "../ResourceIdentifiers.h"
#include <../../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/Sprite.hpp>

#include "EntityObject.h"
#include "ProjectileEntity.h"

class ProjectileController;

class AircraftEntity final : public EntityObject
{
    public:
        enum Type {
            Eagle,
            Raptor
        };

    public:
                            AircraftEntity(ProjectileController& projectileController, Type type, const TextureHolder& textures);
    unsigned int	        getCategory() const override;
    void                    update(sf::Time delta) override;
    void                    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void                    triggerProjectile(ProjectileEntity::Type type) const;
    void                    hit();

    private:
        Type                        mType;
        sf::Sprite                  mSprite;
        ProjectileController&       mProjectileController;

};

#endif //CMAKESFMLPROJECT_AIRCRAFT_H