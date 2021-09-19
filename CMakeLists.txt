set(projectName "uOS")
set(kernel_name "kernel.elf")

cmake_minimum_required (VERSION 3.9)
project (${projectName} C CXX)
enable_language(ASM_NASM)

add_subdirectory(src)
enable_testing()
add_subdirectory(test)