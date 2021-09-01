add_library(stdlib STATIC)
target_sources(stdlib
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/defs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/math.h
    ${CMAKE_CURRENT_SOURCE_DIR}/stdarg.h
    ${CMAKE_CURRENT_SOURCE_DIR}/stdint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/stdio.h
    ${CMAKE_CURRENT_SOURCE_DIR}/string.h
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/math.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stdio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/string.c
)

target_include_directories(stdlib
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)


set_target_properties(stdlib PROPERTIES COMPILE_FLAGS ${compile_flags})