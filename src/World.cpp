#include "World.h"
#include "Label.h"
#include "EnemyAircraftController.h"
#include "ProjectileController.h"
#include "PlayerAircraftController.h"
#include "BackgroundController.h"
#include "ScoreController.h"
#include "CloudsController.h"
#include "SpawnEnemyAircraftSystem.h"
#include "ProjectileSpawnSystem.h"
#include "ProjectileCollisionSystem.h"
#include "RemoveOffScreenEnemiesSystem.h"
#include "RemoveOffScreenProjectilesSystem.h"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
{
    loadTextures();
    loadFonts();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}

void World::draw()
{
    mWindow.setView(mWorldView);

    drawEntities(mSpriteEntitySystem);
    drawEntities(mProjectileEntitySystem);
    drawEntities(mEnemyAircraftEntitySystem);
    drawEntities(mPlayerAircraftEntitySystem);
    drawEntities(mLabelEntitySystem);
}

template <typename T>
void World::drawEntities(EntitySystem<T>& system)
{
    for (const auto* entity : system.getEntities())
    {
        mWindow.draw(*entity);
    }
}

void World::loadTextures()
{
    // move these string values into a struct or similar
    mTextures.load(Textures::Eagle, MediaFiles::Eagle);
    mTextures.load(Textures::Raptor, MediaFiles::Raptor);
    mTextures.load(Textures::Background, MediaFiles::Background);
    mTextures.load(Textures::Bullet, MediaFiles::Bullet);
    mTextures.load(Textures::EnemyBullet, MediaFiles::EnemyBullet);
    mTextures.load(Textures::Clouds, MediaFiles::Clouds);
}

void World::loadFonts()
{
    mFonts.load(Fonts::Main, MediaFiles::Font);
}

void World::buildScene()
{
    // this is for the mEnemyAircraftController and should be internalised in that logic
    const auto startPosition = sf::Vector2f (mWorldBounds.width, (mSpawnPosition.y - mWorldView.getSize().y / 2)-100);

    mScoreController = new ScoreController(
        mLabelEntitySystem
    );
    mScoreController->create(mFonts);

    mProjectileController = new ProjectileController(
        mProjectileEntitySystem,
        mTextures,
        mWorldBounds
    );

    mProjectileCollisionSystem = new ProjectileCollisionSystem(
        mProjectileEntitySystem,
        mEnemyAircraftEntitySystem,
        mPlayerAircraftEntitySystem,
        *mScoreController
    );

    mSpawnEnemyAircraftSystem = new SpawnEnemyAircraftSystem(
        mEnemyAircraftEntitySystem,
        mTextures,
        startPosition
    );

    mEnemyProjectileSpawnSystem = new ProjectileSpawnSystem(
        mEnemyAircraftEntitySystem,
        *mProjectileController
    );

    mPlayerProjectileSpawnSystem = new ProjectileSpawnSystem(
        mPlayerAircraftEntitySystem,
        *mProjectileController
    );

    mRemoveOffScreenEnemiesSystem = new RemoveOffScreenEnemiesSystem(
        mEnemyAircraftEntitySystem,
        mWorldBounds.height
    );

    mRemoveOffScreenProjectilesSystem = new RemoveOffScreenProjectilesSystem(
        mProjectileEntitySystem,
        mWorldBounds.height
    );

    mEnemyAircraftController = new EnemyAircraftController(
        mEnemyAircraftEntitySystem,
        mScrollSpeed
    );

    mPlayerAircraftController = new PlayerAircraftController(
       mPlayerAircraftEntitySystem,
       mWorldView.getCenter(),
       mWorldView.getSize(),
       mScrollSpeed
   );
    mPlayerAircraftController->create(mTextures, mSpawnPosition);

    mBackgroundController = new BackgroundController(
        mSpriteEntitySystem,
        mTextures,
        mWindow.getSize(),
        mScrollSpeed
    );
    mBackgroundController->create();

    mCloudsController = new CloudsController (
        mSpriteEntitySystem,
        mTextures,
        mScrollSpeed
    );
    mCloudsController->create();

    simpleControls.initializeActions(
        *mPlayerAircraftController->getPlayerAircaft()
    );
}

void World::update(const sf::Time delta)
{
    mProjectileController->tick(delta);
    mProjectileCollisionSystem->execute();
    mSpawnEnemyAircraftSystem->execute(delta);
    mEnemyProjectileSpawnSystem->execute(delta);
    mPlayerProjectileSpawnSystem->execute(delta);
    mRemoveOffScreenEnemiesSystem->execute();
    mRemoveOffScreenProjectilesSystem->execute();
    mEnemyAircraftController->tick(delta);
    mPlayerAircraftController->tick();
    mBackgroundController->tick(delta);
    mCloudsController->tick(delta);

    simpleControls.handleRealtimeInput();

    mPlayerAircraftEntitySystem.update(delta);
    mProjectileEntitySystem.update(delta);
    mEnemyAircraftEntitySystem.update(delta);
    mLabelEntitySystem.update(delta);
}

World::~World()
{
    delete mScoreController;
    delete mProjectileController;
    delete mEnemyAircraftController;
    delete mPlayerAircraftController;
    delete mBackgroundController;
    delete mCloudsController;

    delete mProjectileCollisionSystem;
    delete mSpawnEnemyAircraftSystem;
    delete mEnemyProjectileSpawnSystem;
    delete mPlayerProjectileSpawnSystem;
    delete mRemoveOffScreenEnemiesSystem;
    delete mRemoveOffScreenProjectilesSystem;
}