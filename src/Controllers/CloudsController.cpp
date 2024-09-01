#include <CloudsController.h>

#include <iostream>

#include <RandomFloatGenerator.h>
#include <ResourceHolder.h>

CloudsController::CloudsController (EntitySystem<SpriteEntity>& entitySystem, TextureHolder& texture, const float scrollSpeed) noexcept
: mEntitySystem(entitySystem)
, mTexture(texture)
, mScrollSpeed(scrollSpeed * 2.f)
{

}

void CloudsController::create()
{
    auto& cloudsTexture = mTexture.get(Textures::Clouds);
    cloudRect = sf::IntRect(0, 0, cloudsTexture.getSize().x, cloudsTexture.getSize().y);

    for (std::size_t i = 0; i < mScrollSpeedOffsets.size(); i++)
    {
        auto* cloudSprite = mEntitySystem.createObject(cloudsTexture, cloudRect);
        cloudSprite->setScale(1.5f,1);
        const float yPos = -cloudRect.getSize().y * static_cast<float>(i);;
        cloudSprite->setPosition(generateRandomXpos(), (yPos * mScrollSpeedOffsets[i]));
        mSprites.push_back(cloudSprite);
    }
}

void CloudsController::tick(const sf::Time delta) const
{
    for (std::size_t i = 0; i < mScrollSpeedOffsets.size(); i++)
    {
        auto* cloudSprite = mSprites[i];

        cloudSprite->move(0.f, -(mScrollSpeed * mScrollSpeedOffsets[i]) * delta.asSeconds());

        if (cloudSprite->getPosition().y > cloudRect.getSize().y)
        {
            cloudSprite->setPosition(generateRandomXpos(), -cloudRect.getSize().y+1);
        }
    }
}

float CloudsController::generateRandomXpos()
{
    return generateRandomFloat(-10.f, 20.f);
}
