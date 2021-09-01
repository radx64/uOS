add_library(kernel STATIC)

target_sources(kernel
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gdt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/idt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/isr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/kmain.c
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/gdt.h
    ${CMAKE_CURRENT_SOURCE_DIR}/idt.h
    ${CMAKE_CURRENT_SOURCE_DIR}/isr.h 
)

target_include_directories(kernel
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../stdlib
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(kernel PROPERTIES COMPILE_FLAGS ${compile_flags})

add_library(kernel_asm STATIC)
target_sources(kernel_asm
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/interrupt.asm
    ${CMAKE_CURRENT_SOURCE_DIR}/kernel.asm
)

set_target_properties(kernel_asm PROPERTIES LINK_FLAGS "-melf_i386")