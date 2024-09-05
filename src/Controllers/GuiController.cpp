#include "GuiController.h"

#include "AircraftEntity.h"
#include "PlayerAircraftController.h"

GuiController::GuiController(EntitySystem<Label>& entitySystem, const AircraftEntity& playerAircraft, const float screenWidth) noexcept
: mEntitySystem(entitySystem)
, mPlayerAircraft(playerAircraft)
, mScreenWidth(screenWidth)
{

}

void GuiController::create(const FontHolder& fonts)
{
    mScoreTextLabel = mEntitySystem.createObject("Score:", fonts);
    mScoreTextLabel->setPosition(10, 10);

    mScoreAmountLabel = mEntitySystem.createObject("0", fonts);
    mScoreAmountLabel->setPosition(60, 10);


    const auto playerString = std::to_string(PlayerAircraftController::sPlayerHealth);
    mPlayerHealth = mEntitySystem.createObject(playerString, fonts);
    mPlayerHealth->setPosition(mScreenWidth - 50, 10);
}

void GuiController::playerHit() const
{
    mPlayerHealth->setText(std::to_string(mPlayerAircraft.getAircraftData().getHealth()));
}

void GuiController::increaseScore() {
    ++mScore;
    mScoreAmountLabel->setText(std::to_string(mScore));
}
