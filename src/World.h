#pragma once

#include "EntitySystem.h"
#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>
#include "PlayerControls.h"

class SpawnEnemyAircraftSystem;
class PlayerAircraftController;
class ScoreController;
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

namespace sf
{
    class RenderWindow;
}

namespace GUI { class Label; }
using GUI::Label;

struct MediaFiles
{
    static constexpr const char* Eagle = "Media/Textures/Eagle.png";
    static constexpr const char* Raptor = "Media/Textures/Raptor.png";
    static constexpr const char* Background = "Media/Textures/Grass.png";
    static constexpr const char* Bullet = "Media/Textures/Bullet.png";
    static constexpr const char* EnemyBullet = "Media/Textures/EnemyBullet.png";
    static constexpr const char* Clouds = "Media/Textures/Clouds.png";

    static constexpr const char* Font = "Media/Sansation.ttf";
};

class World final
{

public:
    explicit World(sf::RenderWindow& window);
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
    void buildScene();

    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;
    FontHolder mFonts;
    PlayerControls simpleControls;

    EntitySystem<ProjectileEntity> mProjectileEntitySystem;
    EntitySystem<AircraftEntity> mPlayerAircraftEntitySystem;
    EntitySystem<AircraftEntity> mEnemyAircraftEntitySystem;
    EntitySystem<SpriteEntity> mSpriteEntitySystem;
    EntitySystem<GUI::Label> mLabelEntitySystem;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    static constexpr float mScrollSpeed {-50.f};

    ScoreController* mScoreController;
    ProjectileController* mProjectileController;
    EnemyAircraftController* mEnemyAircraftController;
    PlayerAircraftController* mPlayerAircraftController;
    BackgroundController* mBackgroundController;
    CloudsController* mCloudsController;

    SpawnEnemyAircraftSystem* mSpawnEnemyAircraftSystem;
    ProjectileSpawnSystem* mEnemyProjectileSpawnSystem;
    ProjectileSpawnSystem* mPlayerProjectileSpawnSystem;
    ProjectileCollisionSystem* mProjectileCollisionSystem;
    RemoveOffScreenEnemiesSystem* mRemoveOffScreenEnemiesSystem;
    RemoveOffScreenProjectilesSystem* mRemoveOffScreenProjectilesSystem;
};
