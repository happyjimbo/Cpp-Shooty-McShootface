#include "BackgroundController.h"
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
, mScrollSpeed(scrollSpeed *0.5f)
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
        mSprites.push_back(backgroundSprite);
    }
}

void BackgroundController::tick(const sf::Time delta) const
{
    for (auto* backgroundSprite : mSprites) {
        backgroundSprite->move(0.f, -mScrollSpeed * delta.asSeconds());

        if (backgroundSprite->getPosition().y > mBounds.y)
        {
            backgroundSprite->setPosition(0, -mBounds.y+1);
        }
    }
}

BackgroundController::~BackgroundController()
{
    mSprites.clear();
}
