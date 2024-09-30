#include "GuiController.h"
#include "PlayerData.h"
#include "AircraftEntity.h"
#include "PlayerAircraftController.h"

namespace
{
    const sf::Vector2f ScoreTextLabelPos(10, 10);
    const sf::Vector2f ScoreAmountLabelPos(60, 10);
    const sf::Vector2f PlayerHealthLabelPos(50, 10);
}

GuiController::GuiController(
    const FontHolder& fonts,
    EntitySystem<GUI::Label>& entitySystem,
    const Aircraft::AircraftEntity& playerAircraft,
    const PlayerData& playerData,
    const float screenWidth
) noexcept
: mPlayerAircraft(playerAircraft)
{
    const auto mScoreTextLabel = entitySystem.createObject("Score:", fonts);
    mScoreTextLabel->setPosition(ScoreTextLabelPos);

    mScoreAmountLabel = entitySystem.createObject("0", fonts);
    mScoreAmountLabel->setPosition(ScoreAmountLabelPos);

    const auto playerString = std::to_string(playerData.Health);
    mPlayerHealth = entitySystem.createObject(playerString, fonts);
    mPlayerHealth->setPosition(screenWidth - PlayerHealthLabelPos.x, PlayerHealthLabelPos.y);
}

void GuiController::playerHit() const
{
    mPlayerHealth->setText(std::to_string(mPlayerAircraft.getAircraftData().getHealth()));
}

void GuiController::increaseScore() {
    ++mScore;
    mScoreAmountLabel->setText(std::to_string(mScore));
}
