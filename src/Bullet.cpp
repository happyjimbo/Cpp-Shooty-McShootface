#import "Bullet.h"
#import "ResourceHolder.h"

Textures::ID toTextureID(Bullet::Type type)
{
    switch (type) {
        case Bullet::Player:
            return Textures::PlayerBullet;
    }

    return Textures::PlayerBullet;
}

Bullet::Bullet(Type type, const TextureHolder &textures)
: mSprite(textures.get(toTextureID(type)))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}


void Bullet::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}