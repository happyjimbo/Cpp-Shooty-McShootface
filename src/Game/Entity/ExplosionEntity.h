#pragma once

#include "EntityObject.h"
#include "AnimationData.h"

#include <SFML/Graphics/Sprite.hpp>

namespace sf {
    class RenderTarget;
    class RenderStates;
}


class ExplosionEntity final : public EntityObject
{
public:
    ExplosionEntity() = default;
    ~ExplosionEntity() override = default;

    ExplosionEntity(const ExplosionEntity&) = delete;
    ExplosionEntity& operator=(const ExplosionEntity&) = delete;

    ExplosionEntity(ExplosionEntity&&) = default;
    ExplosionEntity& operator=(ExplosionEntity&&) = default;

    void create(const sf::Texture& texture, const sf::IntRect& rect);
    void setTextureRect(sf::IntRect rect);

    AnimationData& getExplosionData() { return mExplosionData; };

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite mSprite;
    AnimationData mExplosionData;
};