# Minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Define the project name for BDD tests
project(BDD_Tests LANGUAGES CXX)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GTEST_INCLUDE_DIR "/opt/homebrew/include")
set(GTEST_LIBRARY "/opt/homebrew/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "/opt/homebrew/lib/libgtest_main.a")
set(GMOCK_LIBRARY "/opt/homebrew/lib/libgmock.a")
set(GMOCK_MAIN_LIBRARY "/opt/homebrew/lib/libgmock_main.a")
set(CUKE_ENABLE_GTEST ON CACHE BOOL "Enable GTest for cucumber-cpp")


# Include dependencies from the root project
include(FetchContent)

# Ensure SFML is already available from the root
if(NOT TARGET sfml-graphics)
    message(FATAL_ERROR "SFML must be provided by the root CMakeLists.txt.")
endif()

# Use the nlohmann_json target from the root
if (NOT TARGET nlohmann_json::nlohmann_json)
    message(FATAL_ERROR "nlohmann_json::nlohmann_json must be provided by the root CMakeLists.txt.")
endif()

# Add Cucumber-Cpp as a subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/cucumber-cpp ${CMAKE_BINARY_DIR}/cucumber-cpp-build)
#link_directories(/opt/homebrew/opt/cucumber-cpp/lib)

# Collect step definition sources
file(GLOB_RECURSE STEP_DEFINITION_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/features/step_definitions/*.cpp)

# Log the collected files
message(STATUS "Collected Step Definition Sources:")
foreach(file ${STEP_DEFINITION_SOURCES})
    message(STATUS "  ${file}")
endforeach()

# Collect game source files from the root project
file(GLOB_RECURSE GAME_SOURCES
        ${CMAKE_SOURCE_DIR}/../src/Game/*.cpp
        ${CMAKE_SOURCE_DIR}/../src/Profiler/*.cpp
)

# Add the executable for the BDD tests
add_executable(${PROJECT_NAME} ${STEP_DEFINITION_SOURCES} ${GAME_SOURCES})

# Include directories for the BDD project
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/../src
        ${nlohmann_json_SOURCE_DIR}/include
)

# Link libraries required for tests
target_link_libraries(${PROJECT_NAME} PRIVATE
        cucumber-cpp
        sfml-graphics
        sfml-audio
        Boost::headers
        Boost::system
        nlohmann_json::nlohmann_json
        GTest::GTest
        GTest::Main
)

# Enable testing
enable_testing()
add_test(NAME BDD_Tests COMMAND ${PROJECT_NAME})