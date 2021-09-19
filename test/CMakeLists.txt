
add_subdirectory(googletest)

add_executable(tests main.cpp)
target_link_libraries(tests gtest)
add_test(NAME tests COMMAND tests)