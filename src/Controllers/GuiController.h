#pragma once

#include "EntitySystem.h"
#include "Label.h"

struct PlayerData;
namespace Aircraft { class AircraftEntity; }

using Aircraft::AircraftEntity;
using GUI::Label;

class GuiController final {
public:
    explicit GuiController(
        const FontHolder& fonts,
        EntitySystem<Label>& entitySystem,
        const AircraftEntity& playerAircraft,
        const PlayerData& playerData,
        float screenWidth
    ) noexcept;

    ~GuiController() = default;

    explicit GuiController(GuiController&) = delete;
    GuiController& operator=(GuiController&) = delete;

    explicit GuiController(GuiController&&) = delete;
    GuiController& operator=(GuiController&&) = delete;

    void increaseScore();
    void playerHit() const;

private:
    const AircraftEntity& mPlayerAircraft;

    int mScore {};

    Label* mScoreAmountLabel;
    Label* mPlayerHealth;
};
