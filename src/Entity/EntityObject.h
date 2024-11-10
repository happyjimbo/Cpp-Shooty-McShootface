#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

struct Command;

namespace sf {
    class RenderTarget;
    class RenderStates;
    class Time;
    class Drawable;
}

class EntityObject : public sf::Drawable
{
public:
    explicit EntityObject() = default;
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

    const sf::Vector2f& getPosition() const noexcept;
    void setPosition(float x, float y) noexcept;
    void setPosition(const sf::Vector2f& position) noexcept;

    void move(float offsetX, float offsetY);
    void move(const sf::Vector2f& offset);

    virtual void update(sf::Time delta);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void reset();

protected:
    const sf::Transform& getTransform() const;

private:
    sf::Vector2f mVelocity;
    sf::Transformable mTransformable;
};