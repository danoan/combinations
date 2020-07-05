cmake_minimum_required(VERSION 3.2)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:${BOOST_LIBS_DIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

project(magLac)

link_directories(${BOOST_LIBS_DIR})

link_directories(${CMAKE_BINARY_DIR}/lab/modules/utils
        ${CMAKE_BINARY_DIR}/lab/modules/logger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release")
set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples.")
set(BUILD_BENCHMARK OFF CACHE BOOL "Build benchmark.")

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    if (${COVERAGE})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    endif ()
endif ()

if (${BUILD_EXAMPLES} OR ${BUILD_TESTS} OR ${BUILD_BENCHMARK})
    add_subdirectory(lab/modules/logger)
    add_subdirectory(lab/modules/utils)
endif ()

if (${BUILD_EXAMPLES})
    add_subdirectory(lab/example)
    add_subdirectory(lab/benchmark)
endif ()

if (${BUILD_TESTS})
    add_subdirectory(lab/test)
endif ()

if (${BUILD_BENCHMARK})
    add_subdirectory(lab/benchmark/techniques/eager-recursive)
    add_subdirectory(lab/benchmark/techniques/lazy-recursive)
    add_subdirectory(lab/benchmark/techniques/lazy-nonrecursive)
endif ()


add_subdirectory(modules/core)

install(DIRECTORY modules/core/include
        DESTINATION ${CMAKE_INSTALL_PREFIX})