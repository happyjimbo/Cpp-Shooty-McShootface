#include "BackgroundController.h"
#include "ResourceHolder.h"

BackgroundController::BackgroundController (
    EntitySystem<SpriteEntity>& entitySystem,
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

void BackgroundController::createBackground()
{
    auto& texture = mTexture.get(Textures::Desert);

    sf::IntRect textureRect(sf::FloatRect(0,0, mBounds.x, mBounds.y));
    texture.setRepeated(true);

    for (std::size_t i = 0; i < 2; i++) {
        auto* mBackgroundSprite = mEntitySystem.createObject(texture, textureRect);
        mBackgroundSprite->setPosition(0, -mBounds.y * i);
        mBackgroundSprites.push_back(mBackgroundSprite);
    }
}

void BackgroundController::tick(const sf::Time delta) const
{
    for (auto* mBackgroundSprite : mBackgroundSprites) {
        mBackgroundSprite->move(0.f, -mScrollSpeed * delta.asSeconds());

        if (mBackgroundSprite->getPosition().y > mBounds.y) {
            mBackgroundSprite->setPosition(0, -mBounds.y+1);
        }
    }

}

BackgroundController::~BackgroundController()
{
    mBackgroundSprites.clear();
}
