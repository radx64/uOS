add_library(drivers STATIC)

target_sources(drivers
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/io.h
    ${CMAKE_CURRENT_SOURCE_DIR}/keyboard.h
    ${CMAKE_CURRENT_SOURCE_DIR}/serial.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vga.h    
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/keyboard.c
    ${CMAKE_CURRENT_SOURCE_DIR}/serial.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vga.c
)

target_include_directories(drivers
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../stdlib
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(drivers PROPERTIES COMPILE_FLAGS ${compile_flags})

add_library(drivers_asm STATIC)
target_sources(drivers_asm
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers.asm
)

set_target_properties(drivers_asm PROPERTIES LINK_FLAGS "-melf_i386")

