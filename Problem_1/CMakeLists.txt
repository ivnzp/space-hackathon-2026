cmake_minimum_required(VERSION 3.28)
project(hakaton)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(third_party)
add_subdirectory(src)

set(BUILD_TESTS_HAKATON ON)
enable_testing()
if(BUILD_TESTS_HAKATON)
    add_subdirectory(tests)
endif()

set(BUILD_RUN_HAKATON OFF)
enable_testing()
if(BUILD_RUN_HAKATON)
    add_subdirectory(run)
endif()