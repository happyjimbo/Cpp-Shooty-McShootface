
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