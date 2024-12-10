#include <gtest/gtest.h>
#include "CsvSerializer.h"
#include "GameSettingsData.h"

TEST(CsvSerializerTest, EnsureCsvIsLoadedAndNotDefault)
{
    auto data = CsvSerializer::load<GameSettingsData>("./test_src/test.csv");

    EXPECT_NE(data.title, "title");
    EXPECT_NE(data.width, 640);
    EXPECT_NE(data.height, 480);
    EXPECT_NE(data.fps, 30.f);
    EXPECT_NE(data.mute, false);
}

TEST(CsvSerializerTest, EnsureCsvIsLoadedAndUsingTestValues)
{
    auto data = CsvSerializer::load<GameSettingsData>("./test_src/test.csv");

    EXPECT_EQ(data.title, "test");
    EXPECT_EQ(data.width, 1024);
    EXPECT_EQ(data.height, 768);
    EXPECT_EQ(data.fps, 60.f);
    EXPECT_EQ(data.mute, true);
}

TEST(CsvSerializerTest, EnsureCsvIsLoadedAsyncAndNotDefault)
{
    auto data = CsvSerializer::loadAsync<GameSettingsData>("./test_src/test.csv");

    EXPECT_NE(data.title, "title");
    EXPECT_NE(data.width, 640);
    EXPECT_NE(data.height, 480);
    EXPECT_NE(data.fps, 30.f);
    EXPECT_NE(data.mute, false);
}

TEST(CsvSerializerTest, EnsureCsvIsLoadedAsyncAndUsingTestValues)
{
    auto data = CsvSerializer::loadAsync<GameSettingsData>("./test_src/test.csv");

    EXPECT_EQ(data.title, "test");
    EXPECT_EQ(data.width, 1024);
    EXPECT_EQ(data.height, 768);
    EXPECT_EQ(data.fps, 60.f);
    EXPECT_EQ(data.mute, true);
}