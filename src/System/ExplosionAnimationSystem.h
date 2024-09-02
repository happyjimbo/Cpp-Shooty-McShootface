#pragma once
#include "EntitySystem.h"

class ExplosionEntity;

namespace sf { class Time; }

class ExplosionAnimationSystem final
{
public:
    explicit ExplosionAnimationSystem(EntitySystem<ExplosionEntity>& entitySystem) noexcept;
    void execute(sf::Time delta) const;

private:
    EntitySystem<ExplosionEntity>& mEntitySystem;
    constexpr static float sDelay = 0.05f;
};
