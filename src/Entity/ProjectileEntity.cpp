#include "ProjectileEntity.h"
#include <Resource/ResourceHolder.h>
#include "../Category.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Time.hpp"


Textures::ID toTextureID(const ProjectileEntity::Type type)
{
    switch (type) {
        case ProjectileEntity::Player:
            return Textures::Bullet;

        // TODO: change this
        case ProjectileEntity::Enemy:
            return Textures::Bullet;
    }

    return Textures::Bullet;
}

ProjectileEntity::ProjectileEntity(const Type type, const TextureHolder &textures)
: mSprite(textures.get(toTextureID(type)))
, mType(type)
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

ProjectileEntity::Type ProjectileEntity::getType() const
{
    return mType;
}

unsigned int ProjectileEntity::getCategory() const
{
    switch (mType)
    {
        case Player:
            return Category::PlayerProjectile;

        default:
            return Category::EnemyAircraft;
    }
}

