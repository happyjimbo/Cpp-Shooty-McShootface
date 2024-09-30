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
    SoundEffects soundEffects;

    Impl(sf::RenderWindow& window, const FontHolder& font, const Settings& settings, const std::function<void()>& endGameCallback)
    : window(window)
    , worldView(window.getDefaultView())
    , endGameCallback(endGameCallback)
    , fonts(font)
    , worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y)
    , spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f)
    , textures(loadTextures())
    , soundEffects(settings)
    // Initalise the controllers and systems
    , playerAircraftController (playerAircraftEntitySystem, textures, playerData, spawnPosition)
    , guiController (
        fonts,
        labelEntitySystem,
        *playerAircraftController.getPlayerAircaft(),
        playerData,
        worldBounds.width
    )
    , backgroundController (backgroundEntitySystem, textures, window.getSize(), ScrollSpeed)
    , cloudsController (cloudEntitySystem, textures, ScrollSpeed)
    , enemyAircraftController (enemyAircraftEntitySystem)
    , explosionController (explosionEntitySystem, textures, soundEffects)
    , projectileController (projectileEntitySystem, textures, worldBounds, soundEffects)
    , playerAircraftMovementSystem(
        *playerAircraftController.getPlayerAircaft(),
           worldView.getCenter(),
           worldView.getSize(),
           ScrollSpeed
        )
    , enemyAircraftMovementSystem (enemyAircraftEntitySystem, *playerAircraftController.getPlayerAircaft(), ScrollSpeed)
    , projectileMovementSystem (projectileEntitySystem)
    , projectileCollisionSystem (
        projectileEntitySystem,
        enemyAircraftEntitySystem,
        *playerAircraftController.getPlayerAircaft(),
        explosionController,
        guiController
    )
    , spawnEnemyAircraftSystem (enemyAircraftEntitySystem, textures, worldBounds.width)
    , enemyProjectileSpawnSystem (enemyAircraftEntitySystem, projectileController)
    , playerProjectileSpawnSystem (playerAircraftEntitySystem,projectileController)
    , removeOffScreenEnemiesSystem (enemyAircraftEntitySystem, worldBounds.height)
    , removeOffScreenProjectilesSystem (projectileEntitySystem, worldBounds.height)
    , explosionAnimationSystem (explosionEntitySystem)
    , cloudMovementSystem (cloudEntitySystem)
    , backgroundMovementSystem (backgroundEntitySystem)
    , playerKilledSystem (*playerAircraftController.getPlayerAircaft(), endGameCallback)
    , simpleControls (*playerAircraftController.getPlayerAircaft())
    {
        worldView.setCenter(spawnPosition);
    }

    void draw()
    {
        window.setView(worldView);

        drawEntities(backgroundEntitySystem);
        drawEntities(cloudEntitySystem);
        drawEntities(explosionEntitySystem);
        drawEntities(projectileEntitySystem);
        drawEntities(enemyAircraftEntitySystem);
        drawEntities(playerAircraftEntitySystem);
        drawEntities(labelEntitySystem);
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
        projectileCollisionSystem.execute();
        spawnEnemyAircraftSystem.execute(delta);
        enemyProjectileSpawnSystem.execute(delta);
        projectileMovementSystem.execute(delta);
        playerProjectileSpawnSystem.execute(delta);
        removeOffScreenEnemiesSystem.execute();
        removeOffScreenProjectilesSystem.execute();
        explosionAnimationSystem.execute(delta);
        cloudMovementSystem.execute(delta);
        backgroundMovementSystem.execute(delta);
        playerAircraftMovementSystem.execute();
        enemyAircraftMovementSystem.execute(delta);

        simpleControls.handleRealtimeInput();

        playerAircraftEntitySystem.update(delta);
        projectileEntitySystem.update(delta);
        enemyAircraftEntitySystem.update(delta);
        labelEntitySystem.update(delta);
        explosionEntitySystem.update(delta);

        soundEffects.update();
    }

    // This needs to run after everything else, otherwise it can result to
    // world being destoryed whilst the update is still processing
    // and thus EXC_BAD_ACCESS
    void lateUpdate() const
    {
        // call playerKilledSystem.execute at the very end
        playerKilledSystem.execute();
    }

    EntitySystem<ProjectileEntity> projectileEntitySystem;
    EntitySystem<Aircraft::AircraftEntity> playerAircraftEntitySystem;
    EntitySystem<Aircraft::AircraftEntity> enemyAircraftEntitySystem;
    EntitySystem<BackgroundEntity> backgroundEntitySystem;
    EntitySystem<CloudEntity> cloudEntitySystem;
    EntitySystem<ExplosionEntity> explosionEntitySystem;
    EntitySystem<GUI::Label> labelEntitySystem;

    PlayerAircraftController playerAircraftController;
    GuiController guiController;
    BackgroundController backgroundController;
    CloudsController cloudsController;
    EnemyAircraftController enemyAircraftController;
    ExplosionController explosionController;
    ProjectileController projectileController;

    PlayerAircraftMovementSystem playerAircraftMovementSystem;
    EnemyAircraftMovementSystem enemyAircraftMovementSystem;
    ProjectileMovementSystem projectileMovementSystem;
    ProjectileCollisionSystem projectileCollisionSystem;
    SpawnEnemyAircraftSystem spawnEnemyAircraftSystem;
    ProjectileSpawnSystem enemyProjectileSpawnSystem;
    ProjectileSpawnSystem playerProjectileSpawnSystem;
    RemoveOffScreenEnemiesSystem removeOffScreenEnemiesSystem;
    RemoveOffScreenProjectilesSystem removeOffScreenProjectilesSystem;
    ExplosionAnimationSystem explosionAnimationSystem;
    CloudMovementSystem cloudMovementSystem;
    BackgroundMovementSystem backgroundMovementSystem;
    PlayerKilledSystem playerKilledSystem;

    PlayerControls simpleControls;
};

World::World(sf::RenderWindow& window, const FontHolder& font, const Settings& settings, const std::function<void()>& endGameCallback)
: mImpl(std::make_unique<Impl>(window, font, settings, endGameCallback))
{
}

void World::draw() const
{
    mImpl->draw();
}


void World::update(const sf::Time delta) const
{
    mImpl->update(delta);
    mImpl->lateUpdate();
}

World::~World() = default;