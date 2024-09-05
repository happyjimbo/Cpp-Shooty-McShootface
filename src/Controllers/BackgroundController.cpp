#include <BackgroundController.h>
#include <ResourceHolder.h>

BackgroundController::BackgroundController (
    EntitySystem<BackgroundEntity>& entitySystem,
    TextureHolder& texture,
    const sf::Vector2u bounds,
    const float scrollSpeed
)
: mEntitySystem(entitySystem)
, mTexture(texture)
, mBounds(bounds)
, mScrollSpeed(scrollSpeed)
{

}

void BackgroundController::create() const
{
    auto& texture = mTexture.get(Textures::Background);
    texture.setRepeated(true);

    for (std::size_t i = 0; i < sBackgroundCount; i++)
    {
        auto* backgroundSprite = mEntitySystem.createObject(texture, mBounds, mScrollSpeed);
        const float yPos = static_cast<float>(mBounds.y * i);
        backgroundSprite->setPosition(0, -yPos);
    }
}