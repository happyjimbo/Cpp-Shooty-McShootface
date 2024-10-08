#pragma once

#include "EntitySystem.h"
#include "ResourceIdentifiers.h"

#include "CloudEntity.h"

class CloudsController final
{
public:
    explicit CloudsController(
        EntitySystem<CloudEntity>& entitySystem,
        TextureHolder& textures,
        ShaderHolder& shaders,
        float scrollSpeed
    );

    CloudsController(CloudsController&) = delete;
    CloudsController& operator=(CloudsController&) = delete;

    CloudsController(CloudsController&&) = delete;
    CloudsController& operator=(CloudsController&&) = delete;

    ~CloudsController() noexcept = default;
};
