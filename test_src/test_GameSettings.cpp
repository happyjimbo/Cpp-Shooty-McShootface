#include <gmock/gmock.h>

#include "GameSettings.h"
#include "GameSettingsData.h"
#include "MockCsvSerializer.h"

using ::testing::Return;

class GameSettingsTest : public ::testing:: Test
{
protected:
    std::unique_ptr<MockCsvSerializer> mock;
    std::string configPath = "path/to/config.csv";
    GameSettingsData testSettings {"hello world", 100, 200, 10, true};

    void SetUp() override
    {
        mock = std::make_unique<MockCsvSerializer>();
    }
};

TEST_F(GameSettingsTest, GetGameSettingsUsesLoadAsync)
{
    EXPECT_CALL(*mock, loadAsync(configPath)).WillOnce(Return(testSettings));

    GameSettings gameSettings { std::move(mock), configPath, nullptr };
    GameSettingsData gameSettingsData = gameSettings.getGameSettingsData();

    EXPECT_EQ(gameSettingsData, testSettings);
}

TEST_F(GameSettingsTest, UpdateSettingsUsesUpdateAsync)
{
    EXPECT_CALL(*mock, loadAsync(configPath)).WillOnce(Return(testSettings));
    EXPECT_CALL(*mock, updateAsync(testSettings, configPath)).Times(1);

    GameSettings gameSettings {std::move(mock), configPath, nullptr};

    EXPECT_NO_THROW(gameSettings.updateSettings(testSettings));
    EXPECT_EQ(gameSettings.getGameSettingsData(), testSettings);
}

TEST_F(GameSettingsTest, UpdateSettingsChangesSettings)
{
    GameSettingsData initialSettings {"Initial Title", 800, 600, 60, false};
    GameSettingsData updatedSettings {"Updated Title", 1920, 1080, 144, true};

    EXPECT_CALL(*mock, loadAsync(configPath))
        .WillOnce(Return(initialSettings))
        .WillOnce(Return(updatedSettings));

    EXPECT_CALL(*mock, updateAsync(updatedSettings, configPath)).Times(1);

    GameSettings gameSettings {std::move(mock), configPath, nullptr};

    auto settings1 = gameSettings.getGameSettingsData();
    gameSettings.updateSettings(updatedSettings);
    auto settings2 = gameSettings.getGameSettingsData();

    EXPECT_EQ(settings1, initialSettings);
    EXPECT_EQ(settings2, updatedSettings);;
}

TEST_F(GameSettingsTest, UpdateSettingsCallback)
{
    EXPECT_CALL(*mock, loadAsync(configPath)).WillRepeatedly(Return(testSettings));
    EXPECT_CALL(*mock, updateAsync(testSettings, configPath)).Times(1);

    bool callback = false;

    GameSettings gameSettings {std::move(mock), configPath, [&]
    {
        callback = true;
    }};

    EXPECT_FALSE(callback);
    gameSettings.updateSettings(testSettings);
    EXPECT_TRUE(callback);
}