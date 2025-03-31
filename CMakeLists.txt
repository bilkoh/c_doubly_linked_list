cmake_minimum_required(VERSION 3.15)
project(c_doubly_linked_list C)

# Use C11 or later (Clang-compatible)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compile the DLL library (static)
add_library(dll STATIC dll.c)

# Optional: expose headers for other projects
target_include_directories(dll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test executable
add_executable(test_dll test_dll.c dll.c)
target_link_libraries(test_dll PRIVATE dll)

# Enable CTest + register tests
enable_testing()
add_test(NAME DLLTests COMMAND test_dll)

add_custom_target(run_all_tests ALL
    COMMAND ${CMAKE_CTEST_COMMAND} -C Debug --output-on-failure
    DEPENDS test_dll
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)