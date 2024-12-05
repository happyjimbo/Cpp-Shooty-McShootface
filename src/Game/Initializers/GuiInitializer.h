#pragma once

#include "EntitySystem.h"
#include "Label.h"

struct PlayerData;
namespace Aircraft { class AircraftEntity; }

class GuiInitializer final {
public:
    explicit GuiInitializer(
        const FontHolder& fonts,
        EntitySystem<GUI::Label>& entitySystem,
        const Aircraft::AircraftEntity& playerAircraft,
        const PlayerData& playerData,
        float screenWidth
    ) noexcept;

    ~GuiInitializer() = default;

    explicit GuiInitializer(const GuiInitializer&) = delete;
    GuiInitializer& operator=(const GuiInitializer&) = delete;

    explicit GuiInitializer(GuiInitializer&&) = delete;
    GuiInitializer& operator=(GuiInitializer&&) = delete;

    void increaseScore();
    void playerHit() const;

private:
    const Aircraft::AircraftEntity& mPlayerAircraft;

    int mScore {};

    GUI::Label* mScoreAmountLabel;
    GUI::Label* mPlayerHealth;
};
