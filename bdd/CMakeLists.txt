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

set(MEDIA_DIR "${CMAKE_SOURCE_DIR}/Media")


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
file(GLOB_RECURSE STEP_DEFINITION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/features/step_definitions/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/features/step_definitions/util/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/features/step_definitions/util/*.h)
#file(GLOB_RECURSE TEMP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
#list(APPEND STEP_DEFINITION_SOURCES ${TEMP_SOURCES})
#file(GLOB_RECURSE TEMP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#list(APPEND STEP_DEFINITION_SOURCES ${TEMP_HEADERS})

# Log the collected files
message(STATUS "Collected Step Definition Sources:")
foreach(file ${STEP_DEFINITION_SOURCES})
    message(STATUS "  ${file}")
endforeach()

# Collect game source files from the root project
file(GLOB_RECURSE GAME_FILES
#        "${CMAKE_SOURCE_DIR}/src/main.cpp"
        "${CMAKE_SOURCE_DIR}/src/GameModeFactory.cpp"
        "${CMAKE_SOURCE_DIR}/src/IGameMode.cpp"
        "${CMAKE_SOURCE_DIR}/src/Profiler/*.h"
        "${CMAKE_SOURCE_DIR}/src/Game/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/Game/*.h"
        "${CMAKE_SOURCE_DIR}/src/Game/*.inl"
        "${CMAKE_SOURCE_DIR}/src/Profiler/*.cpp"
#        "${CMAKE_SOURCE_DIR}/bdd/*.cpp"
#        "${CMAKE_SOURCE_DIR}/bdd/*.h"
)
# call this before EditorMode
set(SOURCE_FILES ${GAME_FILES}
        features/step_definitions/move_player.cpp)

include(../cmake/EditorMode.cmake)

# Add the executable for the BDD tests
add_executable(${PROJECT_NAME} ${STEP_DEFINITION_SOURCES} ${SOURCE_FILES})


# Include directories for the project
target_include_directories(${PROJECT_NAME} PRIVATE
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
        ${CMAKE_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS}
        ${nlohmann_json_SOURCE_DIR}/include
#        ${CMAKE_SOURCE_DIR}/bdd
)

if(ENABLE_EDITOR_MODE)
    target_include_directories(${PROJECT_NAME} PRIVATE ${EDITOR_INCLUDE_DIRS})
endif()

# Link libraries required for tests
target_link_libraries(${PROJECT_NAME} PRIVATE
        cucumber-cpp
        sfml-graphics
        sfml-audio
        ImGui-SFML::ImGui-SFML
        rapidcsv
        Boost::headers
        Boost::system
        Tracy::TracyClient
        nlohmann_json::nlohmann_json
        GTest::GTest
        GTest::Main
)

include(../cmake/MediaCopy.cmake)

# Enable C++20 features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Set compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()


# Enable testing
enable_testing()
add_test(NAME BDD_Tests COMMAND ${PROJECT_NAME})