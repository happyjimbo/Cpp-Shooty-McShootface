#!/bin/bash

rm -rf cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B cmake-build-debug
cmake --build cmake-build-debug --target BDD_Tests

./cmake-build-debug/bin/BDD_Tests --verbose &

sleep 1

CUKE_PORT=3902 cucumber --require bdd/features --format progress bdd/features