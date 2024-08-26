#include <EntityObject.h>
#include <Command/Command.h>
#include "Category.h"


void EntityObject::setVelocity(const sf::Vector2f velocity) noexcept
{
    mVelocity = velocity;
}

void EntityObject::setVelocity(const float vx, const float vy) noexcept
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f EntityObject::getVelocity() const noexcept
{
    return mVelocity;
}

void EntityObject::accelerate(const sf::Vector2f velocity) noexcept
{
    mVelocity += velocity;
}

void EntityObject::accelerate(const float ux, const float uy) noexcept
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

unsigned int EntityObject::getCategory() const noexcept
{
    return Category::Scene;
}