#pragma once

#include "EntitySystem.h"

class CloudEntity;

class CloudMovementSystem final
{
public:
    explicit CloudMovementSystem(EntitySystem<CloudEntity>& entitySystem) noexcept;
    ~CloudMovementSystem() noexcept = default;

    CloudMovementSystem(const CloudMovementSystem&) = delete;
    CloudMovementSystem& operator=(const CloudMovementSystem&) = delete;

    CloudMovementSystem(CloudMovementSystem&&) = delete;
    CloudMovementSystem& operator=(CloudMovementSystem&&) = delete;

    void execute(const sf::Time& delta) const;

private:
    EntitySystem<CloudEntity>& mEntitySystem;
};
