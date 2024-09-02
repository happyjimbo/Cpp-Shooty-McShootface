#pragma once

#include "EntitySystem.h"
#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>
#include "PlayerControls.h"

class PlayerKilledSystem;
class ExplosionAnimationSystem;
class ExplosionController;
class ExplosionEntity;
class SpawnEnemyAircraftSystem;
class PlayerAircraftController;
class GuiController;
class ProjectileEntity;
class SpriteEntity;
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
    explicit World(sf::RenderWindow& window, const std::function<void()>& endGameCallback);
    ~World();

    void update(sf::Time);
    void draw();
private:

    enum Layer
    {
        Background,
        Air,
        Bulelts,
        GUI,
        LayerCount
    };

    template <typename T>
    void drawEntities(EntitySystem<T>& system);
    void loadTextures();
    void loadFonts();
    void initLogic();

    sf::RenderWindow& mWindow;
    sf::View mWorldView;

    const std::function<void()>& mEndGameCallback;

    TextureHolder mTextures;
    FontHolder mFonts;
    PlayerControls simpleControls;

    EntitySystem<ProjectileEntity> mProjectileEntitySystem;
    EntitySystem<AircraftEntity> mPlayerAircraftEntitySystem;
    EntitySystem<AircraftEntity> mEnemyAircraftEntitySystem;
    EntitySystem<SpriteEntity> mSpriteEntitySystem;
    EntitySystem<ExplosionEntity> mExplosionEntitySystem;
    EntitySystem<Label> mLabelEntitySystem;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    static constexpr float mScrollSpeed {-50.f};

    GuiController* mScoreController;
    ProjectileController* mProjectileController;
    EnemyAircraftController* mEnemyAircraftController;
    PlayerAircraftController* mPlayerAircraftController;
    BackgroundController* mBackgroundController;
    CloudsController* mCloudsController;
    ExplosionController* mExplosionController;

    SpawnEnemyAircraftSystem* mSpawnEnemyAircraftSystem;
    ProjectileSpawnSystem* mEnemyProjectileSpawnSystem;
    ProjectileSpawnSystem* mPlayerProjectileSpawnSystem;
    ProjectileCollisionSystem* mProjectileCollisionSystem;
    RemoveOffScreenEnemiesSystem* mRemoveOffScreenEnemiesSystem;
    RemoveOffScreenProjectilesSystem* mRemoveOffScreenProjectilesSystem;
    ExplosionAnimationSystem* mExplosionAnimationSystem;
    PlayerKilledSystem* mPlayerKilledSystem;
};
