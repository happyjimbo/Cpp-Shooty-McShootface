#pragma once
#include "EntitySystem.h"

class ExplosionEntity;

namespace sf { class Time; }

class ExplosionAnimationSystem final
{
public:
    explicit ExplosionAnimationSystem(EntitySystem<ExplosionEntity>& entitySystem) noexcept;
    ~ExplosionAnimationSystem() = default;

    // delete
    explicit ExplosionAnimationSystem() = delete;

    ExplosionAnimationSystem(const ExplosionAnimationSystem&) = delete;
    ExplosionAnimationSystem& operator=(const ExplosionAnimationSystem&) = delete;

    ExplosionAnimationSystem(ExplosionAnimationSystem&&) = delete;
    ExplosionAnimationSystem& operator=(ExplosionAnimationSystem&&) = delete;

    void execute(sf::Time delta) const;

private:
    EntitySystem<ExplosionEntity>& mEntitySystem;
    constexpr static float sDelay = 0.05f;
};
