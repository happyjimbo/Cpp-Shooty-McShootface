# Pass the define to the compiler
if(ENABLE_EDITOR_MODE)
    message(STATUS "Building with EDITOR_MODE enabled")
    add_compile_definitions(EDITOR_MODE)
else()
    message(STATUS "Building without EDITOR_MODE")
endif()

# Conditionally collect editor files
if(ENABLE_EDITOR_MODE)
    add_definitions(-DENABLE_EDITOR_MODE)
    file(GLOB_RECURSE EDITOR_FILES
            "${CMAKE_SOURCE_DIR}/src/Editor/*.cpp"
            "${CMAKE_SOURCE_DIR}/src/Editor/*.h"
            "${CMAKE_SOURCE_DIR}/src/Editor/*.inl"
    )
    set(SOURCE_FILES ${GAME_FILES} ${EDITOR_FILES})

    # Store include directories for later
    set(EDITOR_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/src/Editor")
endif()