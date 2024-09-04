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

    CloudMovementSystem(const CloudMovementSystem&&) = delete;
    CloudMovementSystem& operator=(const CloudMovementSystem&&) = delete;

    void execute(sf::Time delta) const;

private:
    EntitySystem<CloudEntity>& mEntitySystem;
};
