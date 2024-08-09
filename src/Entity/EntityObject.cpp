#include <EntityObject.h>
#include "Command.h"
#include "Category.h"


void EntityObject::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void EntityObject::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f EntityObject::getVelocity() const
{
    return mVelocity;
}

void EntityObject::accelerate(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void EntityObject::accelerate(float ux, float uy)
{
    mVelocity.x += ux;
    mVelocity.y += uy;
}

void EntityObject::update(sf::Time delta)
{
    move(mVelocity * delta.asSeconds());
}

void EntityObject::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
    draw(target, states);
}

void EntityObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
}

unsigned int EntityObject::getCategory() const {
    return Category::Scene;
}

void EntityObject::onCommand(const Command& command, sf::Time dt)
{
    if (command.category & getCategory())
    {
        command.entityAction(*this, dt);
    }
}