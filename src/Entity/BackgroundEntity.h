#pragma once

#include "EntityObject.h"
#include "BackgroundData.h"

#include <SFML/Graphics/Sprite.hpp>

namespace sf {
    class RenderTarget;
    class RenderStates;
}

class BackgroundEntity final : public EntityObject
{
public:
    BackgroundEntity() noexcept = default;
    ~BackgroundEntity() override = default;

    BackgroundEntity(const BackgroundEntity&) = delete;
    BackgroundEntity operator=(const BackgroundEntity&) = delete;

    BackgroundEntity(const BackgroundEntity&&) = delete;
    BackgroundEntity operator=(const BackgroundEntity&&) = delete;

    BackgroundEntity(const sf::Texture&, sf::Vector2u bounds, float scrollSpeed) = delete;

    void create(const sf::Texture&, sf::Vector2u bounds, float scrollSpeed);

    BackgroundData& getBackgroundData() { return mBackgrounData; };

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite mSprite;
    BackgroundData mBackgrounData;
};