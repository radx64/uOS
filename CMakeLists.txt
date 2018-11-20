set(projectName "uOS")
set(kernel_name "kernel.elf")
set(linker_script "../src/link.ld")
#set(CMAKE_CXX_LINK_EXECUTABLE "ld")
#set(CMAKE_C_LINK_EXECUTABLE "ld")

cmake_minimum_required (VERSION 3.12)
project (${projectName} C CXX)
enable_language(ASM_NASM)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(warnings "-Wall -Wextra -Werror")
endif()

set(compile_flags "-m32 -nostdlib -nostdinc -ffreestanding -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compile_flags}")

add_subdirectory(src)
set_target_properties(asm_src PROPERTIES LINK_FLAGS "-melf_i386")
set_target_properties(loader_asm PROPERTIES LINK_FLAGS "-melf_i386")
set_target_properties(src PROPERTIES COMPILE_FLAGS ${compile_flags})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -T ${linker_script}")
#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(BUILD_SHARED_LIBS OFF)
add_executable(${kernel_name} dummy.cpp src/loader.asm)
target_link_libraries(${kernel_name} loader_asm src asm_src)
#target_link_libraries(${kernel_name} loader_asm)