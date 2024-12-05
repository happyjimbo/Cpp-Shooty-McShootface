#include "CloudsInitializer.h"
#include "ResourceHolder.h"


CloudsInitializer::CloudsInitializer (EntitySystem<CloudEntity>& entitySystem, TextureHolder& textures, ShaderHolder& shaders, const float scrollSpeed)
{
    constexpr std::array scrollSpeedOffsets = {0.3f, 0.6f, 0.9f, 1.2f};
    constexpr size_t scrollSize = scrollSpeedOffsets.size();

    entitySystem.prePool(scrollSize);

    const auto& cloudTexture = textures.get(Textures::Clouds);
    const auto rect = sf::IntRect(0, 0, cloudTexture.getSize().x, cloudTexture.getSize().y);

    for (std::size_t i = 0; i < scrollSize; i++)
    {
        CloudEntity* cloudSprite = entitySystem.createObject(cloudTexture, textures, shaders, rect, scrollSpeed);

        CloudData& cloudData = cloudSprite->getCloudData();
        cloudData.scrollSpeedOffset = scrollSpeedOffsets[i];

        const float yPos = static_cast<float>(-rect.getSize().y * i);
        cloudSprite->setPosition(cloudData.generateRandomXpos(), (yPos * scrollSpeedOffsets[i]));
    }
}
