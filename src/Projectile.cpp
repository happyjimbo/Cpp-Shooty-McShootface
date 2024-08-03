#include "Projectile.h"

#include "Logger.h"
#include "ResourceHolder.h"


Textures::ID toTextureID(Projectile::Type type)
{
    switch (type) {
        case Projectile::Player:
            return Textures::Bullet;
    }

    return Textures::Bullet;
}

Projectile::Projectile(Type type, const TextureHolder &textures)
: mSprite(textures.get(toTextureID(type)))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Projectile::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}