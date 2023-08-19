cmake_minimum_required(VERSION 3.27.1)
project(graph VERSION 0.1.0 LANGUAGES C CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)
include_directories(googletest)
include_directories(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
link_directories(${GTEST_DIR}/lib)

enable_testing()
include(GoogleTest)

add_executable(app src/main.cpp)
add_executable(tests tests/test_graph.cpp)
target_link_libraries(tests gtest gtest_main)

gtest_discover_tests(tests)
