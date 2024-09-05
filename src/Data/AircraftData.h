#pragma once

struct AircraftData
{
    int mHealth {};

    int getHealth() const { return mHealth; }
    void hit() { --mHealth; }
    bool destroyed() const { return  mHealth <= 0; }
};