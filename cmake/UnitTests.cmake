# Unit Tests Target Configuration
message(STATUS "Configuring Unit Tests")

# Add the test executable
add_executable(UnitTests_tests
        ${TEST_DIR}/test_ProjectileFiringData.cpp
        ${TEST_DIR}/test_CircularBuffer.cpp
        ${TEST_DIR}/test_CsvSerializer.cpp
        ${TEST_DIR}/MockCsvSerializer.h
        ${TEST_DIR}/test_GameSettings.cpp
)

# Include additional source files required by tests
target_sources(UnitTests_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Game/Settings/GameSettings.cpp
)

# Include directories for the test target
target_include_directories(UnitTests_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Game
        ${CMAKE_SOURCE_DIR}/src/Game/state
        ${CMAKE_SOURCE_DIR}/src/Game/Gui
        ${CMAKE_SOURCE_DIR}/src/Game/Entity
        ${CMAKE_SOURCE_DIR}/src/Game/Resource
        ${CMAKE_SOURCE_DIR}/src/Game/Command
        ${CMAKE_SOURCE_DIR}/src/Game/Initializers
        ${CMAKE_SOURCE_DIR}/src/Game/System
        ${CMAKE_SOURCE_DIR}/src/Game/ObjectPool
        ${CMAKE_SOURCE_DIR}/src/Game/Data
        ${CMAKE_SOURCE_DIR}/src/Game/Util/Math
        ${CMAKE_SOURCE_DIR}/src/Game/Util/OS
        ${CMAKE_SOURCE_DIR}/src/Game/Util/DataStruct
        ${CMAKE_SOURCE_DIR}/src/Game/Audio
        ${CMAKE_SOURCE_DIR}/src/Game/Settings
        ${CMAKE_SOURCE_DIR}/src/Profiler
        ${Boost_INCLUDE_DIRS}
)

# Link GoogleTest, Boost, SFML, and Tracy to the test executable
target_link_libraries(UnitTests_tests PRIVATE
        ${GTEST_LIBRARY}
        ${GTEST_MAIN_LIBRARY}
        ${GMOCK_LIBRARY}
        ${GMOCK_MAIN_LIBRARY}
        GTest::gtest_main
        GTest::gmock_main
        sfml-graphics
        rapidcsv
        Boost::headers
        Boost::system
        Tracy::TracyClient
)

target_include_directories(UnitTests_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/Editor)

# Enable C++20 features for tests
target_compile_features(UnitTests_tests PRIVATE cxx_std_20)

# Set compiler warnings for the tests
if(MSVC)
    target_compile_options(UnitTests_tests PRIVATE /W4 /WX)
else()
    target_compile_options(UnitTests_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Copy the test CSV file to the output directory
add_custom_command(
        TARGET UnitTests_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TEST_DIR}/test.csv
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/test_src/test.csv
)

# Enable testing and discover tests
enable_testing()
include(GoogleTest)
gtest_discover_tests(UnitTests_tests)