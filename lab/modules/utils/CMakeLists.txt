cmake_minimum_required(VERSION 3.2)
project(magLac-utils)

add_library(magLac-utils SHARED
        src/mockUtils.cpp)

target_include_directories(magLac-utils PRIVATE
        include)
