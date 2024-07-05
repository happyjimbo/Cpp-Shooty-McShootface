#ifndef CMAKESFMLPROJECT_AIRCRAFT_H
#define CMAKESFMLPROJECT_AIRCRAFT_H

#include "SceneNode.h"
#include "Entity.h"
#include "ResourceIdentifiers.h"

class Aircraft : public Entity
{
    public:
        enum Type {
            Eagle,
            Raptor
        };

    public:
                            Aircraft(Type type, const TextureHolder& textures);

    private:
        virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Type                mType;
        sf::Sprite          mSprite;

};

#endif //CMAKESFMLPROJECT_AIRCRAFT_H