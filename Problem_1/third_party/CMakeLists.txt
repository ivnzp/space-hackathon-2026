include(FetchContent)

FetchContent_Declare(
        sofa
        GIT_REPOSITORY "https://gitlab.com/mipt_ballistics/third-party/sofa.git"
        GIT_TAG main
)

FetchContent_MakeAvailable(sofa)

FetchContent_Declare(
        calceph
        GIT_REPOSITORY "https://gitlab.com/mipt_ballistics/third-party/calceph.git"
        GIT_TAG main
)

FetchContent_MakeAvailable(calceph)

FetchContent_Declare(
        eigen
        GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
        GIT_TAG 5.0.0
)

FetchContent_MakeAvailable(eigen)

FetchContent_Declare(
        GeographicLib_SHARED
        GIT_REPOSITORY "https://github.com/geographiclib/geographiclib.git"
        GIT_TAG v2.6
)

FetchContent_MakeAvailable(GeographicLib_SHARED)