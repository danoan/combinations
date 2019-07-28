cmake_minimum_required(VERSION 3.2)
project(test-single-combinator)

add_executable(test-single-combinator
        test-single-combinator.cpp
        src/correcteness.cpp)

target_include_directories(test-single-combinator PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-single-combinator
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)