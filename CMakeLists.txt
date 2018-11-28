set(projectName "uOS")
set(kernel_name "kernel.elf")
set(linker_script "../src/link.ld")

cmake_minimum_required (VERSION 3.9)
project (${projectName} C CXX)
enable_language(ASM_NASM)

set(compile_flags "-m32 -nostdlib -nostdinc -ffreestanding -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compile_flags}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compile_flags} -std=gnu99")

add_subdirectory(src)
set_target_properties(asm_src PROPERTIES LINK_FLAGS "-melf_i386")
set_target_properties(loader_asm PROPERTIES LINK_FLAGS "-melf_i386")
set_target_properties(src PROPERTIES COMPILE_FLAGS ${compile_flags})

if( CMAKE_C_LINK_EXECUTABLE)
  set(CMAKE_C_LINK_EXECUTABLE
    "ld  <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
endif()

set(CMAKE_EXE_LINKER_FLAGS "-T ${linker_script} -melf_i386")
SET(BUILD_SHARED_LIBS OFF)
add_executable(${kernel_name} dummy.c)
target_link_libraries(${kernel_name} loader_asm src asm_src)