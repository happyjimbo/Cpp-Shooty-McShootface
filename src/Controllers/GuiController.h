#pragma once

#include "EntitySystem.h"
#include "Label.h"

struct PlayerData;
namespace Aircraft { class AircraftEntity; }

class GuiController final {
public:
    explicit GuiController(
        const FontHolder& fonts,
        EntitySystem<GUI::Label>& entitySystem,
        const Aircraft::AircraftEntity& playerAircraft,
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
    const Aircraft::AircraftEntity& mPlayerAircraft;

    int mScore {};

    GUI::Label* mScoreAmountLabel;
    GUI::Label* mPlayerHealth;
};
