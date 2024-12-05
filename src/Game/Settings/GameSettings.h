#pragma once
#include <functional>

struct GameSettingsData;

class GameSettings final
{
public:
    static void setConfigPath(const std::string&);
    static GameSettingsData getSettings();
    static void updateSettings(const GameSettingsData& newSettings);
    static void settingsUpdated(const std::function<void()>& callback);
private:
    static GameSettingsData loadSettings();
};