#ifndef CMAKESFMLPROJECT_WORLD_H
#define CMAKESFMLPROJECT_WORLD_H

#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "Aircraft.h"
#include "CommandQueue.h"
#include "ProjectileController.h"
#include "EnemyAircraftController.h"
#include "EntitySystem.h"
#include "ProjectileCollisionController.h"

// forward declaration
namespace sf
{
    class RenderWindow;
}

class World final {

    public:
        explicit                            World(sf::RenderWindow& window);
        void                                update(sf::Time);
        void                                draw() const;

        CommandQueue&                       getCommandQueue();


    private:
        void                                loadTextures();
        void                                loadFonts();
        void                                buildScene();
        void                                adaptPlayerPosition() const;
        void                                adaptPlayerVelocity() const;

    private:
        enum Layer {
            Background,
            Air,
            Bulelts,
            GUI,
            LayerCount
        };

    private:
        sf::RenderWindow&                   mWindow;
        sf::View                            mWorldView;
        TextureHolder                       mTextures;
        FontHolder                          mFonts;

        EntitySystem                       mEntitySystem;

        SceneNode                           mSceneGraph;
        std::array<SceneNode*, LayerCount>  mSceneLayer;
        CommandQueue                        mCommandQueue;

        sf::FloatRect                       mWorldBounds;
        sf::Vector2f                        mSpawnPosition;
        float                               mScrollSpeed;
        Aircraft*                           mPlayerAircraft;

    private:
        std::shared_ptr<ProjectileController>               mProjectileController;
        std::shared_ptr<EnemyAircraftController>            mEnemyAircraftController;
        std::unique_ptr<ProjectileCollisionController>      mProjectileCollisionController;
};


#endif //CMAKESFMLPROJECT_WORLD_H
