#include <SFML/Graphics/RenderTarget.hpp>
#include "ProjectileEntity.h"
#include "ResourceHolder.h"

void ProjectileEntity::create(const Type type, const TextureHolder &textures)
{
    auto& texture = textures.get(toTextureID(type));
    if (mSprite.getTexture() != &texture)
    {
        mSprite.setTexture(texture);
    }

    mType = type;

    const sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void ProjectileEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}

ProjectileEntity::Type ProjectileEntity::getType() const noexcept
{
    return mType;
}

constexpr Textures::ID ProjectileEntity::toTextureID(const Type type) noexcept
{
    switch (type) {
        case Player:
            return Textures::Bullet;

        default:
            return Textures::EnemyBullet;
    }
}
