#include <AircraftEntity.h>
#include "../ResourceHolder.h"
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
: mprojectileController(projectileController)
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
    move(mVelocity * delta.asSeconds());
}

void AircraftEntity::triggerProjectile(const ProjectileEntity::Type type) const
{
    mprojectileController.spawn(type, getPosition());
}


void AircraftEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
