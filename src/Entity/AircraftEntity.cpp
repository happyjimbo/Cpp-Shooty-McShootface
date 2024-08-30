#include "AircraftEntity.h"
#include "ResourceHolder.h"
#include "Category.h"
#include "ProjectileController.h"

using Aircraft::AircraftEntity;

void AircraftEntity::create(const Type type, const TextureHolder& textures)
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

unsigned int AircraftEntity::getCategory() const noexcept
{
    switch (mType)
    {
        case Eagle:
            return Category::PlayerAircraft;

        default:
            return Category::EnemyAircraft;
    }
}

void AircraftEntity::triggerProjectile(const ProjectileEntity::Type& type, const float spawnSpeed)
{
    mProjectileFiringData.needsToFireProjectile = true;
    mProjectileFiringData.speed = spawnSpeed;
    mProjectileFiringData.projectileType = type;
    mProjectileFiringData.position = (mProjectileFiringData.position == ProjectileFiringData::Left) ? ProjectileFiringData::Right : ProjectileFiringData::Left;
}

void AircraftEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}

Textures::ID AircraftEntity::toTextureID(const Type type) noexcept
{
    switch (type) {
        case Eagle:
            return Textures::Eagle;

        case Raptor:
            return Textures::Raptor;
    }
    return Textures::Eagle;
}