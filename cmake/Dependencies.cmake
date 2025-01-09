# Include FetchContent module for fetching external projects
include(FetchContent)

#imgui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.91.0-docking
)

FetchContent_MakeAvailable(imgui)

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

#imgui-sfml
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG v2.6
)
add_subdirectory(imgui-sfml)

set_target_properties(imgui ImGui-SFML PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)

#rapidcsv
FetchContent_Declare(
        rapidcsv
        GIT_REPOSITORY "https://github.com/d99kris/rapidcsv.git"
        GIT_TAG        "v8.50"
)
FetchContent_MakeAvailable(rapidcsv)

# Add Tracy profiler
add_subdirectory(tracy)