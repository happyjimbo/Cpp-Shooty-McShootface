#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "EntityObject.h"
#include "CloudData.h"
#include "ResourceIdentifiers.h"

namespace sf {
    class Sprite;
    class RenderTarget;
    class RenderStates;
    class Time;
}

class CloudEntity final : public EntityObject
{
public:
    CloudEntity() = default;
    ~CloudEntity() override = default;

    CloudEntity(const CloudEntity&) = delete;
    CloudEntity& operator=(const CloudEntity&) = delete;

    CloudEntity(CloudEntity&&) = default;
    CloudEntity& operator=(CloudEntity&&) = default;

    void create(
        const sf::Texture&,
        const TextureHolder& textures,
        ShaderHolder& shaders,
        const sf::IntRect&,
        float scrollSpeed
    );

    CloudData& getCloudData() { return mCloudData; }

    void update(sf::Time delta) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    constexpr static float sScaleX {1.5f};
    constexpr static float sScaleY {1.f};

    sf::Sprite mSprite;
    // shader is a borrowed pointer managed by ShaderHolder; do not delete it.
    sf::Shader* mShader = nullptr;
    CloudData mCloudData;
    float mAccumulatedTime {};
};