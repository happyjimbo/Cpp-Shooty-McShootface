#pragma once
#include <string>

struct GameSettingsData;

class GameSettings final
{
public:
    static void setConfigPath(const std::string&);
    static GameSettingsData getSettings();
    static void updateSettings(const GameSettingsData& newSettings);
private:
    static GameSettingsData loadSettings();
};