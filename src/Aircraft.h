#ifndef CMAKESFMLPROJECT_AIRCRAFT_H
#define CMAKESFMLPROJECT_AIRCRAFT_H

#include "Entity.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

class Aircraft : public Entity
{
    public:
        enum Type {
            Eagle,
            Raptor
        };

    public:
                            Aircraft(const Type type, const TextureHolder& textures);
    unsigned int	getCategory() const override;
    void                    hit();


    private:
        virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Type                mType;
        sf::Sprite          mSprite;

};

#endif //CMAKESFMLPROJECT_AIRCRAFT_H