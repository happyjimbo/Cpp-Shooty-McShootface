#include <AircraftEntity.h>
#include <Resource/ResourceHolder.h>
#include "../Category.h"
#include <Controllers/ProjectileController.h>

Textures::ID toTextureID(const AircraftEntity::Type type)
{
    switch (type) {
        case AircraftEntity::Eagle:
            return Textures::Eagle;

        case AircraftEntity::Raptor:
            return Textures::Raptor;
    }
    return Textures::Eagle;
}

AircraftEntity::AircraftEntity(ProjectileController& projectileController, const Type type, const TextureHolder& textures)
: mProjectileController(projectileController)
, mType(type)
, mSprite(textures.get(toTextureID(type)))
{
    const sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int AircraftEntity::getCategory() const
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

        const sf::Vector2f spawnPosition = getPosition();
        mPosition = mPosition == Left ? Right : Left;
        const float xOffset = mPosition == Left ? -mXOffsetAmount : mXOffsetAmount;
        const auto spawnPos = sf::Vector2f(spawnPosition.x - xOffset, spawnPosition.y - mYOffsetAmount);

        mProjectileController.spawn(type, spawnPos);
    }
}

void AircraftEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
