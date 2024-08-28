#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

struct Command;

namespace sf {
    class RenderTarget;
    class RenderStates;
    class Time;
}

class EntityObject : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    EntityObject() = default;
    void setVelocity(sf::Vector2f) noexcept;
    void setVelocity(float vx, float vy) noexcept;
    void accelerate(sf::Vector2f velocity) noexcept;
    void accelerate(float ux, float uy) noexcept;

    sf::Vector2f getVelocity() const noexcept;

    virtual unsigned int getCategory() const noexcept;
    virtual void update(sf::Time delta);
    virtual void draw(const sf::RenderTarget& target, const sf::RenderStates& states) const;

    void reset();

protected:
    sf::Vector2f mVelocity;
};