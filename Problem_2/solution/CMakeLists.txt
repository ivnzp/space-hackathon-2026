cmake_minimum_required(VERSION 3.28)
project(turbospace_lib)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(tests)