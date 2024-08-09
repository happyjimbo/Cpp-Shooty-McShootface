#include "ProjectileEntity.h"
#include "../ResourceHolder.h"


Textures::ID toTextureID(const ProjectileEntity::Type type)
{
    switch (type) {
        case ProjectileEntity::Player:
            return Textures::Bullet;
    }

    return Textures::Bullet;
}

ProjectileEntity::ProjectileEntity(const Type type, const TextureHolder &textures)
: mSprite(textures.get(toTextureID(type)))
{
    const sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void ProjectileEntity::update(const sf::Time delta)
{
    move(mVelocity * delta.asSeconds());
}

void ProjectileEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
