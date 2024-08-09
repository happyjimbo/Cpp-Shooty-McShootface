#include "Projectile.h"
#include "ResourceHolder.h"


Textures::ID toTextureID(const Projectile::Type type)
{
    switch (type) {
        case Projectile::Player:
            return Textures::Bullet;
    }

    return Textures::Bullet;
}

Projectile::Projectile(const Type type, const TextureHolder &textures)
: mSprite(textures.get(toTextureID(type)))
{
    const sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Projectile::update(const sf::Time delta)
{
    move(mVelocity * delta.asSeconds());
}

void Projectile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
