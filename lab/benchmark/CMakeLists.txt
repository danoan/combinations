cmake_minimum_required(VERSION 3.2)
project(app-benchmark)

add_executable(app-benchmark benchmark.cpp)
target_include_directories(app-benchmark PRIVATE
        techniques/eager-recursive/include
        techniques/lazy-recursive/include
        techniques/lazy-nonrecursive/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(app-benchmark
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem
        -lpthread)