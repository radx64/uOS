#!/bin/bash

set -e
echo -e "\033[32;1;1mBuilding µOS...\033[0m"
mkdir -p build
cd build
cmake .. && make kernel.elf
cd -
if [ -f os.iso ]
then
    rm os.iso -rf
fi
make -s os.iso
echo -e "\033[32;1;1mDone :) Now try to boot from \033[31;1;1mos.iso\033[32;1;1m file\033[0m"