cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Define the directory containing the media files
set(MEDIA_DIR "${CMAKE_SOURCE_DIR}/Media")

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/Game.cpp
        src/Game.h
        src/World.cpp
        src/World.h
        src/Resource/ResourceHolder.inl
        src/Resource/ResourceHolder.h
        src/Resource/ResourceIdentifiers.h
        src/Entity/SpriteEntity.cpp
        src/Entity/SpriteEntity.h
        src/Entity/AircraftEntity.cpp
        src/Entity/AircraftEntity.h
        src/Command/Command.h
        src/Category.h
        src/Command/CommandQueue.cpp
        src/Command/CommandQueue.h
        src/Controls.cpp
        src/Controls.h
        src/Entity/ProjectileEntity.cpp
        src/Entity/ProjectileEntity.h
        src/Controllers/ProjectileController.cpp
        src/Controllers/ProjectileController.h
        src/Controllers/EnemyAircraftController.cpp
        src/Controllers/EnemyAircraftController.h
        src/Controllers/ProjectileCollisionController.cpp
        src/Controllers/ProjectileCollisionController.h
        src/Gui/Label.cpp
        src/Gui/Label.h
        src/Entity/EntitySystem.h
        src/Entity/EntityObject.cpp
        src/Entity/EntityObject.h
        src/Entity/EntitySystem.inl
        src/Controllers/BackgroundController.cpp
        src/Controllers/BackgroundController.h
        src/Controllers/ScoreController.cpp
        src/Controllers/ScoreController.h
        src/Controllers/PlayerAircraftController.cpp
        src/Controllers/PlayerAircraftController.h
)

# Add the parent directory of src and Gui to the include path for the target
target_include_directories(main PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/Gui
        ${CMAKE_SOURCE_DIR}/src/Entity
        ${CMAKE_SOURCE_DIR}/src/Resource
        ${CMAKE_SOURCE_DIR}/src/Command
        ${CMAKE_SOURCE_DIR}/src/Controllers
)

target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

# Get a list of all texture files in the media directory
file(GLOB_RECURSE TEXTURE_FILES
        "${MEDIA_DIR}/*.png"
        "${MEDIA_DIR}/*.jpg"
        "${MEDIA_DIR}/*.jpeg"
        "${MEDIA_DIR}/*.bmp"
        "${MEDIA_DIR}/*.tga"
        "${MEDIA_DIR}/*.dds"
)

# Copy texture files to the build output directory
foreach(TEXTURE_FILE ${TEXTURE_FILES})
    get_filename_component(FILE_NAME ${TEXTURE_FILE} NAME)
    add_custom_command(
            TARGET main
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TEXTURE_FILE}
            $<TARGET_FILE_DIR:main>/Media/Textures/${FILE_NAME}
    )
endforeach()

# Exclude CMakeLists.txt from being installed
install(DIRECTORY ${MEDIA_DIR}
        DESTINATION ${PROJECT_NAME}/Media
        PATTERN "CMakeLists.txt" EXCLUDE
)
