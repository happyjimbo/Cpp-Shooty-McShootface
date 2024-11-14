#pragma once

#include "EntityObject.h"
#include <SFML/Graphics/Sprite.hpp>

class StarEntity final : public EntityObject
{
public:
    explicit StarEntity() = default;
    ~StarEntity() override = default;

    StarEntity(const StarEntity&) = delete;
    StarEntity& operator=(StarEntity&) = delete;

    StarEntity(const StarEntity&&) = delete;
    StarEntity& operator=(StarEntity&&) = delete;

    void create(const sf::Texture& texture);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time delta) override;

private:
    sf::Sprite mSprite{};
};
