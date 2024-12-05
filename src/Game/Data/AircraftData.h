#pragma once

struct AircraftData
{
    int mHealth {};
    bool isFlashing {};
    float flashingAccumulatedTime = 0.0f;

    int getHealth() const { return mHealth; }
    void hit()
    {
        --mHealth;
        isFlashing = true;
    }

    bool destroyed() const { return  mHealth <= 0; }
};