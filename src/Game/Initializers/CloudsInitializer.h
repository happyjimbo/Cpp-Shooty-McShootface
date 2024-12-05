#pragma once

#include "EntitySystem.h"
#include "ResourceIdentifiers.h"

#include "CloudEntity.h"

class CloudsInitializer final
{
public:
    explicit CloudsInitializer(
        EntitySystem<CloudEntity>& entitySystem,
        TextureHolder& textures,
        ShaderHolder& shaders,
        float scrollSpeed
    );

    CloudsInitializer(const CloudsInitializer&) = delete;
    CloudsInitializer& operator=(const CloudsInitializer&) = delete;

    CloudsInitializer(CloudsInitializer&&) = delete;
    CloudsInitializer& operator=(CloudsInitializer&&) = delete;

    ~CloudsInitializer() noexcept = default;
};
