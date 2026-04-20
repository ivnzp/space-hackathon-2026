include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)


include(GoogleTest)
file(GLOB_RECURSE SOURCES test_*.cpp)

message(${SOURCES})

enable_testing()
foreach (S IN LISTS SOURCES)
    message("${S}")
    get_filename_component(name ${S} NAME_WE)

    message("${name}")
    add_executable(${name} ${S})
    target_link_libraries(${name} PUBLIC hakaton_lib GTest::gtest_main sofa calceph eigen GeographicLib_SHARED)
    #    target_compile_definitions(${FILE_NAME} PUBLIC TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../../data/")

    gtest_discover_tests(${name}
            EXTRA_ARGS "--gtest_color=yes"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    add_test(NAME ${name} COMMAND ${name})
endforeach ()

message("=== TESTS CONFIGURATION SUMMARY ===")
message("Number of test sources found: ${SOURCES}")
get_property(test_list DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)
message("Registered tests: ${test_list}")