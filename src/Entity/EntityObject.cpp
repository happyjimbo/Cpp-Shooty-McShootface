#include <EntityObject.h>
#include "Command.h"
#include "Category.h"


void EntityObject::setVelocity(const sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void EntityObject::setVelocity(const float vx, const float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f EntityObject::getVelocity() const
{
    return mVelocity;
}

void EntityObject::accelerate(const sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void EntityObject::accelerate(const float ux, const float uy)
{
    mVelocity.x += ux;
    mVelocity.y += uy;
}

void EntityObject::update(const sf::Time delta)
{
    move(mVelocity * delta.asSeconds());
}

void EntityObject::draw(const sf::RenderTarget& target, const sf::RenderStates& states) const
{

}

unsigned int EntityObject::getCategory() const
{
    return Category::Scene;
}