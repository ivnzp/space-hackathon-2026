add_library(hakaton_lib INTERFACE)

target_link_libraries(hakaton_lib INTERFACE sofa)
target_link_libraries(hakaton_lib INTERFACE eigen)
target_link_libraries(hakaton_lib INTERFACE GeographicLib_SHARED)
target_link_libraries(hakaton_lib INTERFACE calceph)

target_include_directories(hakaton_lib INTERFACE
        ..
)

# Явно укажите язык линковки
set_target_properties(hakaton_lib PROPERTIES
        LINKER_LANGUAGE CXX
)