#pragma once
#include <functional>

#include "CsvSerializer.h"
#include "GameSettingsData.h"

class GameSettings final
{
public:
    explicit GameSettings(
        std::unique_ptr<CsvSerializer<GameSettingsData>> csvSerializerImpl,
        const std::string& path,
        const std::function<void()>& callback
    ) noexcept;

    ~GameSettings() noexcept = default;

    GameSettingsData getGameSettingsData();
    void updateSettings(const GameSettingsData& newSettings);
private:
    GameSettingsData loadSettings() const;

    std::unique_ptr<CsvSerializer<GameSettingsData>> mCsvSerializerImpl;
    std::string mConfigPath {};

    GameSettingsData mCachedSettings;
    bool mIsSettingsStale = true;
    std::function<void()> mCallback;
};
