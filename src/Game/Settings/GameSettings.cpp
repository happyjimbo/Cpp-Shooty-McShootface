#include "GameSettings.h"
#include "GameSettingsData.h"
#include "rapidcsv.h"
#include <string>
#include "CvsSerializer.h"

namespace
{
    GameSettingsData cachedSettings;
    bool isSettingsStale = true;
    std::string configPath {};
    std::function<void()> callback;

}

void GameSettings::setConfigPath(const std::string& path)
{
    configPath = path;
}

GameSettingsData GameSettings::getSettings()
{
    if (!isSettingsStale)
    {
        return cachedSettings;
    }

    cachedSettings = loadSettings();
    isSettingsStale = false;

    return cachedSettings;
}

GameSettingsData GameSettings::loadSettings()
{
    return CvsSerializer::loadAsync<GameSettingsData>(configPath);
}

void GameSettings::updateSettings(const GameSettingsData& newSettings)
{
    CvsSerializer::updateAsync(newSettings, configPath);
    isSettingsStale = true;
    callback();
}

void GameSettings::settingsUpdated(const std::function<void()>& call)
{
    callback = call;
}