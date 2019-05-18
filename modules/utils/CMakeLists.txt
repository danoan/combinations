cmake_minimum_required(VERSION 3.2)
project(combinations-utils)

add_library(comb-utils SHARED
        src/mockUtils.cpp)

target_include_directories(comb-utils PRIVATE
        include)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS comb-utils
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)