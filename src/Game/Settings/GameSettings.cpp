#include "GameSettings.h"
#include "GameSettingsData.h"
#include "rapidcsv.h"
#include <string>

GameSettings::GameSettings(
    std::unique_ptr<CsvSerializerImpl<GameSettingsData>> csvSerializerImpl,
    const std::string& path,
    const std::function<void()>& callback
) noexcept
: mCsvSerializerImpl(std::move(csvSerializerImpl))
, mConfigPath(path)
, mCallback(callback)
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
    if (mCallback)
    {
        mCallback();
    }
}