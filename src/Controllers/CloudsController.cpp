#include "CloudsController.h"
#include "ResourceHolder.h"

CloudsController::CloudsController (EntitySystem<CloudEntity>& entitySystem, TextureHolder& texture, const float scrollSpeed) noexcept
: mEntitySystem(entitySystem)
, mTexture(texture)
, mScrollSpeed(scrollSpeed)
{
}

void CloudsController::create() const
{
    auto& cloudsTexture = mTexture.get(Textures::Clouds);
    auto cloudRect = sf::IntRect(0, 0, cloudsTexture.getSize().x, cloudsTexture.getSize().y);

    for (std::size_t i = 0; i < mScrollSpeedOffsets.size(); i++)
    {
        CloudEntity* cloudSprite = mEntitySystem.createObject(cloudsTexture, cloudRect, mScrollSpeed);

        CloudData& cloudData = cloudSprite->getCloudData();
        cloudData.scrollSpeedOffset = mScrollSpeedOffsets[i];

        const float yPos = -cloudData.cloudRect.getSize().y * i;
        cloudSprite->setPosition(cloudData.generateRandomXpos(), (yPos * mScrollSpeedOffsets[i]));
    }
}
