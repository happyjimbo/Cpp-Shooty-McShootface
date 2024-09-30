#pragma once
#include "EntitySystem.h"

namespace Aircraft { class AircraftEntity; }

class RemoveOffScreenEnemiesSystem {

public:
    explicit RemoveOffScreenEnemiesSystem(EntitySystem<Aircraft::AircraftEntity>& entities, float heightBoundary) noexcept;

    explicit RemoveOffScreenEnemiesSystem() = delete;
    ~RemoveOffScreenEnemiesSystem() = default;

    RemoveOffScreenEnemiesSystem(const RemoveOffScreenEnemiesSystem&) = delete;
    RemoveOffScreenEnemiesSystem& operator=(const RemoveOffScreenEnemiesSystem&) = delete;

    RemoveOffScreenEnemiesSystem(RemoveOffScreenEnemiesSystem&&) = delete;
    RemoveOffScreenEnemiesSystem& operator=(RemoveOffScreenEnemiesSystem&&) = delete;

    void execute() const;

private:
    EntitySystem<Aircraft::AircraftEntity>& mEntitySystem;
    float mHeightBoundary;
};
