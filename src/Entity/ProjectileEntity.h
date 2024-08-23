#pragma once

#include "EntityObject.h"
#include "../ResourceIdentifiers.h"
#include "SFML/Graphics/Sprite.hpp"

class ProjectileEntity final : public EntityObject
{
public:
    enum Type {
        Player,
        Enemy
    };

    explicit ProjectileEntity(Type type, const TextureHolder& textures);
    void update(sf::Time delta) override;
    Type getType() const;
    unsigned int getCategory() const override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite mSprite;
    Type mType;
};
