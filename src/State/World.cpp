#include "World.h"

#include <PlayerData.h>

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

    const FontHolder& fonts;
    const PlayerData playerData;

    sf::FloatRect worldBounds;
    sf::Vector2f spawnPosition;
    TextureHolder textures;

    Impl(sf::RenderWindow& window, const FontHolder& font, const std::function<void()>& endGameCallback)
    : window(window)
    , worldView(window.getDefaultView())
    , endGameCallback(endGameCallback)
    , fonts(font)
    , worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y)
    , spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f)
    , textures(loadTextures())
    // Initalise the controllers and systems
    , mPlayerAircraftController (mPlayerAircraftEntitySystem, textures, playerData, spawnPosition)
    , mGuiController (
        fonts,
        mLabelEntitySystem,
        *mPlayerAircraftController.getPlayerAircaft(),
        playerData,
        worldBounds.width
    )
    , mBackgroundController (mBackgroundEntitySystem, textures, window.getSize(), ScrollSpeed)
    , mCloudsController (mCloudEntitySystem, textures, ScrollSpeed)
    , mEnemyAircraftController (mEnemyAircraftEntitySystem)
    , mExplosionController (mExplosionEntitySystem,textures)
    , mProjectileController(mProjectileEntitySystem, textures, worldBounds)
    , mPlayerAircraftMovementSystem(
        *mPlayerAircraftController.getPlayerAircaft(),
           worldView.getCenter(),
           worldView.getSize(),
           ScrollSpeed
        )
    , mEnemyAircraftMovementSystem (mEnemyAircraftEntitySystem, *mPlayerAircraftController.getPlayerAircaft(), ScrollSpeed)
    , mProjectileMovementSystem(mProjectileEntitySystem)
    , mProjectileCollisionSystem (
        mProjectileEntitySystem,
        mEnemyAircraftEntitySystem,
        *mPlayerAircraftController.getPlayerAircaft(),
        mExplosionController,
        mGuiController
    )
    , mSpawnEnemyAircraftSystem (mEnemyAircraftEntitySystem, textures, worldBounds.width)
    , mEnemyProjectileSpawnSystem (mEnemyAircraftEntitySystem, mProjectileController)
    , mPlayerProjectileSpawnSystem (mPlayerAircraftEntitySystem,mProjectileController)
    , mRemoveOffScreenEnemiesSystem (mEnemyAircraftEntitySystem, worldBounds.height)
    , mRemoveOffScreenProjectilesSystem (mProjectileEntitySystem, worldBounds.height)
    , mExplosionAnimationSystem (mExplosionEntitySystem)
    , mCloudMovementSystem (mCloudEntitySystem)
    , mBackgroundMovementSystem (mBackgroundEntitySystem)
    , mPlayerKilledSystem (*mPlayerAircraftController.getPlayerAircaft(), endGameCallback)
    , simpleControls (*mPlayerAircraftController.getPlayerAircaft())
    {
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

    static TextureHolder loadTextures()
    {
        TextureHolder textures;
        textures.load(Textures::Eagle, MediaFiles::Eagle);
        textures.load(Textures::Raptor, MediaFiles::Raptor);
        textures.load(Textures::Background, MediaFiles::Background);
        textures.load(Textures::Bullet, MediaFiles::Bullet);
        textures.load(Textures::EnemyBullet, MediaFiles::EnemyBullet);
        textures.load(Textures::Clouds, MediaFiles::Clouds);
        textures.load(Textures::Explosion, MediaFiles::Explosion);
        textures.load(Textures::PlayerExplosion, MediaFiles::PlayerExplosion);
        return textures;
    }

    void update(const sf::Time delta)
    {
        mProjectileCollisionSystem.execute();
        mSpawnEnemyAircraftSystem.execute(delta);
        mEnemyProjectileSpawnSystem.execute(delta);
        mProjectileMovementSystem.execute(delta);
        mPlayerProjectileSpawnSystem.execute(delta);
        mRemoveOffScreenEnemiesSystem.execute();
        mRemoveOffScreenProjectilesSystem.execute();
        mExplosionAnimationSystem.execute(delta);
        mCloudMovementSystem.execute(delta);
        mBackgroundMovementSystem.execute(delta);
        mPlayerAircraftMovementSystem.execute();
        mEnemyAircraftMovementSystem.execute(delta);

        simpleControls.handleRealtimeInput();

        mPlayerAircraftEntitySystem.update(delta);
        mProjectileEntitySystem.update(delta);
        mEnemyAircraftEntitySystem.update(delta);
        mLabelEntitySystem.update(delta);
        mExplosionEntitySystem.update(delta);

        // this needs to run last as it will tear this world object down
        mPlayerKilledSystem.execute();
    }

    EntitySystem<ProjectileEntity> mProjectileEntitySystem;
    EntitySystem<AircraftEntity> mPlayerAircraftEntitySystem;
    EntitySystem<AircraftEntity> mEnemyAircraftEntitySystem;
    EntitySystem<BackgroundEntity> mBackgroundEntitySystem;
    EntitySystem<CloudEntity> mCloudEntitySystem;
    EntitySystem<ExplosionEntity> mExplosionEntitySystem;
    EntitySystem<Label> mLabelEntitySystem;

    PlayerAircraftController mPlayerAircraftController;
    GuiController mGuiController;
    BackgroundController mBackgroundController;
    CloudsController mCloudsController;
    EnemyAircraftController mEnemyAircraftController;
    ExplosionController mExplosionController;
    ProjectileController mProjectileController;

    PlayerAircraftMovementSystem mPlayerAircraftMovementSystem;
    EnemyAircraftMovementSystem mEnemyAircraftMovementSystem;
    ProjectileMovementSystem mProjectileMovementSystem;
    ProjectileCollisionSystem mProjectileCollisionSystem;
    SpawnEnemyAircraftSystem mSpawnEnemyAircraftSystem;
    ProjectileSpawnSystem mEnemyProjectileSpawnSystem;
    ProjectileSpawnSystem mPlayerProjectileSpawnSystem;
    RemoveOffScreenEnemiesSystem mRemoveOffScreenEnemiesSystem;
    RemoveOffScreenProjectilesSystem mRemoveOffScreenProjectilesSystem;
    ExplosionAnimationSystem mExplosionAnimationSystem;
    CloudMovementSystem mCloudMovementSystem;
    BackgroundMovementSystem mBackgroundMovementSystem;
    PlayerKilledSystem mPlayerKilledSystem;
    SoundEffects mSoundEffects;

    PlayerControls simpleControls;
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