#include <BackgroundInitializer.h>
#include <ResourceHolder.h>

BackgroundInitializer::BackgroundInitializer (
    EntitySystem<BackgroundEntity>& entitySystem,
    TextureHolder& texture,
    const sf::Vector2u bounds,
    const float scrollSpeed
)
{
    constexpr float backgroundCount {2};
    entitySystem.prePool(backgroundCount);

    auto& backgroundTexture = texture.get(Textures::Background);
    backgroundTexture.setRepeated(true);

    for (std::size_t i = 0; i < backgroundCount; i++)
    {
        auto* backgroundSprite = entitySystem.createObject(backgroundTexture, bounds, scrollSpeed);
        const float yPos = static_cast<float>(bounds.y * i);
        backgroundSprite->setPosition(0, -yPos);
    }
}