#include "GameSettings.h"
#include "GameSettingsData.h"
#include "rapidcsv.h"
#include <string>

#include "CvsSerializer.h"

namespace
{
    GameSettingsData cachedSettings;
    bool isSettingsChanged = false;
    std::string configPath {};
}

void GameSettings::setConfigPath(const std::string& path)
{
    configPath = path;
}

GameSettingsData GameSettings::getSettings()
{
    if (isSettingsChanged)
    {
        return cachedSettings;
    }

    cachedSettings = loadSettings();
    isSettingsChanged = true;

    return cachedSettings;
}

GameSettingsData GameSettings::loadSettings()
{
    return CvsSerializer::load<GameSettingsData>(configPath);
}

void GameSettings::updateSettings(const GameSettingsData& newSettings)
{
    CvsSerializer::update(newSettings, configPath);
}
