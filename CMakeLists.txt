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

# Pass the define to the compiler
if(ENABLE_EDITOR_MODE)
    message(STATUS "Building with EDITOR_MODE enabled")
    add_compile_definitions(EDITOR_MODE)
else()
    message(STATUS "Building without EDITOR_MODE")
endif()

# Define the directory containing media files
set(MEDIA_DIR "${CMAKE_SOURCE_DIR}/Media")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test_src")

# Debug and Release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include FetchContent module for fetching external projects
include(FetchContent)

# Fetch SFML
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Fetch GoogleTest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# If Boost is not found automatically, manually set paths
if(NOT Boost_FOUND)
    set(Boost_INCLUDE_DIR /opt/homebrew/include)
    set(Boost_LIBRARY_DIR /opt/homebrew/lib)
    set(Boost_SYSTEM_LIBRARY /opt/homebrew/lib/libboost_system.a)
    find_package(Boost 1.86 REQUIRED COMPONENTS system)
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.86.0 REQUIRED COMPONENTS)

# Detect platform
if(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    message(STATUS "Configuring for iOS")
    set(CMAKE_OSX_SYSROOT iphoneos)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.0)
    set(CMAKE_OSX_ARCHITECTURES arm64)

    # Add any iOS-specific settings here

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Configuring for macOS")

    FetchContent_Declare(
            imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui
            GIT_TAG v1.91.0-docking
    )

    FetchContent_MakeAvailable(imgui)

    FetchContent_Declare(
            rapidcsv
            GIT_REPOSITORY "https://github.com/d99kris/rapidcsv.git"
            GIT_TAG        "v8.50"
    )
    FetchContent_MakeAvailable(rapidcsv)



    # Manually add ImGui source files (since ImGui doesn't define its own CMake target)
    set(IMGUI_SOURCES
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    )

    add_library(imgui STATIC ${IMGUI_SOURCES})


    # Include ImGui directories
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})


    FetchContent_Declare(
            imgui-sfml
            GIT_REPOSITORY https://github.com/SFML/imgui-sfml
            GIT_TAG v2.6
    )
    add_subdirectory(imgui-sfml)

    set_target_properties(imgui ImGui-SFML PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)

endif()


add_subdirectory(tracy)

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

# Conditionally collect editor files
if(ENABLE_EDITOR_MODE)
    add_definitions(-DENABLE_EDITOR_MODE)
    file(GLOB_RECURSE EDITOR_FILES
            "${CMAKE_SOURCE_DIR}/src/Editor/*.cpp"
            "${CMAKE_SOURCE_DIR}/src/Editor/*.h"
            "${CMAKE_SOURCE_DIR}/src/Editor/*.inl"
    )
    set(SOURCE_FILES ${GAME_FILES} ${EDITOR_FILES})
else()
    set(SOURCE_FILES ${GAME_FILES})
endif()

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

# Add editor-specific include directories if ENABLE_EDITOR_MODE is defined
if(ENABLE_EDITOR_MODE)
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/src/Editor
    )
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio)
    target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
    target_link_libraries(${PROJECT_NAME} PRIVATE rapidcsv)
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::headers)
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)
    target_link_libraries(${PROJECT_NAME} PUBLIC Tracy::TracyClient)

    #target_compile_definitions(${PROJECT_NAME} PRIVATE TRACY_ENABLE TRACY_CALLSTACK=20)

endif ()

# Enable C++20 features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Set compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Copy media files after the build
file(GLOB_RECURSE TEXTURE_FILES "${MEDIA_DIR}/Textures/*")
file(GLOB_RECURSE FONT_FILES "${MEDIA_DIR}/Font/*")
file(GLOB_RECURSE SOUND_FILES "${MEDIA_DIR}/Sounds/*")
file(GLOB_RECURSE SHADER_FILES "${MEDIA_DIR}/Shaders/*")
file(GLOB_RECURSE DATA_FILES "${MEDIA_DIR}/Data/*")

foreach(FILE ${TEXTURE_FILES} ${FONT_FILES} ${SOUND_FILES} ${DATA_FILES} ${SHADER_FILES} ${OTHER_FILES})
    get_filename_component(FILE_NAME ${FILE} NAME)
    get_filename_component(DIR_NAME ${FILE} DIRECTORY)
    string(REPLACE ${MEDIA_DIR} "" REL_DIR ${DIR_NAME})

    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${FILE}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Media/${REL_DIR}/${FILE_NAME}
    )
endforeach()

# Post-execution: Copy modified settings.csv back to the source location
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Media/Data/settings.csv
        ${MEDIA_DIR}/Data/settings.csv
)

# Install media files but exclude CMakeLists.txt
install(DIRECTORY ${MEDIA_DIR}
        DESTINATION ${PROJECT_NAME}/Media
        PATTERN "CMakeLists.txt" EXCLUDE
)

# -----------------------------
# Unit Tests Target
# -----------------------------

# Add the test executable
add_executable(UnitTests_tests
        test_src/test_ProjectileFiringData.cpp
        test_src/test_CircularBuffer.cpp
        test_src/test_CsvSerializer.cpp
        test_src/MockCsvSerializer.h
        test_src/test_GameSettings.cpp
)

target_sources(UnitTests_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Game/Settings/GameSettings.cpp
)

# Include directories for the test target as well
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

target_include_directories(UnitTests_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/Editor)

# Link GoogleTest and SFML to the test executable
target_link_libraries(UnitTests_tests PRIVATE GTest::gtest_main GTest::gmock_main sfml-graphics)
target_link_libraries(UnitTests_tests PRIVATE rapidcsv)
target_link_libraries(UnitTests_tests PRIVATE Boost::headers)
target_link_libraries(UnitTests_tests PRIVATE Boost::system)
target_link_libraries(UnitTests_tests PUBLIC Tracy::TracyClient)

# copy test csv over to test
add_custom_command(
        TARGET UnitTests_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TEST_DIR}/test.csv
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/test_src/test.csv
)


# Enable C++20 features for the tests as well
target_compile_features(UnitTests_tests PRIVATE cxx_std_20)

# Compiler warnings for the tests
if(MSVC)
    target_compile_options(UnitTests_tests PRIVATE /W4 /WX)
else()
    target_compile_options(UnitTests_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Enable testing and discover tests
enable_testing()
include(GoogleTest)
gtest_discover_tests(UnitTests_tests)