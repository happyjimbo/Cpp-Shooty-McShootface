#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

struct Command;

class EntityObject : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    void setVelocity(sf::Vector2f);
    void setVelocity(float vx, float vy);
    void accelerate(sf::Vector2f velocity);
    void accelerate(float ux, float uy);

    sf::Vector2f getVelocity() const;

    virtual unsigned int getCategory() const;
    virtual void update(sf::Time delta);
    virtual void draw(const sf::RenderTarget& target, const sf::RenderStates& states) const;

protected:
    sf::Vector2f mVelocity;
};