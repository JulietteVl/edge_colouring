cmake_minimum_required(VERSION 3.27.1)
project(graph VERSION 0.1.0 LANGUAGES C CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)
enable_testing()

# Goggle tests
# ------------
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)
# ------------

add_executable(app src/main.cpp)

add_executable(tests_graph tests/test_graph.cpp)
add_executable(tests_segment_tree tests/test_segment_tree.cpp)

target_link_libraries(tests_graph gtest gtest_main pthread)
target_link_libraries(tests_segment_tree gtest gtest_main pthread)

gtest_discover_tests(tests_graph)
gtest_discover_tests(tests_segment_tree)
