#include "World.h"

#include "Entity/SpriteEntity.h"
#include "EnemyAircraftController.h"
#include "ProjectileCollisionController.h"
#include <Gui/Label.h>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mFonts()
, mEntitySystem()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
, mPlayerAircraft(nullptr)
{
    loadTextures();
    loadFonts();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}

void World::draw()
{
    mWindow.setView(mWorldView);

    for(auto entity : mEntitySystem.getEntities()) {
        mWindow.draw(*entity);
    }
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
    mTextures.load(Textures::Bullet, "Media/Textures/Bullet.png");
}

void World::loadFonts()
{
    mFonts.load(Fonts::Main, "Media/Sansation.ttf");
}

void World::buildScene()
{
    const auto startPosition = sf::Vector2f (mWorldBounds.width, mWorldBounds.top);

    mProjectileController = std::make_shared<ProjectileController>(mEntitySystem, mTextures, mWorldBounds);
    ProjectileController& projectileControllerRef(*mProjectileController.get());

    mEnemyAircraftController = std::make_shared<EnemyAircraftController>(mEntitySystem, projectileControllerRef, mTextures, AircraftEntity::Type::Raptor, startPosition, mWorldBounds);
    mProjectileCollisionController = std::make_unique<ProjectileCollisionController>(mProjectileController, mEnemyAircraftController);

    // Prepare tiled background
    sf::Texture& texture = mTextures.get(Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    auto backgroundSprite(std::make_unique<SpriteEntity>(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mEntitySystem.addObject(std::move(backgroundSprite));

    auto leader(std::make_unique<AircraftEntity>(projectileControllerRef, AircraftEntity::Eagle, mTextures));

    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
    mEntitySystem.addObject(std::move(leader));

    auto label(std::make_unique<GUI::Label>("hello world", mFonts));
    const auto labelPtr = label.get();
    labelPtr->setPosition(mSpawnPosition);
    mEntitySystem.addObject(std::move(label));
}

void World::update(sf::Time delta)
{
    mWorldView.move(0.f, mScrollSpeed * delta.asSeconds());
    mPlayerAircraft->setVelocity(0.f, 0.f);

    while (!mCommandQueue.isEmpty())
    {
        mEntitySystem.onCommand(mCommandQueue.pop(), delta);
    }

    adaptPlayerVelocity();
    mProjectileController->tick(delta, mScrollSpeed);
    mEnemyAircraftController->tick(delta, mScrollSpeed);
    mProjectileCollisionController->tick(delta);

    for (const auto& aircraft : mEnemyAircraftController->getAircrafts()) {
        aircraft->update(delta);
    }

    mPlayerAircraft->update(delta);

    adaptPlayerPosition();
}

void World::lateUpdate(const sf::Time delta) {
    mEntitySystem.lateUpdate(delta);
}

void World::adaptPlayerPosition() const
{
    const sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    constexpr float borderDistance = 40.f;

    sf::Vector2f position = mPlayerAircraft->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity() const
{
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

    mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}