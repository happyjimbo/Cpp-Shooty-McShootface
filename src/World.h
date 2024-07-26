#ifndef CMAKESFMLPROJECT_WORLD_H
#define CMAKESFMLPROJECT_WORLD_H

#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "Aircraft.h"
#include "CommandQueue.h"
#include "BulletController.h"

// forward declaration
namespace sf
{
    class RenderWindow;
}

class World {

public:
    explicit                            World(sf::RenderWindow& window);
    void                                update(sf::Time);
    void                                draw();

    CommandQueue&                       getCommandQueue();


private:
    void                                loadTextures();
    void                                buildScene();
    void                                adaptPlayerPosition();
    void                                adaptPlayerVelocity();

private:
    enum Layer {
        Background,
        Air,
        Bulelts,
        LayerCount
    };

private:
    sf::RenderWindow&                   mWindow;
    sf::View                            mWorldView;
    TextureHolder                       mTextures;

    SceneNode                           mSceneGraph;
    std::array<SceneNode*, LayerCount>  mSceneLayer;
    CommandQueue                        mCommandQueue;

    sf::FloatRect                       mWorldBounds;
    sf::Vector2f                        mSpawnPosition;
    float                               mScrollSpeed;
    Aircraft*                           mPlayerAircraft;
    BulletController*                   mBulletController;
};


#endif //CMAKESFMLPROJECT_WORLD_H
