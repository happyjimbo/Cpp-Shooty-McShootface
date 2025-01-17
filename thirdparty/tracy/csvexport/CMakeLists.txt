cmake_minimum_required(VERSION 3.16)

option(NO_ISA_EXTENSIONS "Disable ISA extensions (don't pass -march=native or -mcpu=native to the compiler)" OFF)
option(NO_PARALLEL_STL "Disable parallel STL" OFF)

set(NO_STATISTICS OFF)

include(../cmake/version.cmake)

set(CMAKE_CXX_STANDARD 20)

project(
    tracy-csvexport
    LANGUAGES C CXX
    VERSION ${TRACY_VERSION_STRING}
)

include(../cmake/config.cmake)
include(../cmake/vendor.cmake)
include(../cmake/server.cmake)

set(PROGRAM_FILES
        src/csvexport.cpp
)

add_executable(${PROJECT_NAME} ${PROGRAM_FILES} ${COMMON_FILES} ${SERVER_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE TracyServer TracyGetOpt)
set_property(DIRECTORY . PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
