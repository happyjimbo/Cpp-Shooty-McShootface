#ifndef CMAKESFMLPROJECT_WORLD_H
#define CMAKESFMLPROJECT_WORLD_H

#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "Aircraft.h"

class World {

public:
    explicit                            World(sf::RenderWindow& window);
    void                                update(sf::Time);
    void                                draw();

private:
    void                                loadTextures();
    void                                buildScene();

private:
    enum Layer {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderWindow&                   mWindow;
    sf::View                            mWorldView;
    TextureHolder                       mTextures;

    SceneNode                           mSceneGraph;
    std::array<SceneNode*, LayerCount>  mSceneLayer;

    sf::FloatRect                       mWorldBounds;
    sf::Vector2f                        mSpawnPosition;
    float                               mScrollSpeed;
    Aircraft*                           mPlayerAircraft;
};


#endif //CMAKESFMLPROJECT_WORLD_H
