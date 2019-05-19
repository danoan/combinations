cmake_minimum_required(VERSION 3.2)
project(app-lazy-recursive)

add_executable(app-lazy-recursive lazy-recursive.cpp)

target_include_directories(app-lazy-recursive PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/single-range/lazy-recursive/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include)

target_link_libraries(app-lazy-recursive
        -lcomb-utils
        -lboost_system
        -lboost_filesystem)