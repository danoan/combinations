cmake_minimum_required(VERSION 3.2)
project(app-lazy-nonrecursive)

add_executable(app-lazy-nonrecursive lazy-nonrecursive.cpp)

target_include_directories(app-lazy-nonrecursive PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/single-range/lazy-nonrecursive/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include)

target_link_libraries(app-lazy-nonrecursive
        -lcomb-utils)