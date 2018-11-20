file(GLOB_RECURSE SRC
    "./*.cpp"
    "./*.c"
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    stdlib)

add_library(src ${SRC})

file(GLOB_RECURSE ASM_SRC
    "./*/*.asm"
)
add_library(asm_src ${ASM_SRC})

add_library(loader_asm loader.asm)