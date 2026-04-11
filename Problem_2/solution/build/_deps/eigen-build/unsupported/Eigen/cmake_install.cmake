# Install script for directory: /home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/AdolcForward"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/AlignedVector3"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/ArpackSupport"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/AutoDiff"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/BVH"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/EulerAngles"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/FFT"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/IterativeSolvers"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/KroneckerProduct"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/LevenbergMarquardt"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/MatrixFunctions"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/MPRealSupport"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/NNLS"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/NonLinearOptimization"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/NumericalDiff"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/OpenGLSupport"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/Polynomials"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/SparseExtra"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/SpecialFunctions"
    "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/Splines"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-src/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-build/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/gleblarkin/Study/space-hackathon-2026/Problem_2/solution/build/_deps/eigen-build/unsupported/Eigen/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
