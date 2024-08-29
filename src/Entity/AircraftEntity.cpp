#include "AircraftEntity.h"
#include "ResourceHolder.h"
#include "Category.h"
#include "ProjectileController.h"

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

void AircraftEntity::update(const sf::Time delta)
{
    mTimeSinceLastProjectileSpawn += delta.asSeconds();
    move(mVelocity * delta.asSeconds());
}

void AircraftEntity::triggerProjectile(const ProjectileEntity::Type& type, const float spawnSpeed)
{
    if (mTimeSinceLastProjectileSpawn > spawnSpeed) {
        mTimeSinceLastProjectileSpawn = 0;

        mNeedsToFireProjectile = true;
        mProjectileType = type;
        mPosition = mPosition == Left ? Right : Left;
    }
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