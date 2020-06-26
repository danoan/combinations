cmake_minimum_required(VERSION 3.2)
project(lib-lazy-nonrecursive)

add_library(lib-lazy-nonrecursive INTERFACE)

target_include_directories(lib-lazy-nonrecursive INTERFACE
        include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils)

if (${BUILD_TESTS})
    add_subdirectory(lab/test)
endif ()

