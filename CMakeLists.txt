set(projectName "uOS")
set(kernel_name "kernel.elf")
set(linker_script "../src/link.ld")
set(CMAKE_CXX_LINK_EXECUTABLE "ld")
set(CMAKE_C_LINK_EXECUTABLE "ld")

cmake_minimum_required (VERSION 3.12)
project (${projectName} C CXX)
enable_language(ASM_NASM)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(warnings "-Wall -Wextra -Werror")
endif()

#add_definitions(-m32 -O3 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror)

add_definitions(-m32 -O3 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror)

add_subdirectory(src)

add_executable(${kernel_name} dummy.cpp)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${linker_script}")
set_target_properties(${kernel_name} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-melf_i386")
target_link_libraries(${kernel_name} src)
