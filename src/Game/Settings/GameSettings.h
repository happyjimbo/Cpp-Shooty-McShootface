#pragma once
#include <functional>

#include "CsvSerializerImpl.h"
#include "GameSettingsData.h"

class GameSettings final
{
public:
    explicit GameSettings(
        std::unique_ptr<CsvSerializerImpl<GameSettingsData>> csvSerializerImpl,
        const std::string& path,
        const std::function<void()>& callback
    ) noexcept;

    ~GameSettings() noexcept = default;

    GameSettingsData getGameSettingsData();
    void updateSettings(const GameSettingsData& newSettings);
private:
    GameSettingsData loadSettings() const;

    std::unique_ptr<CsvSerializerImpl<GameSettingsData>> mCsvSerializerImpl;
    std::string mConfigPath {};

    GameSettingsData mCachedSettings;
    bool mIsSettingsStale = true;
    std::function<void()> mCallback;
};
