#!/bin/bash

rm -rf cmake-build-debug
mkdir -p cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --cmake-build-debug .