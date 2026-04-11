file(GLOB_RECURSE SOURCE *.hpp)

add_library(turbospace_lib INTERFACE ${SOURCE})
target_include_directories(turbospace_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(turbospace_lib INTERFACE sofa calceph eigen GeographicLib::GeographicLib_SHARED)