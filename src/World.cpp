#include "World.h"
#include "SpriteNode.h"
#include "Projectile.h"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayer()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
, mPlayerAircraft(nullptr)
{
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time delta)
{
    mWorldView.move(0.f, mScrollSpeed * delta.asSeconds());
    mPlayerAircraft->setVelocity(0.f, 0.f);

    while (!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), delta);
    }

    adaptPlayerVelocity();
    mProjectileController->tick(delta, mPlayerAircraft->getPosition(), mScrollSpeed);

    mSceneGraph.update(delta);
    adaptPlayerPosition();
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::loadTextures()
{
    mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
    mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
    mTextures.load(Textures::PlayerBullet, "Media/Textures/Bullet.png");
}

void World::buildScene()
{
    for (std::size_t i = 0; i < LayerCount; i++)
    {
        SceneNode::Ptr layer(std::make_unique<SceneNode>());
        mSceneLayer[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepare tiled background
    sf::Texture& texture = mTextures.get(Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(std::make_unique<SpriteNode>(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayer[Background]->attachChild(std::move(backgroundSprite));

    std::unique_ptr<Aircraft> leader(std::make_unique<Aircraft>(Aircraft::Eagle, mTextures));
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
    mSceneLayer[Air]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort(std::make_unique<Aircraft>(Aircraft::Raptor, mTextures));
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(std::make_unique<Aircraft>(Aircraft::Raptor, mTextures));
    rightEscort->setPosition(80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));

    std::unique_ptr<ProjectileController> projectileController (std::make_unique<ProjectileController>(mTextures));
    mProjectileController = projectileController.get();
    mSceneLayer[Air]->attachChild(std::move(projectileController));
}

void World::adaptPlayerPosition()
{
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    const float borderDistance = 40.f;

    sf::Vector2f position = mPlayerAircraft->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity()
{
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

    mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}