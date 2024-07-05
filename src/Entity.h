#ifndef CMAKESFMLPROJECT_ENTITY_H
#define CMAKESFMLPROJECT_ENTITY_H

#include "SceneNode.h"

class Entity : public SceneNode
{
    public:
        void                    setVelocity(sf::Vector2f);
        void                    setVelocity(float vx, float vy);
        sf::Vector2f            getVelocity();

    private:
        virtual void            updateCurrent(sf::Time delta);

    private:
        sf::Vector2f            mVelocity;

};

#endif //CMAKESFMLPROJECT_ENTITY_H