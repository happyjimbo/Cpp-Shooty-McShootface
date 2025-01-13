#include <cucumber-cpp/generic.hpp>
#include <gtest/gtest.h>
#include <iostream>

namespace
{
    int playerPosition = 0;

    GIVEN("^the player starts at position (\\d+)$") {
        REGEX_PARAM(int, startPosition);
        std::cout << "GIVEN step invoked with: " << startPosition << std::endl;
        playerPosition = startPosition;
    }

    WHEN("^the player moves forward by (\\d+) units$") {
        REGEX_PARAM(int, units);
        playerPosition += units;
    }

    THEN("^the player's position should be (\\d+)$") {
        REGEX_PARAM(int, expectedPosition);
        EXPECT_EQ(playerPosition, expectedPosition);
    }
}