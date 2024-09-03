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

    drawEntities(mSpriteEntitySystem);
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
       mPlayerAircraftEntitySystem,
       mWorldView.getCenter(),
       mWorldView.getSize(),
       mScrollSpeed
   );
    mPlayerAircraftController->create(mTextures, mSpawnPosition);

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
        mEnemyAircraftEntitySystem,
        *mPlayerAircraftController->getPlayerAircaft(),
        mScrollSpeed
    );

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

    mEnemyAircraftController->tick(delta);
    mPlayerAircraftController->tick();
    mBackgroundController->tick(delta);
    mCloudsController->tick(delta);

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
}