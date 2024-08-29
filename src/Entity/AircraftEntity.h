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
    enum Position {
        Left,
        Right
    };

    AircraftEntity() = default;
    AircraftEntity(Type type, const TextureHolder& textures) = delete;
    ~AircraftEntity() override = default;

    void create(Type type, const TextureHolder& textures);
    unsigned int getCategory() const noexcept override;
    void update(sf::Time delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void triggerProjectile(const ProjectileEntity::Type& type, float spawnSpeed);

    bool needsToFireProjectile() const noexcept { return mNeedsToFireProjectile; }
    ProjectileEntity::Type getProjectileType() const noexcept { return mProjectileType; }
    Position getProjectilePosition() const noexcept { return mPosition; }
    void resetFireProjectile() { mNeedsToFireProjectile = false; }

    static constexpr float XOffsetAmount = 15.f;
    static constexpr float YOffsetAmount = 5.f;

private:

    static Textures::ID toTextureID(Type type) noexcept;
    Textures::ID mTexture {};

    Type mType {};
    sf::Sprite mSprite {};

    Position mPosition = Left;
    float mTimeSinceLastProjectileSpawn = 0;

    bool mNeedsToFireProjectile = false;
    ProjectileEntity::Type mProjectileType;
};