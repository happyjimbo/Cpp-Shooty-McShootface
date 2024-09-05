#pragma once

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
        AircraftEntity(Type, const TextureHolder&) = delete;
        ~AircraftEntity() override = default;

        AircraftEntity(const AircraftEntity&) = delete;
        AircraftEntity operator=(const AircraftEntity&) = delete;

        AircraftEntity(const AircraftEntity&&) = delete;
        AircraftEntity operator=(const AircraftEntity&&) = delete;

        void create(Type type, const TextureHolder& textures, int health);

        unsigned int getCategory() const noexcept override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void triggerProjectile(const ProjectileEntity::Type& type, float spawnSpeed);

        ProjectileFiringData& getProjectileFiringData() noexcept { return mProjectileFiringData; }
        const ProjectileFiringData& getProjectileFiringData() const noexcept { return mProjectileFiringData; }

        // these could be in their own data struct, in a more ecs approach
        int getHealth() const { return mHealth; }
        void hit() { --mHealth; }
        bool destroyed() const { return  mHealth <= 0; }

    private:

        constexpr static Textures::ID toTextureID(Type type) noexcept;
        Textures::ID mTexture {};

        Type mType {};
        sf::Sprite mSprite {};
        int mHealth {};
        ProjectileFiringData mProjectileFiringData;
    };
}
