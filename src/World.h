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

namespace GUI {
    class Label;
}

class World final {

public:
    explicit World(sf::RenderWindow& window);
    ~World();

    void update(sf::Time);
    void draw();
    CommandQueue& getCommandQueue();

private:

    enum Layer {
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
    void adaptPlayerPosition() const;
    void adaptPlayerVelocity() const;

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
    float mScrollSpeed;

    PlayerAircraftController* mPlayerAircraftController;
    ScoreController* mScoreController;
    BackgroundController* mBackgroundController;
    EnemyAircraftController* mEnemyAircraftController;
    ProjectileController* mProjectileController;
    ProjectileCollisionController* mProjectileCollisionController;
};
