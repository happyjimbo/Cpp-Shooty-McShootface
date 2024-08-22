#include "ScoreController.h"

ScoreController::ScoreController(GUI::Label& scoreLabel)
: mScoreLabel(scoreLabel)
{

}

void ScoreController::increaseScore() {
    ++mScore;
    mScoreLabel.setText(std::to_string(mScore));
}
