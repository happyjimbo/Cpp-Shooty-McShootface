#pragma once

#include "EntitySystem.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "PlayerControls.h"

class SoundEffects;
class ProjectileMovementSystem;
class EnemyAircraftMovementSystem;
class PlayerAircraftMovementSystem;
class BackgroundMovementSystem;
class CloudMovementSystem;
class PlayerKilledSystem;
class ExplosionAnimationSystem;
class ExplosionController;
class ExplosionEntity;
class SpawnEnemyAircraftSystem;
class PlayerAircraftController;
class GuiController;
class ProjectileEntity;
class BackgroundEntity;
class CloudEntity;
class ProjectileController;
class EnemyAircraftController;
class BackgroundController;
class CloudsController;

class ProjectileCollisionSystem;
class ProjectileSpawnSystem;
class RemoveOffScreenEnemiesSystem;
class RemoveOffScreenProjectilesSystem;

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

namespace sf { class RenderWindow; }

namespace GUI { class Label; }
using GUI::Label;

class World final
{

public:
    explicit World(sf::RenderWindow& window, const FontHolder& font, const std::function<void()>& endGameCallback);
    ~World();

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    World(World&&) = delete;
    World& operator=(World&&) = delete;

    void update(sf::Time);
    void draw();
private:

    template <typename T>
    void drawEntities(EntitySystem<T>& system);
    void loadTextures();
    void initLogic();

    sf::RenderWindow& mWindow;
    sf::View mWorldView;

    const std::function<void()>& mEndGameCallback;

    TextureHolder mTextures;
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
