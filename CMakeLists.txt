# Minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Define the project name and the languages used
project(main LANGUAGES CXX)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to build shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Option to enable Editor mode
option(ENABLE_EDITOR_MODE "Build with editor mode enabled" ON)

# Define the directory containing media files
set(MEDIA_DIR "${CMAKE_SOURCE_DIR}/Media")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test_src")

# Debug and Release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include(cmake/BDDTestingConfig.cmake)

# Detect platform
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include(cmake/PlatformMacOS.cmake)
elseif(WIN32)
    include(cmake/PlatformWindows.cmake)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()


set(SFML_STATIC_LIBRARIES OFF)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics audio)
find_package(GTest REQUIRED)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(Boost 1.86 REQUIRED COMPONENTS system)
find_package(nlohmann_json REQUIRED)
find_package(Boost 1.86 REQUIRED COMPONENTS system)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.86.0 REQUIRED COMPONENTS)

include(cmake/Dependencies.cmake)

# Collect all source files (you can modify the paths as needed)
file(GLOB_RECURSE GAME_FILES
        "${CMAKE_SOURCE_DIR}/src/main.cpp"
        "${CMAKE_SOURCE_DIR}/src/GameModeFactory.cpp"
        "${CMAKE_SOURCE_DIR}/src/IGameMode.cpp"
        "${CMAKE_SOURCE_DIR}/src/Profiler/*.h"
        "${CMAKE_SOURCE_DIR}/src/Game/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/Game/*.h"
        "${CMAKE_SOURCE_DIR}/src/Game/*.inl"
)

# call this before EditorMode
set(SOURCE_FILES ${GAME_FILES})

include(cmake/EditorMode.cmake)

# Define the main executable with the collected source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

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
)

# EDITOR_INCLUDE_DIRS is set in EditorMode.cmake
if(ENABLE_EDITOR_MODE)
    target_include_directories(${PROJECT_NAME} PRIVATE ${EDITOR_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-audio
    ImGui-SFML::ImGui-SFML
    rapidcsv
    Boost::headers
    Boost::system
    Tracy::TracyClient
)

# Enable C++20 features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Set compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()


# Media Copy
include(cmake/MediaCopy.cmake)

# Unit Tests
include(cmake/UnitTests.cmake)

add_subdirectory(bdd)