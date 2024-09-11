#include "World.h"
#include "Label.h"
#include "EnemyAircraftController.h"
#include "ProjectileController.h"
#include "PlayerAircraftController.h"
#include "BackgroundController.h"
#include "GuiController.h"
#include "CloudsController.h"
#include "ExplosionController.h"
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
#include "PlayerControls.h"
#include "ProjectileMovementSystem.h"
#include "SoundEffects.h"

namespace
{
    constexpr float mScrollSpeed {-50.f};

    // not used yet?
    // enum Layer
    // {
        // Background,
        // Air,
        // Bulelts,
        // GUI,
        // LayerCount
    // };

}

class WorldImpl final
{

    sf::RenderWindow& mWindow;
    sf::View mWorldView;

    const std::function<void()>& mEndGameCallback;

    const FontHolder& mFonts;
    PlayerControls simpleControls;

    EntitySystem<ProjectileEntity> mProjectileEntitySystem;
    EntitySystem<AircraftEntity> mPlayerAircraftEntitySystem;
    EntitySystem<AircraftEntity> mEnemyAircraftEntitySystem;
    EntitySystem<BackgroundEntity> mBackgroundEntitySystem;
    EntitySystem<CloudEntity> mCloudEntitySystem;
    EntitySystem<ExplosionEntity> mExplosionEntitySystem;
    EntitySystem<Label> mLabelEntitySystem;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;

    ExplosionController mExplosionController;
    ProjectileController mProjectileController;
    PlayerAircraftController mPlayerAircraftController;
    PlayerAircraftMovementSystem mPlayerAircraftMovementSystem;
    EnemyAircraftMovementSystem mEnemyAircraftMovementSystem;
    ProjectileMovementSystem mProjectileMovementSystem;
    GuiController mScoreController;
    ProjectileCollisionSystem mProjectileCollisionSystem;
    SpawnEnemyAircraftSystem mSpawnEnemyAircraftSystem;
    ProjectileSpawnSystem mEnemyProjectileSpawnSystem;
    ProjectileSpawnSystem mPlayerProjectileSpawnSystem;
    RemoveOffScreenEnemiesSystem mRemoveOffScreenEnemiesSystem;
    RemoveOffScreenProjectilesSystem mRemoveOffScreenProjectilesSystem;
    ExplosionAnimationSystem mExplosionAnimationSystem;
    EnemyAircraftController mEnemyAircraftController;
    BackgroundController mBackgroundController;
    CloudsController mCloudsController;
    CloudMovementSystem mCloudMovementSystem;
    BackgroundMovementSystem mBackgroundMovementSystem;
    PlayerKilledSystem mPlayerKilledSystem;
    SoundEffects mSoundEffects;

public:
    explicit WorldImpl(sf::RenderWindow& window,
        TextureHolder& textures,
        const FontHolder& font,
        const std::function<void()>& endGameCallback)
        : mWindow(window)
          , mWorldView(window.getDefaultView())
          , mEndGameCallback(endGameCallback)
          , mFonts(font)
          , mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
          , mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
          // ----
          , mExplosionController(mExplosionEntitySystem, textures)
          , mProjectileController(mProjectileEntitySystem, textures, mWorldBounds)
          , mPlayerAircraftController(mPlayerAircraftEntitySystem, textures, mSpawnPosition)
          , mPlayerAircraftMovementSystem(
              *mPlayerAircraftController.getPlayerAircaft(),
              mWorldView.getCenter(),
              mWorldView.getSize(),
              mScrollSpeed)
          , mEnemyAircraftMovementSystem(
              mEnemyAircraftEntitySystem,
              *mPlayerAircraftController.getPlayerAircaft(),
              mScrollSpeed)
          , mProjectileMovementSystem(mProjectileEntitySystem)
          , mScoreController(
              mLabelEntitySystem,
              *mPlayerAircraftController.getPlayerAircaft(),
              mWorldBounds.width)
          , mProjectileCollisionSystem(
              mProjectileEntitySystem,
              mEnemyAircraftEntitySystem,
              *mPlayerAircraftController.getPlayerAircaft(),
              mExplosionController,
              mScoreController)
          , mSpawnEnemyAircraftSystem(mEnemyAircraftEntitySystem, textures, mWorldBounds.width)
          , mEnemyProjectileSpawnSystem(mEnemyAircraftEntitySystem, mProjectileController)
          , mPlayerProjectileSpawnSystem(mPlayerAircraftEntitySystem, mProjectileController)
          , mRemoveOffScreenEnemiesSystem(mEnemyAircraftEntitySystem, mWorldBounds.height)
          , mRemoveOffScreenProjectilesSystem(mProjectileEntitySystem, mWorldBounds.height)
          , mExplosionAnimationSystem(mExplosionEntitySystem)
          , mEnemyAircraftController(mEnemyAircraftEntitySystem)
          , mBackgroundController(mBackgroundEntitySystem, textures, mWindow.getSize(), mScrollSpeed)
          , mCloudsController(mCloudEntitySystem, textures, mScrollSpeed)
          , mCloudMovementSystem(mCloudEntitySystem)
          , mBackgroundMovementSystem(mBackgroundEntitySystem)
          , mPlayerKilledSystem(
              *mPlayerAircraftController.getPlayerAircaft(),
              mEndGameCallback)
    {
        // loadTextures();

        mScoreController.create(mFonts);
        mBackgroundController.create();
        mCloudsController.create();
        simpleControls.initializeActions(
            *mPlayerAircraftController.getPlayerAircaft()
        );

        mWorldView.setCenter(mSpawnPosition);
    }

