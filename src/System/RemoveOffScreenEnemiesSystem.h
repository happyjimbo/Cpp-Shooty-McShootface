#pragma once
#include "EntitySystem.h"

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

class RemoveOffScreenEnemiesSystem {

public:
    explicit RemoveOffScreenEnemiesSystem(EntitySystem<AircraftEntity>& entities, float heightBoundary) noexcept;

    explicit RemoveOffScreenEnemiesSystem() = delete;
    ~RemoveOffScreenEnemiesSystem() = default;

    RemoveOffScreenEnemiesSystem(const RemoveOffScreenEnemiesSystem&) = delete;
    RemoveOffScreenEnemiesSystem& operator=(const RemoveOffScreenEnemiesSystem&) = delete;

    RemoveOffScreenEnemiesSystem(RemoveOffScreenEnemiesSystem&&) = delete;
    RemoveOffScreenEnemiesSystem& operator=(RemoveOffScreenEnemiesSystem&&) = delete;

    void execute() const;

private:
    EntitySystem<AircraftEntity>& mEntitySystem;
    float mHeightBoundary;
};
