#ifndef CMAKESFMLPROJECT_ENTITY_H
#define CMAKESFMLPROJECT_ENTITY_H

#include "SceneNode.h"

class Entity : public SceneNode
{
    public:
        void                    setVelocity(sf::Vector2f);
        void                    setVelocity(float vx, float vy);
        void                    accelerate(sf::Vector2f velocity);
        void                    accelerate(float ux, float uy);
        sf::Vector2f            getVelocity();

    private:
        void                    updateCurrent(sf::Time delta) override;

    private:
        sf::Vector2f            mVelocity;

};

#endif //CMAKESFMLPROJECT_ENTITY_H
