#pragma once

#include "EntitySystem.h"
#include "Label.h"

using GUI::Label;

class ScoreController final {
public:
    explicit ScoreController(EntitySystem<Label>& entitySystem) noexcept;
    void create(const FontHolder& fonts);
    void increaseScore();

private:
    EntitySystem<Label>& mEntitySystem;

    int mScore {};
    Label* mScoreTextLabel;
    Label* scoreAmountLabel;
};
