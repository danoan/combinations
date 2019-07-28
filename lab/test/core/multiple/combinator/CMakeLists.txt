cmake_minimum_required(VERSION 3.2)
project(test-multiple-combinator)

add_executable(test-multiple-combinator
        test-multiple-combinator.cpp
        src/correcteness.cpp)

target_include_directories(test-multiple-combinator PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-multiple-combinator
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)