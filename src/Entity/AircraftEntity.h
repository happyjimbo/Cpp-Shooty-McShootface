#pragma once

#include "EntityObject.h"
#include "ProjectileEntity.h"

class ProjectileController;

class AircraftEntity final : public EntityObject
{
public:
    enum Type {
        Eagle,
        Raptor
    };

    AircraftEntity() = default;
    AircraftEntity(ProjectileController& projectileController, Type type, const TextureHolder& textures) = delete;

    void create(ProjectileController* projectileController, Type type, const TextureHolder& textures);
    unsigned int getCategory() const noexcept override;
    void update(sf::Time delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void triggerProjectile(const ProjectileEntity::Type& type, float spawnSpeed);
    void hit();

private:
    enum Position {
        Left,
        Right
    };

    static Textures::ID toTextureID(Type type) noexcept;
    Textures::ID mTexture {};

    Type mType {};
    sf::Sprite mSprite {};
    ProjectileController* mProjectileController;

    static constexpr float mXOffsetAmount = 15.f;
    static constexpr float mYOffsetAmount = 5.f;

    Position mPosition = Left;
    float mTimeSinceLastProjectileSpawn = 0;
};