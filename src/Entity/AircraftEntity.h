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
        AircraftEntity(Type type, const TextureHolder& textures) = delete;
        ~AircraftEntity() override = default;

        void create(Type type, const TextureHolder& textures);

        unsigned int getCategory() const noexcept override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void triggerProjectile(const ProjectileEntity::Type& type, float spawnSpeed);

        ProjectileFiringData& getProjectileFiringData() noexcept { return mProjectileFiringData; }
        const ProjectileFiringData& getProjectileFiringData() const noexcept { return mProjectileFiringData; }

    private:

        static Textures::ID toTextureID(Type type) noexcept;
        Textures::ID mTexture {};

        Type mType {};
        sf::Sprite mSprite {};
        ProjectileFiringData mProjectileFiringData;
    };
}
