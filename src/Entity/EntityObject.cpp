#include "EntityObject.h"
#include "Category.h"
#include <SFML/System/Time.hpp>

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

const sf::Vector2f& EntityObject::getPosition() const noexcept
{
    return mTransformable.getPosition();
}

void EntityObject::setPosition(float x, float y) noexcept
{
    mTransformable.setPosition(x, y);
}
void EntityObject::setPosition(const sf::Vector2f& position) noexcept
{
    mTransformable.setPosition(position);
}

void EntityObject::move(float offsetX, float offsetY)
{
    mTransformable.move(offsetX, offsetY);
}

void EntityObject::move(const sf::Vector2f& offset)
{
    mTransformable.move(offset);
}

void EntityObject::update(const sf::Time delta)
{
    mTransformable.move(mVelocity * delta.asSeconds());
}

void EntityObject::draw(sf::RenderTarget&, sf::RenderStates) const
{

}

void EntityObject::reset()
{
    mTransformable.setPosition(100.f, 100.f);
    setVelocity(sf::Vector2f(0, 0));
}

unsigned int EntityObject::getCategory() const noexcept
{
    return Category::Scene;
}

const sf::Transform& EntityObject::getTransform() const
{
    return mTransformable.getTransform();
}