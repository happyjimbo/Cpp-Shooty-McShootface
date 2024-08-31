#include "ScoreController.h"

ScoreController::ScoreController(EntitySystem<Label>& entitySystem) noexcept
: mEntitySystem(entitySystem)
{

}

void ScoreController::create(const FontHolder& fonts)
{
    mScoreTextLabel = mEntitySystem.createObject("Score:", fonts);
    mScoreTextLabel->setPosition(10, 10);

    scoreAmountLabel = mEntitySystem.createObject("0", fonts);
    scoreAmountLabel->setPosition(60, 10);
}

void ScoreController::increaseScore() {
    ++mScore;
    scoreAmountLabel->setText(std::to_string(mScore));
}
