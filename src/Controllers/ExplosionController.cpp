#include "ExplosionController.h"
#include "ResourceHolder.h"

ExplosionController::ExplosionController(
    EntitySystem<ExplosionEntity>& entitySystem,
    TextureHolder& texture
    ) noexcept
: mEntitySystem(entitySystem)
, mTexture(texture)
{

}

void ExplosionController::spawn(const sf::Vector2f& spawnPosition, const Textures::ID textureId)
{
    constexpr int spriteSize = AnimationData::spriteSize;
    constexpr int spriteOffset = spriteSize / 2;

    auto& texture = mTexture.get(textureId);
    explosionRect = sf::IntRect(0, 0, spriteSize, spriteSize);

    auto* explosionSprite = mEntitySystem.createObject(texture, explosionRect);

    explosionSprite->setPosition(spawnPosition.x - spriteOffset, spawnPosition.y - spriteOffset);
}