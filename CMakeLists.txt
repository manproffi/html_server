cmake_minimum_required(VERSION 3.10)

# set the project name, version and language c++
project(html_server VERSION 1.0)


#specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)