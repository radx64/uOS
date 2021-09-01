set(projectName "uOS")
set(kernel_name "kernel.elf")
set(linker_script "../src/link.ld")

cmake_minimum_required (VERSION 3.9)
project (${projectName} C CXX)
enable_language(ASM_NASM)

set(compile_flags "-O0 -m32 -nostdlib -nostdinc -ffreestanding -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compile_flags}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compile_flags} -std=gnu99")

add_subdirectory(src)

if(CMAKE_C_LINK_EXECUTABLE)
  set(CMAKE_C_LINK_EXECUTABLE
    "ld  <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
endif()

set(CMAKE_EXE_LINKER_FLAGS "-T ${linker_script} -melf_i386")
set(BUILD_SHARED_LIBS OFF)
add_executable(${kernel_name} dummy.c)

# There is a circular dependency in linking kernel and kernel_asm due isr handlers
# That's why in linking kernel lib is linked twice "kernel kernel_asm kernel"
# Need to separate that or link to one target later on
target_link_libraries(${kernel_name} loader_asm kernel kernel_asm kernel drivers drivers_asm apps stdlib)
