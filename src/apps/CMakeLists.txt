add_library(apps STATIC)
target_sources(apps
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/terminal.h
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/terminal.c
)

target_include_directories(apps
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../stdlib
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(apps PROPERTIES COMPILE_FLAGS ${compile_flags})