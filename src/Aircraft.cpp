#include "Aircraft.h"
#include "ResourceHolder.h"
#include "Category.h"

Textures::ID toTextureID(Aircraft::Type type)
{
    switch (type) {
        case Aircraft::Eagle:
            return Textures::Eagle;

        case Aircraft::Raptor:
            return Textures::Raptor;
    }
    return Textures::Eagle;
}

Aircraft::Aircraft(const Type type, const TextureHolder& textures)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
{
    const sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
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

void Aircraft::update(sf::Time delta)
{
    move(mVelocity * delta.asSeconds());
}