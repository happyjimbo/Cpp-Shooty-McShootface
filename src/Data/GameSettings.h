#pragma once
#include <string>

struct GameSettings
{
    // default values, overriden by settings.csv
    std::string title = "title";
    int width = 640;
    int height = 480;
    float fps = 30.f;
};