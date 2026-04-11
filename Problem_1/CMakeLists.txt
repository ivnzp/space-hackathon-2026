cmake_minimum_required(VERSION 3.28)
project(hakaton)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

# --- 1. НАСТРОЙКА ЗАГРУЗКИ И СБОРКИ ALGLIB ---
# Указываем, куда всё установится
set(ALGLIB_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/alglib_install)
set(ALGLIB_INCLUDE_DIR ${ALGLIB_INSTALL_PREFIX}/include)
set(ALGLIB_LIBRARY_DIR ${ALGLIB_INSTALL_PREFIX}/lib)

# Загружаем и собираем ALGLIB с помощью готового CMake-проекта
ExternalProject_Add(
        alglib_external
        GIT_REPOSITORY "https://github.com/S-Dafarra/alglib-cmake.git"
        GIT_TAG        "a332573"  # Этот коммит точно существует
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${ALGLIB_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install
)

# --- 2. СОЗДАНИЕ ЦЕЛИ ДЛЯ ЛИНКОВКИ ---
# Создаём ИМПОРТИРУЕМУЮ библиотеку, чтобы CMake знал, где лежат файлы
add_library(ALGLIB::ALGLIB STATIC IMPORTED GLOBAL)
set_target_properties(ALGLIB::ALGLIB PROPERTIES
        IMPORTED_LOCATION ${ALGLIB_LIBRARY_DIR}/libalglib.a
        INTERFACE_INCLUDE_DIRECTORIES ${ALGLIB_INCLUDE_DIR}
)
# Указываем, что наша библиотека должна быть собрана до начала линковки
add_dependencies(ALGLIB::ALGLIB alglib_external)

# --- 3. ПОДКЛЮЧЕНИЕ К ВАШИМ ТЕСТАМ ---
# Теперь нужно подключить ALGLIB к тестам.
# Сначала подключаем ваши поддиректории
add_subdirectory(third_party)
add_subdirectory(src)

# ВАЖНО: Замените 'test_spline' на реальное имя вашей тестовой цели!
# Если нужно, просто скопируйте эту строку для каждого теста.
if(TARGET test_spline)
    target_link_libraries(test_spline PRIVATE ALGLIB::ALGLIB)
    target_include_directories(test_spline PRIVATE ${ALGLIB_INCLUDE_DIR})
endif()

# --- 4. ПОДКЛЮЧЕНИЕ ОСТАЛЬНЫХ ЧАСТЕЙ ПРОЕКТА ---
# Убедитесь, что эта секция идёт ПОСЛЕ подключения ALGLIB к вашим тестам

message(STATUS "ALGLIB_INCLUDE_DIR is: ${ALGLIB_INCLUDE_DIR}")

option(BUILD_TESTS_HAKATON "Build tests" ON)
if(BUILD_TESTS_HAKATON)
    enable_testing()
    add_subdirectory(tests)  # Здесь создаются ваши тесты
endif()

option(BUILD_RUN_HAKATON "Build run executable" ON)
if(BUILD_RUN_HAKATON)
    add_subdirectory(run)
endif()