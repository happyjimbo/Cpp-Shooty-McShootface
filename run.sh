#!/bin/bash
# run.sh

rm -rf build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Paths for the runtime (build) and source versions of settings.csv
RUNTIME_CONFIG_PATH="./cmake-build-debug/bin/Media/Data/settings.csv"
SOURCE_CONFIG_PATH="./Media/Data/settings.csv"

# ensure that the latest csv is copied over before running
cp "$SOURCE_CONFIG_PATH" "RUNTIME_CONFIG_PATH"

# Run the built executable with the runtime settings.csv path
./cmake-build-debug/bin/main "$RUNTIME_CONFIG_PATH"

# After execution, copy the modified settings.csv back to the source folder if changes were made
if cmp -s "$RUNTIME_CONFIG_PATH" "$SOURCE_CONFIG_PATH"; then
    echo "No changes detected in settings.csv."
else
    echo "Changes detected in settings.csv. Copying back to source..."
    cp "$RUNTIME_CONFIG_PATH" "$SOURCE_CONFIG_PATH"
    echo "settings.csv copied back to source."
fi