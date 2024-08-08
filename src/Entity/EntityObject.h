#ifndef CMAKESFMLPROJECT_ENTITY_OBJECT_H
#define CMAKESFMLPROJECT_ENTITY_OBJECT_H

#include "SceneNode.h"

class EntityObject : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        void                    setVelocity(sf::Vector2f);
        void                    setVelocity(float vx, float vy);
        void                    accelerate(sf::Vector2f velocity);
        void                    accelerate(float ux, float uy);
        sf::Vector2f            getVelocity() const;


        virtual unsigned int    getCategory() const;
        virtual void            update(sf::Time delta);
        virtual void            drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

        void                    onCommand(const Command& command, sf::Time dt);

    private:
        void                     draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    public:
        sf::Vector2f            mVelocity;

};

#endif //CMAKESFMLPROJECT_ENTITY_OBJECT_H

