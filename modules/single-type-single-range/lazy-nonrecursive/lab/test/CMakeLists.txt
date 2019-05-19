cmake_minimum_required(VERSION 3.2)
project(test-lazy-nonrecursive)

add_executable(test-lazy-nonrecursive
        src/correcteness.cpp
        src/execution.cpp
        test-lazy-nonrecursive.cpp)

add_dependencies(test-lazy-nonrecursive comb-utils comb-logger)

target_include_directories(test-lazy-nonrecursive PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/logger/include
        ${CMAKE_SOURCE_DIR}/modules/single-type-single-range/lazy-nonrecursive/include)

target_link_libraries(test-lazy-nonrecursive
        -lcomb-utils
        -lcomb-logger
        -lboost_system
        -lboost_filesystem)