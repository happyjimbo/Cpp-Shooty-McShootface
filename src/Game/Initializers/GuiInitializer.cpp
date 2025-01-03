#include "GuiInitializer.h"
#include "PlayerData.h"
#include "AircraftEntity.h"
#include "PlayerAircraftInitializer.h"

namespace
{
    const sf::Vector2f ScoreTextLabelPos(10, 10);
    const sf::Vector2f ScoreAmountLabelPos(60, 10);
    const sf::Vector2f PlayerHealthLabelPos(50, 10);
}

GuiInitializer::GuiInitializer(
    const FontHolder& fonts,
    EntitySystem<GUI::Label>& entitySystem,
    const Aircraft::AircraftEntity& playerAircraft,
    const PlayerData& playerData,
    const float screenWidth
) noexcept
: mPlayerAircraft(playerAircraft)
{
    entitySystem.prePool(3);

    const auto mScoreTextLabel = entitySystem.createObject("Score:", fonts);
    mScoreTextLabel->setPosition(ScoreTextLabelPos);

    mScoreAmountLabel = entitySystem.createObject("0", fonts);
    mScoreAmountLabel->setPosition(ScoreAmountLabelPos);

    const auto playerString = std::to_string(playerData.Health);
    mPlayerHealth = entitySystem.createObject(playerString, fonts);
    mPlayerHealth->setPosition(screenWidth - PlayerHealthLabelPos.x, PlayerHealthLabelPos.y);
}

void GuiInitializer::playerHit() const
{
    mPlayerHealth->setText(std::to_string(mPlayerAircraft.getAircraftData().getHealth()));
}

void GuiInitializer::increaseScore() {
    ++mScore;
    mScoreAmountLabel->setText(std::to_string(mScore));
}
