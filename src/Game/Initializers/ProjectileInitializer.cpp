#include "ProjectileInitializer.h"
#include "SoundEffects.h"

namespace
{
    constexpr float Speed = 500.f;
    constexpr int PrePoolAmount = 20;
}

ProjectileInitializer::ProjectileInitializer(
    EntitySystem<ProjectileEntity>& entitySystem,
    const TextureHolder& texture,
    const sf::FloatRect worldBounds,
    SoundEffects& soundEffects
)
: mEntitySystem(entitySystem)
, mTexture(texture)
, mWorldBounds(worldBounds)
, mSoundEffects(soundEffects)
{
    mEntitySystem.prePool(PrePoolAmount);
}

void ProjectileInitializer::spawn(ProjectileEntity::Type type, const sf::Vector2f spawnPosition) const
{
    auto* projectile = mEntitySystem.createObject(type, mTexture);
    projectile->setPosition(spawnPosition);

    const float speed = type == ProjectileEntity::Type::Player ? -Speed : Speed;
    projectile->setVelocity(0, speed);

    mSoundEffects.play(type == ProjectileEntity::Type::Player ? Sounds::PlayerGunfire : Sounds::EnemyGunfire);
}