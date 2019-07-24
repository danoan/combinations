cmake_minimum_required(VERSION 3.2)
project(magLac-utils)

add_library(magLac-utils SHARED
        src/mockUtils.cpp)

target_include_directories(magLac-utils PRIVATE
        include)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS magLac-utils
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)