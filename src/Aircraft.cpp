#include "Aircraft.h"
#include "ResourceHolder.h"
#include "Category.h"
#include "ProjectileController.h"

Textures::ID toTextureID(const Aircraft::Type type)
{
    switch (type) {
        case Aircraft::Eagle:
            return Textures::Eagle;

        case Aircraft::Raptor:
            return Textures::Raptor;
    }
    return Textures::Eagle;
}

Aircraft::Aircraft(ProjectileController& projectileController, const Type type, const TextureHolder& textures)
: mprojectileController(projectileController)
, mType(type)
, mSprite(textures.get(toTextureID(type)))
{
    const sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Aircraft::getCategory() const
{
    switch (mType)
    {
        case Eagle:
            return Category::PlayerAircraft;

        default:
            return Category::EnemyAircraft;
    }
}

void Aircraft::update(const sf::Time delta)
{
    move(mVelocity * delta.asSeconds());
}

void Aircraft::triggerProjectile(const Projectile::Type type) const
{
    mprojectileController.spawn(type, getPosition());
}


void Aircraft::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
