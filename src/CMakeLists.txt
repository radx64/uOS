file(GLOB_RECURSE SRC
    "./*.cpp"
    "./*.c"
    "./*.asm"
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    stdlib)

add_library(src ${SRC})