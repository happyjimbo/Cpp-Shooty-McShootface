#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "EntityObject.h"
#include "ResourceIdentifiers.h"

class ProjectileEntity final : public EntityObject
{
public:
    enum Type {
        Player,
        Enemy
    };

    ProjectileEntity() = default;
    ProjectileEntity(Type type, const TextureHolder& textures) = delete;
    ~ProjectileEntity() override = default;

    void create(Type type, const TextureHolder& textures);
    void update(sf::Time delta) override;
    Type getType() const noexcept;
    unsigned int getCategory() const noexcept override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Textures::ID toTextureID(Type type) noexcept;

    sf::Sprite mSprite {};
    Type mType {};
};
