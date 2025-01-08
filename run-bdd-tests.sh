#!/bin/bash

./cmake-build-debug/bin/BDD_Tests --verbose &
CUKE_PORT=3902 cucumber --require bdd/features --format progress bdd/features