cmake_minimum_required(VERSION 3.16)

option(NO_ISA_EXTENSIONS "Disable ISA extensions (don't pass -march=native or -mcpu=native to the compiler)" OFF)
option(NO_STATISTICS "Disable calculation of statistics" ON)
option(NO_PARALLEL_STL "Disable parallel STL" OFF)

include(../cmake/version.cmake)

set(CMAKE_CXX_STANDARD 20)

project(
    tracy-import
    LANGUAGES C CXX
    VERSION ${TRACY_VERSION_STRING}
)

include(../cmake/config.cmake)
include(../cmake/vendor.cmake)
include(../cmake/server.cmake)

add_executable(tracy-import-chrome
        src/import-chrome.cpp
)
target_link_libraries(tracy-import-chrome PRIVATE TracyServer)

add_executable(tracy-import-fuchsia
        src/import-fuchsia.cpp
)
target_link_libraries(tracy-import-fuchsia PRIVATE TracyServer)

set_property(DIRECTORY . PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
