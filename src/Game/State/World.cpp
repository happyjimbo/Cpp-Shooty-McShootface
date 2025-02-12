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
#include "StarMovementSystem.h"

#include <tracy/Tracy.hpp>

#include "EntitySystems.h"

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

    EntitySystems entitySystems;

    Impl(sf::RenderTexture& gameRenderTexture, const FontHolder& font, const SoundSettings& soundSettings, const std::function<void()>& endGameCallback)
    : gameRenderTexture(gameRenderTexture)
    , worldView(gameRenderTexture.getDefaultView())
    , endGameCallback(endGameCallback)
    , fonts(font)
    , worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y)
    , spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f)
    , textures(loadTextures())
    , soundEffects(soundSettings)
    , shaders(loadShaders())
    // Create the Initializers and systems
    , playerAircraftInitializer (entitySystems.playerAircraftEntitySystem, textures, shaders, playerData, spawnPosition)
    , guiInitializer (
        fonts,
        entitySystems.labelEntitySystem,
        playerAircraftInitializer.getPlayerAircaft(),
        playerData,
        worldBounds.width
    )
    , backgroundInitializer (entitySystems.backgroundEntitySystem, textures, gameRenderTexture.getSize(), ScrollSpeed)
    , cloudsInitializer (entitySystems.cloudEntitySystem, textures, shaders, ScrollSpeed)
    , enemyAircraftInitializer (entitySystems.enemyAircraftEntitySystem)
    , explosionInitializer (entitySystems.explosionEntitySystem, textures, soundEffects)
    , projectileInitializer (entitySystems.projectileEntitySystem, textures, worldBounds, soundEffects)
    , starInitializer(entitySystems.starEntitySystem, textures)
    , playerAircraftMovementSystem(
        playerAircraftInitializer.getPlayerAircaft(),
           worldView.getCenter(),
           worldView.getSize(),
           ScrollSpeed
        )
    , enemyAircraftMovementSystem (entitySystems.enemyAircraftEntitySystem, playerAircraftInitializer.getPlayerAircaft(), ScrollSpeed)
    , projectileMovementSystem (entitySystems.projectileEntitySystem)
    , projectileCollisionSystem (
        entitySystems.projectileEntitySystem,
        entitySystems.enemyAircraftEntitySystem,
        playerAircraftInitializer.getPlayerAircaft(),
        explosionInitializer,
        guiInitializer
    )
    , spawnEnemyAircraftSystem (entitySystems.enemyAircraftEntitySystem, textures, shaders, worldBounds.width)
    , enemyProjectileSpawnSystem (entitySystems.enemyAircraftEntitySystem, projectileInitializer)
    , playerProjectileSpawnSystem (entitySystems.playerAircraftEntitySystem,projectileInitializer)
    , removeOffScreenEnemiesSystem (entitySystems.enemyAircraftEntitySystem, worldBounds.height)
    , removeOffScreenProjectilesSystem (entitySystems.projectileEntitySystem, worldBounds.height)
    , explosionAnimationSystem (entitySystems.explosionEntitySystem)
    , cloudMovementSystem (entitySystems.cloudEntitySystem)
    , backgroundMovementSystem (entitySystems.backgroundEntitySystem)
    , playerKilledSystem (playerAircraftInitializer.getPlayerAircaft(), endGameCallback)
    , starMovementSystem(starInitializer.getStarEntity(), playerAircraftInitializer.getPlayerAircaft())
    , simpleControls (playerAircraftInitializer.getPlayerAircaft())
    {
        worldView.setCenter(spawnPosition);
    }

    void draw()
    {
        gameRenderTexture.setView(worldView);

        drawEntities(entitySystems.backgroundEntitySystem);
        drawEntities(entitySystems.cloudEntitySystem);
        drawEntities(entitySystems.explosionEntitySystem);
        drawEntities(entitySystems.projectileEntitySystem);
        drawEntities(entitySystems.enemyAircraftEntitySystem);
        drawEntities(entitySystems.playerAircraftEntitySystem);
        drawEntities(entitySystems.labelEntitySystem);
        drawEntities(entitySystems.starEntitySystem);
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

        simpleControls.update();

        entitySystems.playerAircraftEntitySystem.update(delta);
        entitySystems.projectileEntitySystem.update(delta);
        entitySystems.enemyAircraftEntitySystem.update(delta);
        entitySystems.labelEntitySystem.update(delta);
        entitySystems.explosionEntitySystem.update(delta);
        entitySystems.cloudEntitySystem.update(delta);
        entitySystems.starEntitySystem.update(delta);

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

    void processEvent(const sf::Event& event)
    {
        simpleControls.handleEvent(event);
    }

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

World::World(sf::RenderTexture& gameRenderTexture, const FontHolder& font, const SoundSettings& soundSettings, const std::function<void()>& endGameCallback)
: mImpl(std::make_unique<Impl>(gameRenderTexture, font, soundSettings, endGameCallback))
{
    // Last time I ran this it was 1824 bytes
    //std::cout << "Size of World::Impl: " << sizeof(Impl) << " bytes\n";
}

void World::update(const sf::Time delta) const
{
    mImpl->update(delta);
    mImpl->lateUpdate();
}

void World::draw() const
{
    mImpl->draw();
}

void World::processEvent(const sf::Event& event) const
{
    mImpl->processEvent(event);
}

EntitySystems& World::getEntitySystems() const
{
    return mImpl->entitySystems;
}

World::~World() = default;