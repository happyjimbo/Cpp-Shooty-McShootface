#include <gtest/gtest.h>
#include "CsvSerializer.h"
#include "GameSettingsData.h"

class CsvSerializerTest : public ::testing::Test
{
protected:
    std::unique_ptr<CsvSerializer<GameSettingsData>> csvSerializer = std::make_unique<CsvSerializer<GameSettingsData>>();
    GameSettingsData data;

    void SetUp() override
    {
        data = csvSerializer->load("./test_src/test.csv");
    }
};

TEST_F(CsvSerializerTest, EnsureCsvIsLoadedAndNotDefault)
{
    EXPECT_NE(data.title, "title");
    EXPECT_NE(data.width, 640);
    EXPECT_NE(data.height, 480);
    EXPECT_NE(data.fps, 30.f);
    EXPECT_NE(data.mute, false);
}

TEST_F(CsvSerializerTest, EnsureCsvIsLoadedAndUsingTestValues)
{
    EXPECT_EQ(data.title, "test");
    EXPECT_EQ(data.width, 1024);
    EXPECT_EQ(data.height, 768);
    EXPECT_EQ(data.fps, 60.f);
    EXPECT_EQ(data.mute, true);
}

TEST_F(CsvSerializerTest, EnsureCsvIsLoadedAsyncAndNotDefault)
{
    EXPECT_NE(data.title, "title");
    EXPECT_NE(data.width, 640);
    EXPECT_NE(data.height, 480);
    EXPECT_NE(data.fps, 30.f);
    EXPECT_NE(data.mute, false);
}

TEST_F(CsvSerializerTest, EnsureCsvIsLoadedAsyncAndUsingTestValues)
{
    EXPECT_EQ(data.title, "test");
    EXPECT_EQ(data.width, 1024);
    EXPECT_EQ(data.height, 768);
    EXPECT_EQ(data.fps, 60.f);
    EXPECT_EQ(data.mute, true);
}