#include "BackgroundController.h"

#include <iostream>
#include <random>
#include <__random/random_device.h>

#include "RandomFloatGenerator.h"
#include "Resource/ResourceHolder.h"

BackgroundController::BackgroundController (
    EntitySystem<SpriteEntity>& entitySystem,
    TextureHolder& texture,
    const sf::Vector2u bounds,
    const float scrollSpeed
)
: mEntitySystem(entitySystem)
, mTexture(texture)
, mBounds(bounds)
, mScrollSpeedBackground(scrollSpeed *0.5f)
, mScrollSpeedClouds(scrollSpeed *2.f)
{

}

void BackgroundController::create()
{
    auto& backgroundTexture = mTexture.get(Textures::Background);

    sf::IntRect textureRect(sf::FloatRect(0,0, mBounds.x, mBounds.y));
    backgroundTexture.setRepeated(true);

    for (std::size_t i = 0; i < 2; i++) {
        auto* backgroundSprite = mEntitySystem.createObject(backgroundTexture, textureRect);
        backgroundSprite->setPosition(0, -mBounds.y * i);
        mBackgroundSprites.push_back(backgroundSprite);
    }

    auto& cloudsTexture = mTexture.get(Textures::Clouds);
    cloudRect = sf::IntRect(sf::FloatRect(0,0, cloudsTexture.getSize().x, cloudsTexture.getSize().y));

    for (std::size_t i = 0; i < 2; i++)
    {
        auto* cloudsSprite = mEntitySystem.createObject(cloudsTexture, cloudRect);
        cloudsSprite->setPosition(0, -cloudRect.getSize().y * i);
        mCloudSprites.push_back(cloudsSprite);
    }
}

void BackgroundController::tick(const sf::Time delta) const
{
    for (auto* backgroundSprite : mBackgroundSprites) {
        backgroundSprite->move(0.f, -mScrollSpeedBackground * delta.asSeconds());

        if (backgroundSprite->getPosition().y > mBounds.y)
        {
            backgroundSprite->setPosition(0, -mBounds.y+1);
        }
    }

    for (auto* cloudSprite : mCloudSprites)
    {
        cloudSprite->move(0.f, -mScrollSpeedClouds * delta.asSeconds());

        if (cloudSprite->getPosition().y > cloudRect.getSize().y)
        {
            cloudSprite->setPosition(0, -cloudRect.getSize().y+1);
        }
    }

}

BackgroundController::~BackgroundController()
{
    mBackgroundSprites.clear();
}
