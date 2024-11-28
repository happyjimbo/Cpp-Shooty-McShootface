#include <gtest/gtest.h>

#include "CircularBuffer.h"

TEST(CircularBufferTest, BufferWrapsCorrectly)
{
    CircularBuffer<float, 3> buffer;

    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer.data()[0], 1);
    EXPECT_EQ(buffer.data()[1], 2);
    EXPECT_EQ(buffer.data()[2], 3);

    buffer.push_back(4);

    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer.data()[0], 4);
    EXPECT_EQ(buffer.data()[1], 2);
    EXPECT_EQ(buffer.data()[2], 3);
}

TEST(CircularBufferTest, BufferMaxValue)
{
    CircularBuffer<float, 3> buffer;

    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    EXPECT_EQ(buffer.maxValue(), 3);

    buffer.push_back(54);
    buffer.push_back(4);
    buffer.push_back(5);

    EXPECT_EQ(buffer.maxValue(), 54);
}