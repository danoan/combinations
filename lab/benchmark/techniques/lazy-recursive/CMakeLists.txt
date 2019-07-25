cmake_minimum_required(VERSION 3.2)
project(lib-lazy-recursive)

add_library(lib-lazy-recursive INTERFACE)

target_include_directories(lib-lazy-recursive INTERFACE
        include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils)

if( ${BUILD_TESTS} )
    add_subdirectory(lab/test)
endif()
