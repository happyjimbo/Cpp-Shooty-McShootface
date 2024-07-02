#ifndef CMAKESFMLPROJECT_SPRITENODE_H
#define CMAKESFMLPROJECT_SPRITENODE_H

#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
    explicit            SpriteNode(const sf::Texture&);
                        SpriteNode(const sf::Texture&, const sf::IntRect&);

private:
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite          mSprite;
};

#endif //CMAKESFMLPROJECT_SPRITENODE_H