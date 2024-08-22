#pragma once

#include "Label.h"

class ScoreController final {
public:
    explicit ScoreController( GUI::Label& scoreLabel);
    void increaseScore();

private:
    GUI::Label& mScoreLabel;
    int mScore {};
};
