cmake_minimum_required(VERSION 3.2)
project(app-comparison)

add_executable(app-comparison comparison.cpp)
target_include_directories(app-comparison PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/single-range/eager-recursive/include
        ${CMAKE_SOURCE_DIR}/modules/single-range/lazy-recursive/include
        ${CMAKE_SOURCE_DIR}/modules/single-range/lazy-nonrecursive/include
        ${CMAKE_SOURCE_DIR}/modules/single-range/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(app-comparison
        -lcomb-utils
        -lcomb-logger
        -lboost_system
        -lboost_filesystem
        -lpthread)