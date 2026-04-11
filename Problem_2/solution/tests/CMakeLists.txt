include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)


include(GoogleTest)
file(GLOB_RECURSE SOURCES *_test.cpp)

enable_testing()
foreach (S IN LISTS SOURCES)
    get_filename_component(name ${S} NAME_WE)

    add_executable(${name} ${S})
    target_link_libraries(${name} PUBLIC turbospace_lib GTest::gtest_main sofa calceph GeographicLib::GeographicLib_SHARED)

    gtest_discover_tests(${name}
            EXTRA_ARGS "--gtest_color=yes"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    message(${name})

    add_test(NAME ${name} COMMAND ${name})
endforeach ()

get_property(test_list DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)