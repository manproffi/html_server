cmake_minimum_required(VERSION 3.10)

# set the project name, version and language c++
project(html_server VERSION 1.0)


#specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

add_subdirectory(src)

add_subdirectory(googletest)
include_directories(include)
include_directories(googletest/googletest/include)
set(SOURCE_TEST_FILES test/test.cpp src/ReversePolishNotation.cpp)
add_executable(test_html_server ${SOURCE_TEST_FILES})
target_link_libraries(test_html_server gtest gtest_main)
