#include "ExplosionController.h"
#include "ResourceHolder.h"
#include "SoundEffects.h"

ExplosionController::ExplosionController(
    EntitySystem<ExplosionEntity>& entitySystem,
    TextureHolder& texture,
    SoundEffects& soundEffects
    ) noexcept
: mEntitySystem(entitySystem)
, mTexture(texture)
, mSoundEffects(soundEffects)
{

}

void ExplosionController::spawn(const sf::Vector2f& spawnPosition, const Textures::ID textureId, const Sounds::ID soundId)
{
    constexpr int spriteSize = AnimationData::spriteSize;
    constexpr int spriteOffset = spriteSize / 2;

    auto& texture = mTexture.get(textureId);
    mExplosionRect = sf::IntRect(0, 0, spriteSize, spriteSize);

    auto* explosionSprite = mEntitySystem.createObject(texture, mExplosionRect);

    explosionSprite->setPosition(spawnPosition.x - spriteOffset, spawnPosition.y - spriteOffset);

    mSoundEffects.play(soundId);
}