    void draw()
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
    void drawEntities(EntitySystem<T>& system)
    {
        for (const auto* entity : system.getEntities())
        {
            mWindow.draw(*entity);
        }
    }

    // void loadTextures()
    // {
        // textures.load(Textures::Eagle, MediaFiles::Eagle);
        // textures.load(Textures::Raptor, MediaFiles::Raptor);
        // textures.load(Textures::Background, MediaFiles::Background);
        // textures.load(Textures::Bullet, MediaFiles::Bullet);
        // textures.load(Textures::EnemyBullet, MediaFiles::EnemyBullet);
        // textures.load(Textures::Clouds, MediaFiles::Clouds);
        // textures.load(Textures::Explosion, MediaFiles::Explosion);
        // textures.load(Textures::PlayerExplosion, MediaFiles::PlayerExplosion);
    // }

void update(const sf::Time delta)
{
    mProjectileCollisionSystem.execute();
    mSpawnEnemyAircraftSystem.execute(delta);
    mEnemyProjectileSpawnSystem.execute(delta);
    mPlayerProjectileSpawnSystem.execute(delta);
    mRemoveOffScreenEnemiesSystem.execute();
    mRemoveOffScreenProjectilesSystem.execute();
    mExplosionAnimationSystem.execute(delta);
    mCloudMovementSystem.execute(delta);
    mBackgroundMovementSystem.execute(delta);
    mPlayerAircraftMovementSystem.execute();
    mEnemyAircraftMovementSystem.execute(delta);
    mProjectileMovementSystem.execute(delta);

    simpleControls.handleRealtimeInput();

    mPlayerAircraftEntitySystem.update(delta);
    mProjectileEntitySystem.update(delta);
    mEnemyAircraftEntitySystem.update(delta);
    mLabelEntitySystem.update(delta);
    mExplosionEntitySystem.update(delta);

    // this needs to run last as it will tear this world object down
    mPlayerKilledSystem.execute();
}

};

World::World(sf::RenderWindow& window,
    TextureHolder& textures,
    const FontHolder& font,
    const std::function<void()>& endGameCallback)
    : impl_(std::make_unique<WorldImpl>(window, textures, font, endGameCallback)) // forward?
{

}

void World::draw()
{
    impl_->draw();
}

void World::update(const sf::Time delta)
{
    impl_->update(delta);
}

World::~World() = default;

