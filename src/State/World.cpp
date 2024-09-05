#include "World.h"
#include "Label.h"
#include "EnemyAircraftController.h"
#include "ProjectileController.h"
#include "PlayerAircraftController.h"
#include "BackgroundController.h"
#include "GuiController.h"
#include "CloudsController.h"
#include "ExplosionController.h"
#include "MediaFiles.h"
#include "SpawnEnemyAircraftSystem.h"
#include "ProjectileSpawnSystem.h"
#include "ProjectileCollisionSystem.h"
#include "RemoveOffScreenEnemiesSystem.h"
#include "RemoveOffScreenProjectilesSystem.h"
#include "ExplosionAnimationSystem.h"
#include "PlayerKilledSystem.h"
#include "CloudMovementSystem.h"
#include "BackgroundMovementSystem.h"
#include "EnemyAircraftMovementSystem.h"
#include "PlayerAircraftMovementSystem.h"


World::World(sf::RenderWindow& window, const FontHolder& font, const std::function<void()>& endGameCallback)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mEndGameCallback(endGameCallback)
, mFonts(font)
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
{
    loadTextures();
    initLogic();

    mWorldView.setCenter(mSpawnPosition);
}

void World::draw()
{
    mWindow.setView(mWorldView);

    drawEntities(mBackgroundEntitySystem);
    drawEntities(mCloudEntitySystem);
    drawEntities(mExplosionEntitySystem);
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
    mTextures.load(Textures::Eagle, MediaFiles::Eagle);
    mTextures.load(Textures::Raptor, MediaFiles::Raptor);
    mTextures.load(Textures::Background, MediaFiles::Background);
    mTextures.load(Textures::Bullet, MediaFiles::Bullet);
    mTextures.load(Textures::EnemyBullet, MediaFiles::EnemyBullet);
    mTextures.load(Textures::Clouds, MediaFiles::Clouds);
    mTextures.load(Textures::Explosion, MediaFiles::Explosion);
    mTextures.load(Textures::PlayerExplosion, MediaFiles::PlayerExplosion);
}

void World::initLogic()
{
    mExplosionController = new ExplosionController(
        mExplosionEntitySystem,
        mTextures
    );

    mProjectileController = new ProjectileController(
        mProjectileEntitySystem,
        mTextures,
        mWorldBounds
    );

    mPlayerAircraftController = new PlayerAircraftController(
       mPlayerAircraftEntitySystem
   );
    mPlayerAircraftController->create(mTextures, mSpawnPosition);

    mPlayerAircraftMovementSystem = new PlayerAircraftMovementSystem(
    *mPlayerAircraftController->getPlayerAircaft(),
       mWorldView.getCenter(),
       mWorldView.getSize(),
       mScrollSpeed
    );

    mEnemyAircraftMovementSystem = new EnemyAircraftMovementSystem(
        mEnemyAircraftEntitySystem,
        *mPlayerAircraftController->getPlayerAircaft(),
        mScrollSpeed
    );

    mScoreController = new GuiController(
        mLabelEntitySystem,
        *mPlayerAircraftController->getPlayerAircaft(),
        mWorldBounds.width
    );
    mScoreController->create(mFonts);

    mProjectileCollisionSystem = new ProjectileCollisionSystem(
        mProjectileEntitySystem,
        mEnemyAircraftEntitySystem,
        *mPlayerAircraftController->getPlayerAircaft(),
        *mExplosionController,
        *mScoreController
    );

    mSpawnEnemyAircraftSystem = new SpawnEnemyAircraftSystem(
        mEnemyAircraftEntitySystem,
        mTextures,
        mWorldBounds.width
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

    mExplosionAnimationSystem = new ExplosionAnimationSystem(
        mExplosionEntitySystem
    );

    mEnemyAircraftController = new EnemyAircraftController(
        mEnemyAircraftEntitySystem
    );

    mBackgroundController = new BackgroundController(
        mBackgroundEntitySystem,
        mTextures,
        mWindow.getSize(),
        mScrollSpeed
    );
    mBackgroundController->create();

    mCloudsController = new CloudsController (
        mCloudEntitySystem,
        mTextures,
        mScrollSpeed
    );
    mCloudsController->create();

    mCloudMovementSystem = new CloudMovementSystem(
        mCloudEntitySystem
    );

    mBackgroundMovementSystem = new BackgroundMovementSystem(
        mBackgroundEntitySystem
    );

    simpleControls.initializeActions(
        *mPlayerAircraftController->getPlayerAircaft()
    );

    mPlayerKilledSystem = new PlayerKilledSystem (
        *mPlayerAircraftController->getPlayerAircaft(),
        mEndGameCallback
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
    mExplosionAnimationSystem->execute(delta);
    mCloudMovementSystem->execute(delta);
    mBackgroundMovementSystem->execute(delta);
    mPlayerAircraftMovementSystem->execute();
    mEnemyAircraftMovementSystem->execute(delta);

    simpleControls.handleRealtimeInput();

    mPlayerAircraftEntitySystem.update(delta);
    mProjectileEntitySystem.update(delta);
    mEnemyAircraftEntitySystem.update(delta);
    mLabelEntitySystem.update(delta);
    mExplosionEntitySystem.update(delta);

    // this needs to run last as it will tear this world object down
    mPlayerKilledSystem->execute();
}

World::~World()
{
    delete mScoreController;
    delete mExplosionController;
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
    delete mExplosionAnimationSystem;
    delete mPlayerKilledSystem;
    delete mCloudMovementSystem;
    delete mBackgroundMovementSystem;
    delete mPlayerAircraftMovementSystem;
    delete mEnemyAircraftMovementSystem;
}