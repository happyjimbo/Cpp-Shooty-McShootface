#include "World.h"
#include "PlayerData.h"
#include "Label.h"
#include "EnemyAircraftInitializer.h"
#include "ProjectileInitializer.h"
#include "StarInitializer.h"
#include "PlayerAircraftInitializer.h"
#include "BackgroundInitializer.h"
#include "GuiInitializer.h"
#include "CloudsInitializer.h"
#include "ExplosionInitializer.h"
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
#include "StarEntity.h"
#include "StarMovementSystem.h"

#include <tracy/Tracy.hpp>

namespace
{
    constexpr float ScrollSpeed {-50.f};
}

struct World::Impl
{
    sf::RenderTexture& gameRenderTexture;
    sf::View worldView;

    const std::function<void()>& endGameCallback;

    const FontHolder& fonts;
    const PlayerData playerData;

    sf::FloatRect worldBounds;
    sf::Vector2f spawnPosition;
    TextureHolder textures;
    SoundEffects soundEffects;
    ShaderHolder shaders;

    Impl(sf::RenderTexture& gameRenderTexture, const FontHolder& font, const Settings& settings, const std::function<void()>& endGameCallback)
    : gameRenderTexture(gameRenderTexture)
    , worldView(gameRenderTexture.getDefaultView())
    , endGameCallback(endGameCallback)
    , fonts(font)
    , worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y)
    , spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f)
    , textures(loadTextures())
    , soundEffects(settings)
    , shaders(loadShaders())
    // Create the Initializers and systems
    , playerAircraftInitializer (playerAircraftEntitySystem, textures, shaders, playerData, spawnPosition)
    , guiInitializer (
        fonts,
        labelEntitySystem,
        playerAircraftInitializer.getPlayerAircaft(),
        playerData,
        worldBounds.width
    )
    , backgroundInitializer (backgroundEntitySystem, textures, gameRenderTexture.getSize(), ScrollSpeed)
    , cloudsInitializer (cloudEntitySystem, textures, shaders, ScrollSpeed)
    , enemyAircraftInitializer (enemyAircraftEntitySystem)
    , explosionInitializer (explosionEntitySystem, textures, soundEffects)
    , projectileInitializer (projectileEntitySystem, textures, worldBounds, soundEffects)
    , starInitializer(starEntitySystem, textures)
    , playerAircraftMovementSystem(
        playerAircraftInitializer.getPlayerAircaft(),
           worldView.getCenter(),
           worldView.getSize(),
           ScrollSpeed
        )
    , enemyAircraftMovementSystem (enemyAircraftEntitySystem, playerAircraftInitializer.getPlayerAircaft(), ScrollSpeed)
    , projectileMovementSystem (projectileEntitySystem)
    , projectileCollisionSystem (
        projectileEntitySystem,
        enemyAircraftEntitySystem,
        playerAircraftInitializer.getPlayerAircaft(),
        explosionInitializer,
        guiInitializer
    )
    , spawnEnemyAircraftSystem (enemyAircraftEntitySystem, textures, shaders, worldBounds.width)
    , enemyProjectileSpawnSystem (enemyAircraftEntitySystem, projectileInitializer)
    , playerProjectileSpawnSystem (playerAircraftEntitySystem,projectileInitializer)
    , removeOffScreenEnemiesSystem (enemyAircraftEntitySystem, worldBounds.height)
    , removeOffScreenProjectilesSystem (projectileEntitySystem, worldBounds.height)
    , explosionAnimationSystem (explosionEntitySystem)
    , cloudMovementSystem (cloudEntitySystem)
    , backgroundMovementSystem (backgroundEntitySystem)
    , playerKilledSystem (playerAircraftInitializer.getPlayerAircaft(), endGameCallback)
    , starMovementSystem(starInitializer.getStarEntity(), playerAircraftInitializer.getPlayerAircaft())
    , simpleControls (playerAircraftInitializer.getPlayerAircaft())
    {
        worldView.setCenter(spawnPosition);
    }

    void draw()
    {
        gameRenderTexture.setView(worldView);

        drawEntities(backgroundEntitySystem);
        drawEntities(cloudEntitySystem);
        drawEntities(explosionEntitySystem);
        drawEntities(projectileEntitySystem);
        drawEntities(enemyAircraftEntitySystem);
        drawEntities(playerAircraftEntitySystem);
        drawEntities(labelEntitySystem);
        drawEntities(starEntitySystem);
    }

    template <typename T>
    void drawEntities(EntitySystem<T>& system, sf::Shader* shader = nullptr)
    {
        for (const auto* entity : system.getEntities())
        {
            if (shader)
            {
                gameRenderTexture.draw(*entity, shader);
            }
            else
            {
                gameRenderTexture.draw(*entity);
            }
        }
    }

    static TextureHolder loadTextures()
    {
        TextureHolder textures;

        textures.load(Textures::NoiseTexture, MediaFiles::NoiseTexture);

        textures.load(Textures::Eagle, MediaFiles::Eagle);
        textures.load(Textures::Raptor, MediaFiles::Raptor);
        textures.load(Textures::Background, MediaFiles::Background);
        textures.load(Textures::Bullet, MediaFiles::Bullet);
        textures.load(Textures::EnemyBullet, MediaFiles::EnemyBullet);
        textures.load(Textures::Clouds, MediaFiles::Clouds);
        textures.load(Textures::Explosion, MediaFiles::Explosion);
        textures.load(Textures::PlayerExplosion, MediaFiles::PlayerExplosion);
        textures.load(Textures::Star, MediaFiles::Star);

        return textures;
    }

    static ShaderHolder loadShaders()
    {
        ShaderHolder shaders;

        shaders.loadShader(Shaders::Clouds, ShaderFiles::Clouds, sf::Shader::Fragment);
        shaders.loadShader(Shaders::Flash, ShaderFiles::Flash, sf::Shader::Fragment);
        return shaders;
    }

    void update(const sf::Time delta)
    {
        // FrameMark;
        ZoneScoped;

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
        starMovementSystem.execute();

        simpleControls.handleRealtimeInput();

        playerAircraftEntitySystem.update(delta);
        projectileEntitySystem.update(delta);
        enemyAircraftEntitySystem.update(delta);
        labelEntitySystem.update(delta);
        explosionEntitySystem.update(delta);
        cloudEntitySystem.update(delta);
        starEntitySystem.update(delta);

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
    EntitySystem<StarEntity> starEntitySystem;

    PlayerAircraftInitializer playerAircraftInitializer;
    GuiInitializer guiInitializer;
    BackgroundInitializer backgroundInitializer;
    CloudsInitializer cloudsInitializer;
    EnemyAircraftInitializer enemyAircraftInitializer;
    ExplosionInitializer explosionInitializer;
    ProjectileInitializer projectileInitializer;
    StarInitializer starInitializer;

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
    StarMovementSystem starMovementSystem;

    PlayerControls simpleControls;
};

World::World(sf::RenderTexture& gameRenderTexture, const FontHolder& font, const Settings& settings, const std::function<void()>& endGameCallback)
: mImpl(std::make_unique<Impl>(gameRenderTexture, font, settings, endGameCallback))
{
    // Last time I ran this it was 1824 bytes
    //std::cout << "Size of World::Impl: " << sizeof(Impl) << " bytes\n";
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