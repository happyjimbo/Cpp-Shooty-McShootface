# BDD Testing configuration
message(STATUS "Configuring testing dependencies")

set(GTEST_INCLUDE_DIR "/opt/homebrew/include")
set(GTEST_LIBRARY "/opt/homebrew/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "/opt/homebrew/lib/libgtest_main.a")
set(GMOCK_LIBRARY "/opt/homebrew/lib/libgmock.a")
set(GMOCK_MAIN_LIBRARY "/opt/homebrew/lib/libgmock_main.a")

find_package(GTest REQUIRED)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(ASIO_INCLUDE_DIR /opt/homebrew/include)
set(TCLAP_INCLUDE_DIR /opt/homebrew/include)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/share/cmake/nlohmann_json")
set(nlohmann_json_DIR "/opt/homebrew/share/cmake/nlohmann_json")
find_package(nlohmann_json REQUIRED)