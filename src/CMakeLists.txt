# file(GLOB_RECURSE SRC
#     "./*.cpp"
#     "./*.c"
# )
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}
#                     stdlib)

# add_library(src ${SRC})

# file(GLOB_RECURSE ASM_SRC
#     "./*/*.asm"
# )
# add_library(asm_src ${ASM_SRC})

add_subdirectory(apps)
add_subdirectory(drivers)
add_subdirectory(kernel)
add_subdirectory(stdlib)

add_library(loader_asm loader.asm)

set_target_properties(loader_asm PROPERTIES LINK_FLAGS "-melf_i386")