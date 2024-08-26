#pragma once

#include <Command/CommandQueue.h>
#include "EntitySystem.h"
#include <Resource/ResourceHolder.h>
#include <Resource/ResourceIdentifiers.h>

class PlayerAircraftController;
class ScoreController;
class ProjectileEntity;
class AircraftEntity;
class SpriteEntity;
class ProjectileController;
class EnemyAircraftController;
class ProjectileCollisionController;
class BackgroundController;

namespace sf
{
    class RenderWindow;
}

namespace GUI
{
    class Label;
}

struct MediaFiles
{
    static constexpr const char* Eagle = "Media/Textures/Eagle.png";
    static constexpr const char* Raptor = "Media/Textures/Raptor.png";
    static constexpr const char* Background = "Media/Textures/Grass.png";
    static constexpr const char* Bullet = "Media/Textures/Bullet.png";
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
    CommandQueue& getCommandQueue();

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

    EntitySystem<ProjectileEntity> mProjectileEntitySystem;
    EntitySystem<AircraftEntity> mEnemyAircraftEntitySystem;
    EntitySystem<AircraftEntity> mPlayerAircraftEntitySystem;
    EntitySystem<SpriteEntity> mSpriteEntitySystem;
    EntitySystem<GUI::Label> mLabelEntitySystem;

    CommandQueue mCommandQueue;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    static constexpr float mScrollSpeed {-50.f};

    PlayerAircraftController* mPlayerAircraftController;
    ScoreController* mScoreController;
    BackgroundController* mBackgroundController;
    EnemyAircraftController* mEnemyAircraftController;
    ProjectileController* mProjectileController;
    ProjectileCollisionController* mProjectileCollisionController;
};
