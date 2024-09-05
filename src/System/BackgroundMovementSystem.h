#pragma once

#include "EntitySystem.h"

class BackgroundEntity;

class BackgroundMovementSystem final
{
public:
    explicit BackgroundMovementSystem(EntitySystem<BackgroundEntity>& entitySystem) noexcept;
    ~BackgroundMovementSystem() noexcept = default;

    BackgroundMovementSystem(const BackgroundMovementSystem&) = delete;
    BackgroundMovementSystem& operator=(const BackgroundMovementSystem&) = delete;

    BackgroundMovementSystem(const BackgroundMovementSystem&&) = delete;
    BackgroundMovementSystem& operator=(const BackgroundMovementSystem&&) = delete;

    void execute(const sf::Time& delta) const;

private:
    EntitySystem<BackgroundEntity>& mEntitySystem;
};
