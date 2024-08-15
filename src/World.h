#ifndef CMAKESFMLPROJECT_WORLD_H
#define CMAKESFMLPROJECT_WORLD_H

#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "Entity/AircraftEntity.h"
#include "CommandQueue.h"
#include "ProjectileController.h"
#include "EnemyAircraftController.h"
#include "EntitySystem.h"
#include "Label.h"
#include "ProjectileCollisionController.h"
#include "SpriteEntity.h"

// forward declaration
namespace sf
{
    class RenderWindow;
}

class World final {

    public:
        explicit                            World(sf::RenderWindow& window);
                                            ~World();

    public:
        void                                update(sf::Time);
        void                                draw();

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

        EntitySystem<ProjectileEntity>      mProjectileEntitySystem;
        EntitySystem<AircraftEntity>        mEnemyAircraftEntitySystem;
        EntitySystem<AircraftEntity>        mPlayerAircraftEntitySystem;
        EntitySystem<SpriteEntity>          mSpriteEntitySystem;
        EntitySystem<GUI::Label>            mLabelEntitySystem;

        CommandQueue                        mCommandQueue;

        sf::FloatRect                       mWorldBounds;
        sf::Vector2f                        mSpawnPosition;
        float                               mScrollSpeed;



    private:
        AircraftEntity*                     mPlayerAircraft;
        ProjectileController*               mProjectileController;
        EnemyAircraftController*            mEnemyAircraftController;
        ProjectileCollisionController*      mProjectileCollisionController;
};


#endif //CMAKESFMLPROJECT_WORLD_H
