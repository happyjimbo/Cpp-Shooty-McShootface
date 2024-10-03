#pragma once
#include <string>

struct GameSettingsData
{
    // default values, overriden by settings.csv
    std::string title = "title";
    int width = 640;
    int height = 480;
    int fps = 30.f;
};
