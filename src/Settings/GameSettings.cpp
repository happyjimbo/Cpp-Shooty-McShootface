#include "GameSettings.h"
#include "GameSettingsData.h"
#include "rapidcsv.h"
#include <string>

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
    GameSettingsData settings;

    try
    {
        const rapidcsv::Document doc(configPath);
        settings.title = doc.GetCell<std::string>("title", 0);
        settings.width = doc.GetCell<int>("width", 0);
        settings.height = doc.GetCell<int>("height", 0);
        settings.fps = doc.GetCell<float>("fps", 0);
        const auto muteStr = doc.GetCell<std::string>("mute", 0);
        settings.mute = muteStr == "true" || muteStr == "1";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error while loading settings: " << e.what() << std::endl;
    }

    std::cout << "settings.mute " << settings.mute << std::endl;

    return settings;
}

void GameSettings::updateSettings(const GameSettingsData& newSettings)
{
    try
    {
        if (rapidcsv::Document doc(configPath); doc.GetRowCount() > 0)
        {
            doc.SetCell<std::string>(doc.GetColumnIdx("title"), 0, newSettings.title);
            doc.SetCell<int>( doc.GetColumnIdx("width"), 0, newSettings.width);
            doc.SetCell<int>(doc.GetColumnIdx("height"), 0, newSettings.height);
            doc.SetCell<int>(doc.GetColumnIdx("fps"), 0, newSettings.fps);
            doc.SetCell<std::string>(doc.GetColumnIdx("mute"), 0, newSettings.mute ? "true" : "false");
            doc.Save();
            std::cout << "Settings saved successfully!" << std::endl;
        }
        else
        {
            std::cerr << "CSV structure not as expected!" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error while saving settings: " << e.what() << std::endl;
    }
}
