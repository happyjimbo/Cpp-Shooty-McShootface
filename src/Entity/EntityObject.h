#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

struct Command;

namespace sf {
    class RenderTarget;
    class RenderStates;
    class Time;
}

class EntityObject : public sf::Transformable, public sf::Drawable
{
public:
    EntityObject() = default;
    ~EntityObject() override = default;

    EntityObject(const EntityObject&) = delete;
    EntityObject& operator=(const EntityObject&) = delete;

    EntityObject(EntityObject&&) = delete;
    EntityObject& operator=(EntityObject&&) = delete;

    void setVelocity(sf::Vector2f) noexcept;
    void setVelocity(float vx, float vy) noexcept;
    void accelerate(sf::Vector2f velocity) noexcept;
    void accelerate(float ux, float uy) noexcept;

    sf::Vector2f getVelocity() const noexcept;

    virtual unsigned int getCategory() const noexcept;
    virtual void update(sf::Time delta);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void reset();

protected:
    sf::Vector2f mVelocity;
};