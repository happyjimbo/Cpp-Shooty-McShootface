#include "AircraftEntity.h"
#include "ResourceHolder.h"
#include "Category.h"
#include "EntitySystem.h"
#include <SFML/Graphics/Shader.hpp>

using Aircraft::AircraftEntity;

namespace
{
    constexpr float MaxTime = 0.5f;
}

void AircraftEntity::create(
    const Type type,
    const TextureHolder& textures,
    ShaderHolder& shaders,
    const int health)
{
    auto& texture = textures.get(toTextureID(type));

    flashShader = &shaders.get(Shaders::Flash);
    flashShader->setUniform("flashColor", sf::Glsl::Vec4(1.0, 0, 0, 1.0));

    if (mSprite.getTexture() != &texture)
    {
        mSprite.setTexture(texture);
    }

    mType = type;
    mAircraftData.mHealth = health;
    mAircraftData.isFlashing = false;
    mAircraftData.flashingAccumulatedTime = 0;

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
    flashShader->setUniform("time",
        mAircraftData.isFlashing ? mAircraftData.flashingAccumulatedTime : 0.0f);

    states.transform *= getTransform();
    states.shader = flashShader;
    target.draw(mSprite, states);
}

void AircraftEntity::update(const sf::Time delta)
{
    EntityObject::update(delta);

    if (mAircraftData.isFlashing)
    {
        mAircraftData.flashingAccumulatedTime += delta.asSeconds();
        if (mAircraftData.flashingAccumulatedTime > MaxTime)
        {
            mAircraftData.isFlashing = false;
        }
    }
    else
    {
        mAircraftData.flashingAccumulatedTime = 0;
    }
}


constexpr Textures::ID AircraftEntity::toTextureID(const Type type) noexcept
{
    switch (type) {
        case Eagle:
            return Textures::Eagle;

        case Raptor:
            return Textures::Raptor;
    }
    return Textures::Eagle;
}