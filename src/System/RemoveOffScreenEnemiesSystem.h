#pragma once
#include "EntitySystem.h"

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class RemoveOffScreenEnemiesSystem {

public:
    explicit RemoveOffScreenEnemiesSystem(EntitySystem<AircraftEntity>& entities, float heightBoundary) noexcept;
    void execute() const;

private:
    EntitySystem<AircraftEntity>& mEntitySystem;
    float mHeightBoundary;
};
