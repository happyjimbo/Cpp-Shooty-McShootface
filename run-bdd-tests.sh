#!/bin/bash

./cmake-build-debug/bin/BDD_Tests --verbose &

sleep 1

CUKE_PORT=3902 cucumber --require bdd/features --format progress bdd/features