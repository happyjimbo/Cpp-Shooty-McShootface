#ifndef CMAKESFMLPROJECT_AIRCRAFT_H
#define CMAKESFMLPROJECT_AIRCRAFT_H

#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

#include "EntityObject.h"

class Aircraft final : public EntityObject
{
    public:
        enum Type {
            Eagle,
            Raptor
        };

    public:
                            Aircraft(Type type, const TextureHolder& textures);
    void                    hit();

    unsigned int	        getCategory() const override;
    void                    update(sf::Time delta) override;
    void                    drawEntity(sf::RenderTarget& target, sf::RenderStates states) const override;
    void                    draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        Type                mType;
        sf::Sprite          mSprite;

};

#endif //CMAKESFMLPROJECT_AIRCRAFT_H