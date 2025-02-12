# Windows-specific configuration
message(STATUS "Configuring for Windows")

set(ASIO_INCLUDE_DIR "C:/path/to/asio")
set(TCLAP_INCLUDE_DIR "C:/path/to/tclap")

# Paths for dependencies
list(APPEND CMAKE_PREFIX_PATH "C:/path/to/sfml@2/2.6.2")
set(SFML_DIR "C:/path/to/sfml/sfml@2/2.6.2/lib/cmake/SFML")

list(APPEND CMAKE_PREFIX_PATH "C:/path/to/nlohmann_json")
set(nlohmann_json_DIR "C:/path/to/nlohmann_json")

if(NOT Boost_FOUND)
    set(Boost_INCLUDE_DIR "C:/path/to/boost/include")
    set(Boost_LIBRARY_DIR "C:/path/to/boost/lib")
    set(Boost_SYSTEM_LIBRARY "C:/path/to/boost/lib/opt/homebrew/lib/libboost_system.a")
endif()