#include "GameSettings.h"
#include "GameSettingsData.h"
#include "rapidcsv.h"
#include <string>

GameSettings::GameSettings(std::unique_ptr<CsvSerializerImpl<GameSettingsData>> csvSerializerImpl, const std::string& path) noexcept
: mCsvSerializerImpl(std::move(csvSerializerImpl))
, mConfigPath(path)
{

}

GameSettingsData GameSettings::getGameSettingsData()
{
    if (!mIsSettingsStale)
    {
        return mCachedSettings;
    }

    mCachedSettings = loadSettings();
    mIsSettingsStale = false;

    return mCachedSettings;
}

GameSettingsData GameSettings::loadSettings() const
{
    return mCsvSerializerImpl->loadAsync(mConfigPath);
}

void GameSettings::updateSettings(const GameSettingsData& newSettings)
{
    mCsvSerializerImpl->updateAsync(newSettings, mConfigPath);
    mIsSettingsStale = true;
    mCallback();
}

void GameSettings::settingsUpdated(const std::function<void()>& callback)
{
    mCallback = callback;
}