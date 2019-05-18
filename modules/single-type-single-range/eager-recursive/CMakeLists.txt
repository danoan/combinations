cmake_minimum_required(VERSION 3.2)
project(lib-eager-recursive)

add_library(lib-eager-recursive INTERFACE)
target_include_directories(lib-eager-recursive INTERFACE
        include)

if( ${BUILD_TESTS} )
    add_subdirectory(lab/test)
endif()