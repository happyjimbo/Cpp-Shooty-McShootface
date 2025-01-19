# macOS-specific configuration
message(STATUS "Configuring for macOS")

set(ASIO_INCLUDE_DIR "/opt/homebrew/include")
set(TCLAP_INCLUDE_DIR "/opt/homebrew/include")

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/sfml@2/2.6.2")
set(SFML_DIR "/opt/homebrew/Cellar/sfml@2/2.6.2/lib/cmake/SFML")

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/share/cmake/nlohmann_json")
set(nlohmann_json_DIR "/opt/homebrew/share/cmake/nlohmann_json")

if(NOT Boost_FOUND)
    set(Boost_INCLUDE_DIR /opt/homebrew/include)
    set(Boost_LIBRARY_DIR /opt/homebrew/lib)
    set(Boost_SYSTEM_LIBRARY /opt/homebrew/lib/libboost_system.a)
endif()