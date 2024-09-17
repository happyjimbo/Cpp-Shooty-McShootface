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
#include "PlayerControls.h"
#include "ProjectileMovementSystem.h"
#include "SoundEffects.h"

namespace
{
    constexpr float ScrollSpeed {-50.f};
}

struct World::Impl
{
    sf::RenderWindow& window;
    sf::View worldView;

    const std::function<void()>& endGameCallback;

    TextureHolder textures;
    const FontHolder& fonts;
    PlayerControls simpleControls;

    sf::FloatRect worldBounds;
    sf::Vector2f spawnPosition;

    Impl(sf::RenderWindow& window, const FontHolder& font, const std::function<void()>& endGameCallback)
    : window(window)
    , worldView(window.getDefaultView())
    , endGameCallback(endGameCallback)
    , fonts(font)
    , worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y)
    , spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f)
    {
        loadTextures();
        initLogic();

        worldView.setCenter(spawnPosition);
    }

    void draw()
    {
        window.setView(worldView);

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
            window.draw(*entity);
        }
    }

    void loadTextures()
    {
        textures.load(Textures::Eagle, MediaFiles::Eagle);
        textures.load(Textures::Raptor, MediaFiles::Raptor);
        textures.load(Textures::Background, MediaFiles::Background);
        textures.load(Textures::Bullet, MediaFiles::Bullet);
        textures.load(Textures::EnemyBullet, MediaFiles::EnemyBullet);
        textures.load(Textures::Clouds, MediaFiles::Clouds);
        textures.load(Textures::Explosion, MediaFiles::Explosion);
        textures.load(Textures::PlayerExplosion, MediaFiles::PlayerExplosion);
    }

    void initLogic()
    {
        mExplosionController = std::make_unique<ExplosionController>(
            mExplosionEntitySystem,
            textures
        );

        mProjectileController = std::make_unique<ProjectileController>(
            mProjectileEntitySystem,
            textures,
            worldBounds
        );

        mPlayerAircraftController = std::make_unique<PlayerAircraftController>(
           mPlayerAircraftEntitySystem
       );
        mPlayerAircraftController->create(textures, spawnPosition);

        mPlayerAircraftMovementSystem = std::make_unique<PlayerAircraftMovementSystem>(
        *mPlayerAircraftController->getPlayerAircaft(),
           worldView.getCenter(),
           worldView.getSize(),
           ScrollSpeed
        );

        mEnemyAircraftMovementSystem = std::make_unique<EnemyAircraftMovementSystem>(
            mEnemyAircraftEntitySystem,
            *mPlayerAircraftController->getPlayerAircaft(),
            ScrollSpeed
        );

        mProjectileMovementSystem = std::make_unique<ProjectileMovementSystem>(
            mProjectileEntitySystem
        );

        mScoreController = std::make_unique<GuiController>(
            mLabelEntitySystem,
            *mPlayerAircraftController->getPlayerAircaft(),
            worldBounds.width
        );
        mScoreController->create(fonts);

        mProjectileCollisionSystem = std::make_unique<ProjectileCollisionSystem>(
            mProjectileEntitySystem,
            mEnemyAircraftEntitySystem,
            *mPlayerAircraftController->getPlayerAircaft(),
            *mExplosionController,
            *mScoreController
        );

        mSpawnEnemyAircraftSystem = std::make_unique<SpawnEnemyAircraftSystem>(
            mEnemyAircraftEntitySystem,
            textures,
            worldBounds.width
        );

        mEnemyProjectileSpawnSystem = std::make_unique<ProjectileSpawnSystem>(
            mEnemyAircraftEntitySystem,
            *mProjectileController
        );

        mPlayerProjectileSpawnSystem = std::make_unique<ProjectileSpawnSystem>(
            mPlayerAircraftEntitySystem,
            *mProjectileController
        );

        mRemoveOffScreenEnemiesSystem = std::make_unique<RemoveOffScreenEnemiesSystem>(
            mEnemyAircraftEntitySystem,
            worldBounds.height
        );

        mRemoveOffScreenProjectilesSystem = std::make_unique<RemoveOffScreenProjectilesSystem>(
            mProjectileEntitySystem,
            worldBounds.height
        );

        mExplosionAnimationSystem = std::make_unique<ExplosionAnimationSystem>(
            mExplosionEntitySystem
        );

        mEnemyAircraftController = std::make_unique<EnemyAircraftController>(
            mEnemyAircraftEntitySystem
        );

        mBackgroundController = std::make_unique<BackgroundController>(
            mBackgroundEntitySystem,
            textures,
            window.getSize(),
            ScrollSpeed
        );
        mBackgroundController->create();

        mCloudsController = std::make_unique<CloudsController> (
            mCloudEntitySystem,
            textures,
            ScrollSpeed
        );
        mCloudsController->create();

        mCloudMovementSystem = std::make_unique<CloudMovementSystem> (
            mCloudEntitySystem
        );

        mBackgroundMovementSystem = std::make_unique<BackgroundMovementSystem> (
            mBackgroundEntitySystem
        );

        simpleControls.initializeActions(
            *mPlayerAircraftController->getPlayerAircaft()
        );

        mPlayerKilledSystem = std::make_unique<PlayerKilledSystem> (
            *mPlayerAircraftController->getPlayerAircaft(),
            endGameCallback
        );

        mSoundEffects = std::make_unique<SoundEffects>();
    }

    void update(const sf::Time delta)
    {
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
        mProjectileMovementSystem->execute(delta);

        simpleControls.handleRealtimeInput();

        mPlayerAircraftEntitySystem.update(delta);
        mProjectileEntitySystem.update(delta);
        mEnemyAircraftEntitySystem.update(delta);
        mLabelEntitySystem.update(delta);
        mExplosionEntitySystem.update(delta);

        // this needs to run last as it will tear this world object down
        mPlayerKilledSystem->execute();
    }

    EntitySystem<ProjectileEntity> mProjectileEntitySystem;
    EntitySystem<AircraftEntity> mPlayerAircraftEntitySystem;
    EntitySystem<AircraftEntity> mEnemyAircraftEntitySystem;
    EntitySystem<BackgroundEntity> mBackgroundEntitySystem;
    EntitySystem<CloudEntity> mCloudEntitySystem;
    EntitySystem<ExplosionEntity> mExplosionEntitySystem;
    EntitySystem<Label> mLabelEntitySystem;

    std::unique_ptr<GuiController> mScoreController;
    std::unique_ptr<ProjectileController> mProjectileController;
    std::unique_ptr<EnemyAircraftController> mEnemyAircraftController;
    std::unique_ptr<PlayerAircraftController> mPlayerAircraftController;
    std::unique_ptr<BackgroundController> mBackgroundController;
    std::unique_ptr<CloudsController> mCloudsController;
    std::unique_ptr<ExplosionController> mExplosionController;

    std::unique_ptr<SpawnEnemyAircraftSystem> mSpawnEnemyAircraftSystem;
    std::unique_ptr<ProjectileSpawnSystem> mEnemyProjectileSpawnSystem;
    std::unique_ptr<ProjectileSpawnSystem> mPlayerProjectileSpawnSystem;
    std::unique_ptr<ProjectileCollisionSystem> mProjectileCollisionSystem;
    std::unique_ptr<RemoveOffScreenEnemiesSystem> mRemoveOffScreenEnemiesSystem;
    std::unique_ptr<RemoveOffScreenProjectilesSystem> mRemoveOffScreenProjectilesSystem;
    std::unique_ptr<ExplosionAnimationSystem> mExplosionAnimationSystem;
    std::unique_ptr<PlayerKilledSystem> mPlayerKilledSystem;
    std::unique_ptr<CloudMovementSystem> mCloudMovementSystem;
    std::unique_ptr<BackgroundMovementSystem> mBackgroundMovementSystem;
    std::unique_ptr<PlayerAircraftMovementSystem> mPlayerAircraftMovementSystem;
    std::unique_ptr<EnemyAircraftMovementSystem> mEnemyAircraftMovementSystem;
    std::unique_ptr<ProjectileMovementSystem> mProjectileMovementSystem;
    std::unique_ptr<SoundEffects> mSoundEffects;
};

World::World(sf::RenderWindow& window, const FontHolder& font, const std::function<void()>& endGameCallback)
: mImpl(std::make_unique<Impl>(window, font, endGameCallback))
{
}

void World::draw() const
{
    mImpl->draw();
}


void World::update(const sf::Time delta) const
{
    mImpl->update(delta);
}

World::~World() = default;