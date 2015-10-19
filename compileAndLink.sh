#!/bin/bash
mkdir -p build
nasm -f elf32 loader.s -o build/loader.o
ld -T link.ld -melf_i386 build/loader.o -o build/kernel.elf