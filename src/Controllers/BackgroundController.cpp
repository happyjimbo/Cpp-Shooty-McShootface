#include <BackgroundController.h>
#include <ResourceHolder.h>

namespace
{
    constexpr float backgroundCount {2};
}

BackgroundController::BackgroundController (
    EntitySystem<BackgroundEntity>& entitySystem,
    TextureHolder& texture,
    const sf::Vector2u bounds,
    const float scrollSpeed
)
{
    auto& backgroundTexture = texture.get(Textures::Background);
    backgroundTexture.setRepeated(true);

    for (std::size_t i = 0; i < backgroundCount; i++)
    {
        auto* backgroundSprite = entitySystem.createObject(backgroundTexture, bounds, scrollSpeed);
        const float yPos = static_cast<float>(bounds.y * i);
        backgroundSprite->setPosition(0, -yPos);
    }
}