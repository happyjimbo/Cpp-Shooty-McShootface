#pragma once

#include "AircraftData.h"
#include "EntityObject.h"
#include "ProjectileEntity.h"
#include "ProjectileFiringData.h"

namespace Aircraft
{
    class AircraftEntity final : public EntityObject
    {
    public:
        enum Type {
            Eagle,
            Raptor
        };

        AircraftEntity() = default;
        ~AircraftEntity() override = default;

        AircraftEntity(const AircraftEntity&) = delete;
        AircraftEntity& operator=(const AircraftEntity&) = delete;

        AircraftEntity(const AircraftEntity&&) = delete;
        AircraftEntity& operator=(const AircraftEntity&&) = delete;

        void create(
            Type type,
            const TextureHolder& textures,
            ShaderHolder& shaders,
            int health);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(sf::Time delta) override;

        void triggerProjectile(const ProjectileEntity::Type& type, float spawnSpeed);

        ProjectileFiringData& getProjectileFiringData() noexcept { return mProjectileFiringData; }
        const ProjectileFiringData& getProjectileFiringData() const noexcept { return mProjectileFiringData; }

        AircraftData& getAircraftData() noexcept { return mAircraftData; }
        const AircraftData& getAircraftData() const noexcept { return mAircraftData; }

    private:

        constexpr static Textures::ID toTextureID(Type type) noexcept;

        Type mType {};
        sf::Sprite mSprite {};
        // flashShader is a borrowed pointer managed by ShaderHolder; do not delete it.
        sf::Shader* flashShader = nullptr;
        ProjectileFiringData mProjectileFiringData;
        AircraftData mAircraftData;
    };
}
