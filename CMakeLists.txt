cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Define the directory containing the media files
set(MEDIA_DIR "${CMAKE_SOURCE_DIR}/Media")

# Debug and Release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCE_FILES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h"
        "${CMAKE_SOURCE_DIR}/src/*.inl"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/state
        ${CMAKE_SOURCE_DIR}/src/Gui
        ${CMAKE_SOURCE_DIR}/src/Entity
        ${CMAKE_SOURCE_DIR}/src/Resource
        ${CMAKE_SOURCE_DIR}/src/Command
        ${CMAKE_SOURCE_DIR}/src/Controllers
        ${CMAKE_SOURCE_DIR}/src/System
        ${CMAKE_SOURCE_DIR}/src/ObjectPool
        ${CMAKE_SOURCE_DIR}/src/Data
)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Copy over all the media files
file(GLOB_RECURSE TEXTURE_FILES "${MEDIA_DIR}/Textures/*")
file(GLOB_RECURSE FONT_FILES "${MEDIA_DIR}/Font/*")

foreach(FILE ${TEXTURE_FILES} ${FONT_FILES} ${OTHER_FILES})
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

# Exclude CMakeLists.txt from being installed
install(DIRECTORY ${MEDIA_DIR}
        DESTINATION ${PROJECT_NAME}/Media
        PATTERN "CMakeLists.txt" EXCLUDE
)