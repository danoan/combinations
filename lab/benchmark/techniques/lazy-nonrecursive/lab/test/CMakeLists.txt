cmake_minimum_required(VERSION 3.2)
project(test-lazy-nonrecursive)

add_executable(test-lazy-nonrecursive
        src/correcteness.cpp
        src/execution.cpp
        test-lazy-nonrecursive.cpp)

add_dependencies(test-lazy-nonrecursive magLac-utils magLac-logger)

target_include_directories(test-lazy-nonrecursive PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${CMAKE_SOURCE_DIR}/lab/benchmark/techniques/lazy-nonrecursive/include)

target_link_libraries(test-lazy-nonrecursive
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)
