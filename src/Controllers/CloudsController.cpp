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
    auto& texture = mTexture.get(Textures::Clouds);
    auto rect = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y);

    for (std::size_t i = 0; i < mScrollSpeedOffsets.size(); i++)
    {
        CloudEntity* cloudSprite = mEntitySystem.createObject(texture, rect, mScrollSpeed);

        CloudData& cloudData = cloudSprite->getCloudData();
        cloudData.scrollSpeedOffset = mScrollSpeedOffsets[i];

        const float yPos = static_cast<float>(-rect.getSize().y * i);
        cloudSprite->setPosition(cloudData.generateRandomXpos(), (yPos * mScrollSpeedOffsets[i]));
    }
}
