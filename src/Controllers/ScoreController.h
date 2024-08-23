#pragma once

#include "EntitySystem.h"
#include "Label.h"

class ScoreController final {
public:
    explicit ScoreController(EntitySystem<GUI::Label>& entitySystem) noexcept;
    void create(const FontHolder& fonts);
    void increaseScore();

private:
    EntitySystem<GUI::Label>& mEntitySystem;

    int mScore {};
    GUI::Label* mScoreTextLabel;
    GUI::Label* scoreAmountLabel;
};
