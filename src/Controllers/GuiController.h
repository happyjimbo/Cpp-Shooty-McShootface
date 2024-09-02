#pragma once

#include "EntitySystem.h"
#include "Label.h"

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

using GUI::Label;

class GuiController final {
public:
    explicit GuiController(EntitySystem<Label>& entitySystem, const AircraftEntity& playerAircraft, float screenWidth) noexcept;
    void create(const FontHolder& fonts);
    void increaseScore();
    void playerHit() const;

private:
    EntitySystem<Label>& mEntitySystem;
    const AircraftEntity& mPlayerAircraft;

    int mScore {};

    Label* mScoreTextLabel;
    Label* mScoreAmountLabel;
    Label* mPlayerHealth;
    const float mScreenWidth {};
};
