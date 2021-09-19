#!/bin/bash

set -e
echo -e "\033[32;1;1mBuilding µOS tests target...\033[0m"
mkdir -p build
cd build
cmake .. && make tests
echo -e "\033[32;1;1mDone! Starting ctest now!\033[0m"
ctest
cd -