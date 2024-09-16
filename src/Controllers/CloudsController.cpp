#include "CloudsController.h"
#include "ResourceHolder.h"

namespace
{
    const std::vector<float> scrollSpeedOffsets = {0.3f, 0.6f, 0.9f, 1.2f};
}

CloudsController::CloudsController (EntitySystem<CloudEntity>& entitySystem, TextureHolder& texture, const float scrollSpeed) noexcept
: mEntitySystem(entitySystem)
, mTexture(texture)
, mScrollSpeed(scrollSpeed)
{
}

void CloudsController::create() const
{
    auto& texture = mTexture.get(Textures::Clouds);
    auto rect = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y);

    for (std::size_t i = 0; i < scrollSpeedOffsets.size(); i++)
    {
        CloudEntity* cloudSprite = mEntitySystem.createObject(texture, rect, mScrollSpeed);

        CloudData& cloudData = cloudSprite->getCloudData();
        cloudData.scrollSpeedOffset = scrollSpeedOffsets[i];

        const float yPos = static_cast<float>(-rect.getSize().y * i);
        cloudSprite->setPosition(cloudData.generateRandomXpos(), (yPos * scrollSpeedOffsets[i]));
    }
}
