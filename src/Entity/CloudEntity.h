#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "EntityObject.h"
#include "CloudData.h"

namespace sf {
    class RenderTarget;
    class RenderStates;
}

class CloudEntity final : public EntityObject
{
public:
    CloudEntity() = default;
    CloudEntity(const sf::Texture&, const sf::IntRect&, float scrollSpeed) = delete;
    ~CloudEntity() override = default;

    CloudEntity(const CloudEntity&) = delete;
    CloudEntity operator=(const CloudEntity&) = delete;

    CloudEntity(const CloudEntity&&) = delete;
    CloudEntity operator=(const CloudEntity&&) = delete;

    void create(const sf::Texture&, const sf::IntRect&, float scrollSpeed);

    CloudData& getCloudData() { return mCloudData; };

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    constexpr static float sScaleX {1.5f};
    constexpr static float sScaleY {1.f};

    sf::Sprite mSprite;
    CloudData mCloudData;
};