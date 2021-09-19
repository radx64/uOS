set(compile_flags "-O0 -m32 -nostdlib -nostdinc -ffreestanding -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

add_subdirectory(apps)
add_subdirectory(drivers)
add_subdirectory(kernel)
add_subdirectory(stdlib)

add_library(loader_asm loader.asm)

set_target_properties(loader_asm PROPERTIES LINK_FLAGS "-melf_i386")

if(CMAKE_C_LINK_EXECUTABLE)
  set(CMAKE_C_LINK_EXECUTABLE
    "ld  <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
endif()

set(linker_script ${CMAKE_CURRENT_SOURCE_DIR}/"link.ld")

set(CMAKE_EXE_LINKER_FLAGS "-T ${linker_script} -melf_i386")
set(BUILD_SHARED_LIBS OFF)

add_executable(${kernel_name} dummy.c)
set_target_properties(${kernel_name} PROPERTIES COMPILE_FLAGS ${compile_flags})

# There is a circular dependency in linking kernel and kernel_asm due isr handlers
# That's why in linking kernel lib is linked twice "kernel kernel_asm kernel"
# Need to separate that or link to one target later ons
target_link_libraries(${kernel_name} loader_asm kernel kernel_asm kernel drivers drivers_asm apps stdlib)


