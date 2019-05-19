cmake_minimum_required(VERSION 3.2)
project(test-lazy-recursive)

add_executable(test-lazy-recursive
        src/correcteness.cpp
        src/execution.cpp
        test-lazy-recursive.cpp)

add_dependencies(test-lazy-recursive comb-utils comb-logger)

target_include_directories(test-lazy-recursive PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/logger/include
        ${CMAKE_SOURCE_DIR}/modules/single-range/lazy-recursive/include)

target_link_libraries(test-lazy-recursive
        -lcomb-utils
        -lcomb-logger
        -lboost_system
        -lboost_filesystem)